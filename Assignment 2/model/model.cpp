#include "model.hpp"
/**
 * @brief      Constructs the default vertex.
 */
Vertex::Vertex() {
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	color = glm::vec3(0.0f, 0.0f, 0.0f);
}
/**
 * @brief      Constructs the vertex given position and color.
 *
 * @param[in]  p     position vec3
 * @param[in]  c     color vec3
 */
Vertex::Vertex(glm::vec3 p, glm::vec3 c) {
	position = p;
	color = c;
}


//--------------------------------------------------------------


/**
 * @brief      Load model from a .raw file  and store its vertex data
 *
 * @param      filename the .raw file that contains the model
 *
 * @return     true iff file loaded successfully
 */
bool Model::load(char* filename) {
	FILE *fp_input = fopen(filename, "r" );
	if (fp_input ==  NULL) {
		printf("Error opening file %s\n", filename);
		return false;
	}


	vertex_list.resize(0);

	float vx, vy, vz, cx, cy, cz;
	while (fscanf (fp_input, "%f %f %f %f %f %f", &vx, &vy, &vz, &cx, &cy, &cz) != EOF) {
		Vertex v;
		v.position = glm::vec3(vx, vy, vz);
		v.color = glm::vec3(cx, cy, cz);
		vertex_list.push_back(v);
	}

	fclose(fp_input);
	return true;
}

/**
 * @brief      fill the vbo for the model
 */
void Model::assignBuffer() {
	size_t size_points = vertex_list.size() * sizeof (glm::vec3);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData (GL_ARRAY_BUFFER, size_points * 2, &vertex_list[0], GL_STATIC_DRAW);
}

/**
 * @brief      draw model on screen
 *
 * @param[in]  vPosition         location of position input in vertex shader
 * @param[in]  vColor            location of color input in vertex shader
 * @param[in]  uModelViewMatrix  location of transformation matrix input in vertex shader
 * @param[in]  uNDCS             location of input int uNDCS(to decide whether to manually divide or not) in vertex shader
 * @param[in]  mode              The mode of drawing the model (GL_TRIANGLES, GL_LINES, GL_POINT)
 * @param[in]  modelview_matrix  The modelview matrix to be substituted at location uModelViewMatrix
 * @param[in]  ndcs_divide       The ndcs int to be substituted at location uNDCS
 */
void Model::draw(GLuint vPosition, GLuint vColor, GLuint uModelViewMatrix, GLuint uNDCS, GLenum mode, glm::mat4 modelview_matrix, int ndcs_divide) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0) );
	glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(glm::vec3)) );
	glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
	glUniform1i(uNDCS, ndcs_divide);
	glDrawArrays(mode, 0, vertex_list.size());
}

/**
 * @brief      Determines if v1 is inside the clipping edge.
 *
 * @param[in]  v1               The v 1
 * @param[in]  edge             The edge
 * @param[in]  is_less_in       Indicates if less in
 * @param[in]  is_edge_x_based  Indicates if edge x based
 *
 * @return     1 if inside, 0 otherwise.
 */
int is_inside(Vertex v1, float edge, bool is_less_in, bool is_edge_x_based) {
	bool ans = false;
	if (is_edge_x_based) {
		if (is_less_in) {
			ans = v1.position.x <= edge;
		}
		else {
			ans = v1.position.x >= edge;
		}
	}
	else {
		if (is_less_in) {
			ans = v1.position.y <= edge;
		}
		else {
			ans = v1.position.y >= edge;
		}
	}
	if(ans)
		return 1;
	else
		return 0;
}

/**
 * @brief      Calulate the interection vertex between line of 2 vertices and a clipping edge
 *
 * @param[in]  v_in             The v in
 * @param[in]  v_out            The v out
 * @param[in]  edge             The edge
 * @param[in]  is_edge_x_based  Indicates if edge x based
 *
 * @return     Intersect vertex with correct interpolated z val and colors
 */
