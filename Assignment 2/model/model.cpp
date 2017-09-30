#include "model.hpp"

// void printmat4(glm::mat4 Awv) {
// 	printf("\n");
// 	printf("%f, %f, %f, %f \n", Awv[0][0], Awv[1][0], Awv[2][0], Awv[3][0]);
// 	printf("%f, %f, %f, %f \n", Awv[0][1], Awv[1][1], Awv[2][1], Awv[3][1]);
// 	printf("%f, %f, %f, %f \n", Awv[0][2], Awv[1][2], Awv[2][2], Awv[3][2]);
// 	printf("%f, %f, %f, %f \n", Awv[0][3], Awv[1][3], Awv[2][3], Awv[3][3]);
// 	printf("\n");
// }


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

	transformed_vertex_list = clip_for_edge(transformed_vertex_list, 10, true, 2);
	transformed_vertex_list = clip_for_edge(transformed_vertex_list, -10, false, 1);
	transformed_vertex_list = clip_for_edge(transformed_vertex_list, -10, false, 2);
	transformed_vertex_list = clip_for_edge(transformed_vertex_list, 10, true, 1);
	transformed_vertex_list = clip_for_edge(transformed_vertex_list, -0.99, true, 3);
	clipped_model.vertex_list = clip_for_edge(transformed_vertex_list, -1.01, false, 3);
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