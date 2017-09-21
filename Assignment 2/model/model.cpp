#include "model.hpp"


/**
 * @brief      Loads the model stored in model.raw by default in  X Y Z R G B format
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
 * @brief      Assigns vertex list to the vertex buffer object and corresponding
 *             shader file attributes.
 *
 * @param      vPosition  The vertex_list positions
 * @param      vColor     The vertex_list colors
 */
void Model::assignBuffer(GLuint &vPosition, GLuint &vColor) {
	size_t size_points = vertex_list.size() * sizeof (glm::vec3);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData (GL_ARRAY_BUFFER, size_points * 2, &vertex_list[0], GL_STATIC_DRAW);
}

void WorldModel::calc_modelling_transformation() {
	glm::mat4 scaled_mtx = glm::scale(glm::mat4(1.0f), scale_vec);

	glm::mat4 rotation_mtx = glm::rotate( glm::mat4(1.0f), rotation_vec.x, glm::vec3(1.0f, 0.0f, 0.0f));
	rotation_mtx = glm::rotate( rotation_mtx, rotation_vec.y, glm::vec3(0.0f, 1.0f, 0.0f));
	rotation_mtx = glm::rotate( rotation_mtx, rotation_vec.z, glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 translation_mtx = glm::translate(glm::mat4(1.0f), position_vec);

	transformation_mtx = translation_mtx * rotation_mtx * scaled_mtx;
}

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
		worldModel.m.assignBuffer(vPosition, vColor);

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

	fclose(fp_input);
	return true;
}

void Scene::draw() {
	glBindVertexArray(vao);

	for (int i = 0; i < 3; ++i) {

		glBindBuffer(GL_ARRAY_BUFFER, model_list[i].m.vbo);
		glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0) );
		glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(glm::vec3)) );

		modelview_matrix = model_list[i].transformation_mtx;
		glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));

		glDrawArrays(GL_TRIANGLES, 0, scene.model_list[i].m.vertex_list.size());
	}
}