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

	// float a, b, c;
	// fscanf (fp_input, "%f %f %f", &a, &b, &c);
	// cam.eye_position = glm::vec3(a, b, c);

	// float l, m, n;
	// fscanf (fp_input, "%f %f %f", &l, &m, &n);
	// cam.look_at = glm::vec3(l - a, m - b, n - c);

	// fscanf (fp_input, "%f %f %f", &a, &b, &c);
	// cam.up = glm::vec3(a, b, c);

	// fscanf (fp_input, "%f %f %f %f", &cam.L, &cam.R, &cam.T, &cam.B);
	// fscanf (fp_input, "%f %f", &cam.N, &cam.F);
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
	for (int i = 0; i < 3; ++i){
			model_list[i].m.draw(vPosition, vColor, uModelViewMatrix, GL_TRIANGLES, 
				third_person_transform * model_list[i].transformation_mtx);
	}
}
