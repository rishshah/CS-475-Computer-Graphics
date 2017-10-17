#include "./scene.hpp"

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

	float l, m, n;
	fscanf (fp_input, "%f %f %f", &l, &m, &n);
	cam.look_at = glm::vec3(l - a, m - b, n - c);

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

	glm::vec3 avg = glm::vec3(0.0f);
	for(int i = 0; i < 8 ; i++){
		avg += cam.frustum.vertex_list[i].position;
	}
	avg = avg/8.0f;


	glm::vec4 myavg = glm::vec4(glm::vec3(0.0f, 0.0f, -1.8f), 1.0f);

	glm::mat4 temp = scene.A_ndcs_dcs * scene.A_ccs_ndcs * scene.A_vcs_ccs * scene.A_wcs_vcs; 

	glm::mat4 pointmat = scene.A_vcs_ccs;

	printf("%f %f %f %f the point1\n", myavg.x, myavg.y, myavg.z, myavg.w);

	myavg = pointmat * myavg ; 

	printf("%f %f %f %f the point2\n", myavg.x, myavg.y, myavg.z, myavg.w);

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

	glm::vec4 row1 = glm::vec4(u, 0.0f);
	glm::vec4 row2 = glm::vec4(v, 0.0f);
	glm::vec4 row3 = glm::vec4(n, 0.0f);
	glm::vec4 row4 = glm::vec4(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);

 	A_wcs_vcs = glm::transpose(glm::mat4(row1, row2, row3, row4));
 	A_wcs_vcs =  A_wcs_vcs * glm::translate(glm::mat4(1.0f), -cam.eye_position);
 	reverse_vcs = glm::inverse(A_wcs_vcs);
}

/**
 * @brief      Calculates the A_vcs_ccs matrix from L,R,T,B,N,F values.
 */
void Scene::calc_VCS_CCS() {
	glm::mat4 sh = glm::mat4(1.0f);
	sh[2][0] = (cam.R + cam.L) / (-2.0 * cam.N);
	sh[2][1] = (cam.T + cam.B) / (-2.0 * cam.N);

	glm::mat4 sc = glm::mat4(1.0f);
	sc[0][0] = (2.0 * cam.N) / (cam.R - cam.L);
	sc[1][1] = (2.0 * cam.N) / (cam.T - cam.B);

	glm::mat4 Nm = glm::mat4(1.0f);
	Nm[2][2] = -(cam.F + cam.N) / (cam.F - cam.N);
	Nm[2][3] = -1.0f;
	Nm[3][2] = (-2.0 * cam.F * cam.N) / (cam.F - cam.N);
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