Vertex intersection(Vertex v_in, Vertex v_out, float edge, bool is_edge_x_based){
	if(is_edge_x_based){
		float pos_y = v_in.position.y  + (v_out.position.y - v_in.position.y) * (edge - v_in.position.x)/(v_out.position.x - v_in.position.x);
		float pos_z = v_in.position.z  + (v_out.position.z - v_in.position.z) * (edge - v_in.position.x)/(v_out.position.x - v_in.position.x);
		
		float col_r = v_in.color.x  + (v_out.color.x - v_in.color.x) * (edge - v_in.position.x)/(v_out.position.x - v_in.position.x); 
		float col_g = v_in.color.y  + (v_out.color.y - v_in.color.y) * (edge - v_in.position.x)/(v_out.position.x - v_in.position.x);
		float col_b = v_in.color.z  + (v_out.color.z - v_in.color.z) * (edge - v_in.position.x)/(v_out.position.x - v_in.position.x);

		return Vertex(glm::vec3(edge, pos_y, pos_z),glm::vec3(col_r, col_g, col_b));
		// return Vertex(glm::vec3(edge, pos_y, pos_z),v_out.color);
	}
	else{
		float pos_x = v_in.position.x  + (v_out.position.x - v_in.position.x) * (edge - v_in.position.y)/(v_out.position.y - v_in.position.y);
		float pos_z = v_in.position.z  + (v_out.position.z - v_in.position.z) * (edge - v_in.position.y)/(v_out.position.y - v_in.position.y);
		
		float col_r = v_in.color.x  + (v_out.color.x - v_in.color.x) * (edge - v_in.position.y)/(v_out.position.y - v_in.position.y); 
		float col_g = v_in.color.y  + (v_out.color.y - v_in.color.y) * (edge - v_in.position.y)/(v_out.position.y - v_in.position.y);
		float col_b = v_in.color.z  + (v_out.color.z - v_in.color.z) * (edge - v_in.position.y)/(v_out.position.y - v_in.position.y);

		return Vertex(glm::vec3(pos_x, edge, pos_z),glm::vec3(col_r, col_g, col_b));
		// return Vertex(glm::vec3(pos_x, edge, pos_z),v_out.color);	
	}
}

/**
 * @brief      Clip a triangle given by three vertices
 *
 * @param[in]  v1               The first vertex of triangle
 * @param[in]  v2               The second vertex of triangle
 * @param[in]  v3               The third vertex of triangle
 * @param[in]  edge             The edge to be clipped about
 * @param      output           The output vertex list that will be appended with new clipped vertices
 */
void clip_triangle(Vertex v1, Vertex v2, Vertex v3, float edge, bool is_less_in , bool is_edge_x_based, std::vector<Vertex> &output) {
	int mask = is_inside(v1, edge, is_less_in, is_edge_x_based);
	mask <<= 1;
	mask |= is_inside(v2, edge, is_less_in, is_edge_x_based);
	mask <<= 1;
	mask |= is_inside(v3, edge, is_less_in, is_edge_x_based);
	// mask = v1 | v2 | v3 
	switch(mask){
		case 0 :
			break;
		case 1 :
			output.push_back(intersection(v3, v1, edge, is_edge_x_based));
			output.push_back(intersection(v3, v2, edge, is_edge_x_based));
			output.push_back(v3);
			break;	
		case 2 :
			output.push_back(intersection(v2, v1, edge, is_edge_x_based));
			output.push_back(v2);
			output.push_back(intersection(v2, v3, edge, is_edge_x_based));
			break;
		case 3 :
			output.push_back(intersection(v2, v1, edge, is_edge_x_based));
			output.push_back(v2);
			output.push_back(v3);

			output.push_back(intersection(v3, v1, edge, is_edge_x_based));
			output.push_back(intersection(v2, v1, edge, is_edge_x_based));
			output.push_back(v3);
			break;
		
		case 4 :
			output.push_back(v1);
			output.push_back(intersection(v1, v2, edge, is_edge_x_based));
			output.push_back(intersection(v1, v3, edge, is_edge_x_based));
			break;
		case 5 :
			output.push_back(intersection(v1, v2, edge, is_edge_x_based));
			output.push_back(v1);
			output.push_back(v3);

			output.push_back(intersection(v3, v2, edge, is_edge_x_based));
			output.push_back(intersection(v1, v2, edge, is_edge_x_based));
			output.push_back(v3);
			break;
		
		case 6 :
			output.push_back(intersection(v1, v3, edge, is_edge_x_based));
			output.push_back(v1);
			output.push_back(v2);

			output.push_back(intersection(v2, v3, edge, is_edge_x_based));
			output.push_back(intersection(v1, v3, edge, is_edge_x_based));
			output.push_back(v2);
			break;
		case 7 :
			output.push_back(v1);
			output.push_back(v2);
			output.push_back(v3);
			break;
	}
}

