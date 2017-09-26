#include "model.hpp"

void printmat4(glm::mat4 Awv) {
	printf("\n");
	printf("%f, %f, %f, %f \n", Awv[0][0], Awv[1][0], Awv[2][0], Awv[3][0]);
	printf("%f, %f, %f, %f \n", Awv[0][1], Awv[1][1], Awv[2][1], Awv[3][1]);
	printf("%f, %f, %f, %f \n", Awv[0][2], Awv[1][2], Awv[2][2], Awv[3][2]);
	printf("%f, %f, %f, %f \n", Awv[0][3], Awv[1][3], Awv[2][3], Awv[3][3]);
	printf("\n");
}
////////////////////////////////


Vertex::Vertex() {
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	color = glm::vec3(0.0f, 0.0f, 0.0f);
}
Vertex::Vertex(glm::vec3 p, glm::vec3 c) {
	position = p;
	color = c;
}


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

void Model::assignBuffer() {
	size_t size_points = vertex_list.size() * sizeof (glm::vec3);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData (GL_ARRAY_BUFFER, size_points * 2, &vertex_list[0], GL_STATIC_DRAW);
}

void Model::draw(GLuint vPosition, GLuint vColor, GLuint uModelViewMatrix, GLenum mode, glm::mat4 modelview_matrix) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0) );
	glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(glm::vec3)) );
	glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));

	glDrawArrays(mode, 0, vertex_list.size());
}
////////////////////////////////


void WorldModel::calc_modelling_transformation() {
	glm::mat4 scaled_mtx = glm::scale(glm::mat4(1.0f), scale_vec);

	glm::mat4 rotation_mtx = glm::rotate( glm::mat4(1.0f), rotation_vec.x, glm::vec3(1.0f, 0.0f, 0.0f));
	rotation_mtx = glm::rotate( rotation_mtx, rotation_vec.y, glm::vec3(0.0f, 1.0f, 0.0f));
	rotation_mtx = glm::rotate( rotation_mtx, rotation_vec.z, glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 translation_mtx = glm::translate(glm::mat4(1.0f), position_vec);

	transformation_mtx = translation_mtx * rotation_mtx * scaled_mtx;
}
////////////////////////////////


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

	frustum.vertex_list.push_back(Vertex(glm::vec3(R, T, -N), magenta));
	frustum.vertex_list.push_back(Vertex(glm::vec3(0, 0, 0), magenta));
	frustum.vertex_list.push_back(Vertex(glm::vec3(L, T, -N), magenta));
	frustum.vertex_list.push_back(Vertex(glm::vec3(0, 0, 0), magenta));
	frustum.vertex_list.push_back(Vertex(glm::vec3(L, B, -N), magenta));
	frustum.vertex_list.push_back(Vertex(glm::vec3(0, 0, 0), magenta));
	frustum.vertex_list.push_back(Vertex(glm::vec3(R, B, -N), magenta));
	frustum.vertex_list.push_back(Vertex(glm::vec3(0, 0, 0), magenta));

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

	eye.vertex_list.resize(0);
	eye.vertex_list.push_back(Vertex(glm::vec3(0.0f, 0.0f, 0.0f), red));

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");

	vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
	glEnableVertexAttribArray( vPosition );

	vColor = glGetAttribLocation( shaderProgram, "vColor" );
	glEnableVertexAttribArray( vColor );

	frustum.assignBuffer();
	eye.assignBuffer();
}

void WorldCamera::draw(glm::mat4 transformation_mtx) {
	glBindVertexArray(vao);

	frustum.draw(vPosition, vColor, uModelViewMatrix, GL_LINES, transformation_mtx);
	glPointSize(4.0f);
	eye.draw(vPosition, vColor, uModelViewMatrix, GL_POINTS, transformation_mtx);
}

void Scene::calc_center() {
	center = glm::vec3(axes.dummy_matrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
}
////////////////////////////////


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

	vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
	glEnableVertexAttribArray( vPosition );

	vColor = glGetAttribLocation( shaderProgram, "vColor" );
	glEnableVertexAttribArray( vColor );

	m.assignBuffer();
}

void Axes::draw(glm::mat4 transformation_mtx) {
	glBindVertexArray(vao);
	m.draw(vPosition, vColor, uModelViewMatrix, GL_LINES, transformation_mtx * dummy_matrix);
}
////////////////////////////////

bool Scene::load() {
	FILE *fp_input = fopen("./binary_models/myscene.scn", "r" );
	if (fp_input ==  NULL) {
		printf("Error opening file ./binary_models/myscene.scn\n");
		return false;
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");

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

	fclose(fp_input);
	return true;
}

// apply third person to everything
// apply inverse A_wcs_vcs to frustum only
// apply model tranform to those 3 models
// apply dummy to  frustum, and models
void Scene::draw(glm::mat4 third_person_transform) {

	glBindVertexArray(vao);

	for (int i = 0; i < 3; ++i)
		model_list[i].m.draw(vPosition, vColor, uModelViewMatrix, GL_TRIANGLES, third_person_transform
		                     * dummy_matrix * model_list[i].transformation_mtx);

	cam.draw(third_person_transform * dummy_matrix * reverse_vcs);
	axes.draw(third_person_transform);
}

// Proof of Column Major - Press 1
// glm::vec4 trial = glm::vec4(glm::vec3(1.0f,1.0f,1.0f),1.0f);
// glm::mat4 trial2 = glm::mat4(1.0f);
// trial2[3][0] = 2;
// trial2[3][1] = 3;
// trial2[3][2] = 4;
// trial2[0][3] = 5;
// trial2[1][3] = 6;
// trial2[2][3] = 7;
// glm::vec4 output = glm::vec4(trial2 * trial);
// printf("%f, %f, %f \n", output[0], output[1], output[2]);


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
	glm::mat4 pliden = glm::mat4(A_wcs_vcs * reverse_vcs) ;
	printmat4(pliden);
}

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

void Scene::calc_CCS_NDCS() {
}

void Scene::calc_NDCS_DCS() {
	A_ndcs_dcs[2][2] = -0.01;
	A_ndcs_dcs[3][2] = -1.0;
	A_ndcs_dcs[1][1] = 10.0;
	A_ndcs_dcs[0][0] = 10.0;
}