/**
 * @brief      Clip model for a given edge of DCS(assuming DCS is a sqaure -10 -> 10 along principle axes)
 *
 * @param[in]  vList            The transformed vertices list
 * @param[in]  edge             The edge ( either x value or y value) 
 * @param[in]  is_less_in       Indicates if less value than edge considered as inside the view area
 * @param[in]  is_edge_x_based  Indicates if edge horizontal or vertical
 *
 * @return    New vertex_list of cliped verties
 */
std::vector<Vertex>  clip_for_edge(std::vector<Vertex> vList, float edge, bool is_less_in , bool is_edge_x_based) {
	std::vector<Vertex> output(0);
	for (int i = 0; i < vList.size(); i += 3) {
		clip_triangle(vList[i], vList[i + 1], vList[i + 2], edge, is_less_in, is_edge_x_based, output);
	}
	return output;
}

/**
 * @brief      Clip the given model after tranforming it to DCS
 *
 * @param[in]  transformation_mtx  The transformation mtx for converting it to DCS
 *
 * @return     new clipped model coordinates 
 */
Model Model::clip(glm::mat4 transformation_mtx) {	
	Model clipped_model;
	
	std::vector<Vertex> transformed_vertex_list(vertex_list);
	for (int i = 0; i < vertex_list.size(); i += 3) {
		glm::vec4 x0 = transformation_mtx * glm::vec4(vertex_list[i].position, 1.0f);
		transformed_vertex_list[i] = Vertex(glm::vec3(x0.x / x0.w, x0.y / x0.w, x0.z / x0.w), vertex_list[i].color);

		glm::vec4 x1 = transformation_mtx * glm::vec4(vertex_list[i + 1].position, 1.0f);
		transformed_vertex_list[i + 1] = Vertex(glm::vec3(x1.x / x1.w, x1.y / x1.w, x1.z / x1.w), vertex_list[i+1].color);

		glm::vec4 x2 = transformation_mtx * glm::vec4(vertex_list[i + 2].position, 1.0f);
		transformed_vertex_list[i + 2] = Vertex(glm::vec3(x2.x / x2.w, x2.y / x2.w, x2.z / x2.w), vertex_list[i+2].color);
	}

	transformed_vertex_list = clip_for_edge(transformed_vertex_list, 10, true, false);
	transformed_vertex_list = clip_for_edge(transformed_vertex_list, -10, false, true);
	transformed_vertex_list = clip_for_edge(transformed_vertex_list, -10, false, false);
	clipped_model.vertex_list = clip_for_edge(transformed_vertex_list, 10, true, true);

	clipped_model.assignBuffer();
	return clipped_model;
}


//--------------------------------------------------------------


/**
 * @brief      Calculates the modelling transformation (transformation_mtx) to place models in the world.
 */
void WorldModel::calc_modelling_transformation() {
	glm::mat4 scaled_mtx = glm::scale(glm::mat4(1.0f), scale_vec);

	glm::mat4 rotation_mtx_x = glm::rotate( glm::mat4(1.0f), glm::radians(rotation_vec.x), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotation_mtx_y = glm::rotate( glm::mat4(1.0f), glm::radians(rotation_vec.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotation_mtx_z = glm::rotate( glm::mat4(1.0f), glm::radians(rotation_vec.z), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 translation_mtx = glm::translate(glm::mat4(1.0f), position_vec);

	transformation_mtx = translation_mtx * rotation_mtx_z * rotation_mtx_y * rotation_mtx_x * scaled_mtx;
}


//--------------------------------------------------------------


/**
 * @brief      Creates frustum, eye, and projectors models approriately.
 */
void WorldCamera::create_frustum() {
	glm::vec3 cyan = glm::vec3(0.0f, 1.0f, 1.0f);
	glm::vec3 red = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 magenta = glm::vec3(1.0f, 0.0f, 1.0f);
	float fL = F * L / N, fR = F * R / N, fT = F * T / N, fB = F * B / N;

	frustum.vertex_list.resize(0);
	frustum.vertex_list.push_back(Vertex(glm::vec3(R, T, -N), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(fR, fT, -F), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(L, T, -N), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(fL, fT, -F), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(L, B, -N), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(fL, fB, -F), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(R, B, -N), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(fR, fB, -F), cyan));


	frustum.vertex_list.push_back(Vertex(glm::vec3(R, T, -N), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(L, T, -N), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(L, T, -N), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(L, B, -N), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(L, B, -N), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(R, B, -N), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(R, B, -N), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(R, T, -N), cyan));

	frustum.vertex_list.push_back(Vertex(glm::vec3(fR, fT, -F), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(fL, fT, -F), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(fL, fT, -F), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(fL, fB, -F), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(fL, fB, -F), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(fR, fB, -F), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(fR, fB, -F), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(fR, fT, -F), cyan));

	middle.vertex_list.resize(0);
	middle.vertex_list.push_back(Vertex(glm::vec3(R, T, -N), magenta));
	middle.vertex_list.push_back(Vertex(glm::vec3(0, 0, 0), magenta));
	middle.vertex_list.push_back(Vertex(glm::vec3(L, T, -N), magenta));
	middle.vertex_list.push_back(Vertex(glm::vec3(0, 0, 0), magenta));
	middle.vertex_list.push_back(Vertex(glm::vec3(L, B, -N), magenta));
	middle.vertex_list.push_back(Vertex(glm::vec3(0, 0, 0), magenta));
	middle.vertex_list.push_back(Vertex(glm::vec3(R, B, -N), magenta));
	middle.vertex_list.push_back(Vertex(glm::vec3(0, 0, 0), magenta));

	eye.vertex_list.resize(0);
	eye.vertex_list.push_back(Vertex(glm::vec3(0.0f, 0.0f, 0.0f), red));

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
	uNDCS = glGetUniformLocation( shaderProgram, "uNDCS");

	vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
	glEnableVertexAttribArray( vPosition );

	vColor = glGetAttribLocation( shaderProgram, "vColor" );
	glEnableVertexAttribArray( vColor );

	frustum.assignBuffer();
	middle.assignBuffer();
	eye.assignBuffer();

	display_eye = 1;
}

/**
 * @brief      Draw the camera ( eye, frustum, projectors) on the screen
 *
 * @param[in]  transformation_mtx  The transformation mtx to be given as input to shader for this draw call
 */
void WorldCamera::draw(glm::mat4 transformation_mtx) {
	glBindVertexArray(vao);

	frustum.draw(vPosition, vColor, uModelViewMatrix, uNDCS, GL_LINES, transformation_mtx, 0);
	glPointSize(4.0f);
	if (display_eye == 1) {
		middle.draw(vPosition, vColor, uModelViewMatrix, uNDCS, GL_LINES, transformation_mtx, 0);
		eye.draw(vPosition, vColor, uModelViewMatrix, uNDCS, GL_POINTS, transformation_mtx, 0);
	}
}


//--------------------------------------------------------------


/**
 * @brief      Creates WCC axes model.
 */
void Axes::create_axes() {
	glm::vec3 red = glm::vec3(1.0f, 0.0f, 0.0f);  //x
	glm::vec3 green = glm::vec3(0.0f, 1.0f, 0.0f); //y
	glm::vec3 blue = glm::vec3(0.0f, 0.0f, 1.0f); //z

	float length = 3;

	m.vertex_list.resize(0);

	m.vertex_list.push_back(Vertex(glm::vec3(0, 0, 0), red));
	m.vertex_list.push_back(Vertex(glm::vec3(length, 0, 0), red));

	m.vertex_list.push_back(Vertex(glm::vec3(0, 0, 0), green));
	m.vertex_list.push_back(Vertex(glm::vec3(0, length, 0), green));

	m.vertex_list.push_back(Vertex(glm::vec3(0, 0, 0), blue));
	m.vertex_list.push_back(Vertex(glm::vec3(0, 0, length), blue));

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
	uNDCS = glGetUniformLocation( shaderProgram, "uNDCS");

	vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
	glEnableVertexAttribArray( vPosition );

	vColor = glGetAttribLocation( shaderProgram, "vColor" );
	glEnableVertexAttribArray( vColor );

	m.assignBuffer();
}

/**
 * @brief      draw the WWC axes model on the screen
 *
 * @param[in]  transformation_mtx  The transformation mtx to be used as input to this draw call
 */
void Axes::draw(glm::mat4 transformation_mtx) {
	glBindVertexArray(vao);
	m.draw(vPosition, vColor, uModelViewMatrix, uNDCS, GL_LINES, transformation_mtx * dummy_matrix, 0);
}


//--------------------------------------------------------------


/**
 * @brief      Parse scene (.scn) file and load all the elements present in the scene
 *
 * @return     true iff successfully loaded the file ./binary_models/myscene.scn
 */
bool Scene::load() {
	FILE *fp_input = fopen("./binary_models/myscene.scn", "r" );
	if (fp_input ==  NULL) {
		printf("Error opening file ./binary_models/myscene.scn\n");
		return false;
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
	uNDCS = glGetUniformLocation( shaderProgram, "uNDCS");

	vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
	glEnableVertexAttribArray( vPosition );

	vColor = glGetAttribLocation( shaderProgram, "vColor" );
	glEnableVertexAttribArray( vColor );

	model_list.resize(0);

	for (int i = 0; i < 3; ++i) {
		char model_filename[30];
		fscanf (fp_input, "%s", model_filename);

		WorldModel worldModel;
		worldModel.m.load(model_filename);
		worldModel.m.assignBuffer();

		float a, b, c;
		fscanf (fp_input, "%f %f %f", &a, &b, &c);
		worldModel.scale_vec = glm::vec3(a, b, c);

		fscanf (fp_input, "%f %f %f", &a, &b, &c);
		worldModel.rotation_vec = glm::vec3(a, b, c);

		fscanf (fp_input, "%f %f %f", &a, &b, &c);
		worldModel.position_vec = glm::vec3(a, b, c);

		worldModel.calc_modelling_transformation();
		model_list.push_back(worldModel);
	}

	float a, b, c;
	fscanf (fp_input, "%f %f %f", &a, &b, &c);
	cam.eye_position = glm::vec3(a, b, c);

	fscanf (fp_input, "%f %f %f", &a, &b, &c);
	cam.look_at = glm::vec3(a, b, c);

	fscanf (fp_input, "%f %f %f", &a, &b, &c);
	cam.up = glm::vec3(a, b, c);

	fscanf (fp_input, "%f %f %f %f", &cam.L, &cam.R, &cam.T, &cam.B);
	fscanf (fp_input, "%f %f", &cam.N, &cam.F);

	cam.create_frustum();
	axes.create_axes();
	calc_center();

	calc_WCS_VCS();
	calc_VCS_CCS();
	calc_CCS_NDCS();
	calc_NDCS_DCS();

	glm::mat4 temp = scene.A_ndcs_dcs * scene.A_ccs_ndcs * scene.A_vcs_ccs * scene.A_wcs_vcs;
	clipped_model_list.resize(3);
	for (int i = 0; i < 3; ++i) {
		clipped_model_list[i].m = model_list[i].m.clip(temp * model_list[i].transformation_mtx);
		clipped_model_list[i].transformation_mtx = glm::mat4(1.0f);
	}
	fclose(fp_input);
	return true;
}

/**
 * @brief      draw all contents of the screen
 *
 * @param[in]  third_person_transform  the third person transformation matrix to be used
 */
void Scene::draw(glm::mat4 third_person_transform) {

	glBindVertexArray(vao);
	if (should_clip) {
		for (int i = 0; i < 3; ++i)
			clipped_model_list[i].m.draw(vPosition, vColor, uModelViewMatrix, uNDCS, GL_TRIANGLES, 
				third_person_transform,ndcs_divide);

	}
	else {
		for (int i = 0; i < 3; ++i)
			model_list[i].m.draw(vPosition, vColor, uModelViewMatrix, uNDCS, GL_TRIANGLES, 
				third_person_transform * dummy_matrix * model_list[i].transformation_mtx, ndcs_divide);
	}
	cam.draw(third_person_transform * dummy_matrix * reverse_vcs);
	axes.draw(third_person_transform);
}

/**
 * @brief      Calculates the view center ( for easy rotation by key presses).
 */
void Scene::calc_center() {
	
	center = glm::vec3(axes.dummy_matrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

/**
 * @brief      Calculates the A_wcs_vcs matrix from eye_position, lookat and up vectors.
 */
void Scene::calc_WCS_VCS() {
	glm::vec3 n = -(cam.look_at) / glm::length(cam.look_at);
	glm::vec3 u = glm::cross(cam.up, n) / glm::length(glm::cross(cam.up, n));
	glm::vec3 v = glm::cross(n, u);

	glm::vec4 row1 = glm::vec4(u, -cam.eye_position.x);
	glm::vec4 row2 = glm::vec4(v, -cam.eye_position.y);
	glm::vec4 row3 = glm::vec4(n, -cam.eye_position.z);
	glm::vec4 row4 = glm::vec4(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);

 	A_wcs_vcs = glm::transpose(glm::mat4(row1, row2, row3, row4));
 	reverse_vcs = glm::inverse(A_wcs_vcs);
}

/**
 * @brief      Calculates the A_vcs_ccs matrix from L,R,T,B,N,F values.
 */
void Scene::calc_VCS_CCS() {
	glm::mat4 sh = glm::mat4(1.0f);
	sh[2][0] = (cam.R + cam.L) / (2.0 * cam.N);
	sh[2][1] = (cam.T + cam.B) / (2.0 * cam.N);

	glm::mat4 sc = glm::mat4(1.0f);
	sc[0][0] = (2.0 * cam.N) / (cam.R - cam.L);
	sc[1][1] = (2.0 * cam.N) / (cam.T - cam.B);

	glm::mat4 Nm = glm::mat4(1.0f);
	Nm[2][2] = -(cam.F + cam.N) / (cam.F - cam.N);
	Nm[2][3] = -1.0f;
	Nm[3][2] = -(2.0 * cam.F * cam.N) / (cam.F - cam.N);
	Nm[3][3] = 0.0f;

	A_vcs_ccs = Nm * sc * sh;
}

/**
 * @brief      Set matrix in shader (which in future will be used for manual CCS -> NDCS transform.
 */
void Scene::calc_CCS_NDCS() {
	GLuint uScene = glGetUniformLocation( shaderProgram, "uScene");
	glUniformMatrix4fv(uScene, 1, GL_FALSE, glm::value_ptr(A_wcs_vcs));
}

/**
 * @brief      Calculates the A_ndcs_dcs matrix for projection from NDCS to DCS.
 *             Also z coordinate maps to 0.01 for correct culling and lateral
 *             inversion is taken care of
 */
void Scene::calc_NDCS_DCS() {
	A_ndcs_dcs[2][2] = -0.01;
	A_ndcs_dcs[3][2] = -1.0;
	A_ndcs_dcs[1][1] = 10.0;
	A_ndcs_dcs[0][0] = 10.0;
}
