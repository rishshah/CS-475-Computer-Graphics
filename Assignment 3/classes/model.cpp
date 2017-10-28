#include "model.hpp"

const std::string FILE_NAME = "./models/";
void print(std::string s, glm::vec3 v) {
	printf("%s :%f %f %f\n", s.c_str(), v.x, v.y, v.z);
};

void printmat4(glm::mat4 Awv) {
	printf("\n");
	printf("%f, %f, %f, %f \n", Awv[0][0], Awv[1][0], Awv[2][0], Awv[3][0]);
	printf("%f, %f, %f, %f \n", Awv[0][1], Awv[1][1], Awv[2][1], Awv[3][1]);
	printf("%f, %f, %f, %f \n", Awv[0][2], Awv[1][2], Awv[2][2], Awv[3][2]);
	printf("%f, %f, %f, %f \n", Awv[0][3], Awv[1][3], Awv[2][3], Awv[3][3]);
	printf("\n");
}

/**
 * @brief calculate rotation and scale matrix for each part corresponding to file's rotation and scale vector inputs
 */
void Model::calc_matrices() {
	glm::mat4 rotation_mtx_x = glm::rotate( glm::mat4(1.0f), glm::radians(rotation_vec.x), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotation_mtx_y = glm::rotate( glm::mat4(1.0f), glm::radians(rotation_vec.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotation_mtx_z = glm::rotate( glm::mat4(1.0f), glm::radians(rotation_vec.z), glm::vec3(0.0f, 0.0f, 1.0f));
	rotation_mtx = rotation_mtx_z * rotation_mtx_y * rotation_mtx_x;
	scale_mtx = glm::scale(glm::mat4(1.0f), scale_vec);
}

/**
 * @brief      Load model from a .raw file  and store its vertex data
 * @param      filename the .raw file that contains the model
 *
 * @return     true iff file loaded successfully
 */
bool Model::load(std::string hm_id, std::string filename, glm::mat4 par_scale_mtx ) {
	FILE *fp_input = fopen(filename.c_str(), "r" );
	if (fp_input ==  NULL) {
		printf("Error opening file %s\n", filename.c_str());
		return false;
	}

	int num_vertices, num_children, is_texture_present = -1;
	fscanf (fp_input, "%s", id);
	// fscanf (fp_input, "%d", &is_texture_present);
	fscanf (fp_input, "%d", &num_children);
	fscanf (fp_input, "%d", &num_vertices);

	float x, y, z;

	//scale
	fscanf(fp_input, "%f %f %f", &x, &y, &z);
	scale_vec = glm::vec3(x, y, z);

	//rotation
	fscanf(fp_input, "%f %f %f", &x, &y, &z);
	rotation_vec = glm::vec3(x, y, z);

	calc_matrices();
	//par_translation
	fscanf(fp_input, "%f %f %f", &x, &y, &z);
	par_translation_vec = glm::vec3(par_scale_mtx * glm::vec4(x, y, z, 1.0f));

	//self_translation
	fscanf(fp_input, "%f %f %f", &x, &y, &z);
	self_translation_vec = glm::vec3(scale_mtx * glm::vec4(x, y, z, 1.0f));

	child_model_list.resize(num_children);
	for (int i = 0; i < num_children; ++i) {
		char child_filename[100];
		fscanf(fp_input, "%s\n", child_filename);
		child_model_list[i] = new Model;
		child_model_list[i]->load(hm_id, FILE_NAME + hm_id + "/" + std::string(child_filename) + ".raw", scale_mtx);
		child_model_list[i]->assignBuffer();
	}

	vertex_list.resize(num_vertices);
	if (is_texture_present == 1) {
		char texture_filename[30]; fscanf (fp_input, "%s", texture_filename);
		tex = LoadTexture(texture_filename, 256, 256);
		glBindTexture(GL_TEXTURE_2D, tex);
		for (int i = 0; i < num_vertices; ++i) {
			float vx, vy, vz, cx, cy, cz, tx, ty;
			fscanf(fp_input, "%f %f %f %f %f %f %f %f", &vx, &vy, &vz, &cx, &cy, &cz, &tx, &ty);
			Vertex v;
			v.position = glm::vec3(vx, vy, vz);
			v.color = glm::vec3(cx, cy, cz);
			v.texture = glm::vec2(tx, ty);
			vertex_list[i] = v;
		}
	} else {
		tex = -1;
		for (int i = 0; i < num_vertices; ++i) {
			float vx, vy, vz, cx, cy, cz;
			fscanf(fp_input, "%f %f %f %f %f %f", &vx, &vy, &vz, &cx, &cy, &cz);
			Vertex v;
			v.position = glm::vec3(vx, vy, vz);
			v.color = glm::vec3(cx, cy, cz);
			v.texture = glm::vec2(0, 0);
			vertex_list[i] = v;
		}
	}
	assignBuffer();
	fclose(fp_input);
	return true;
}

/**
 * @brief      fill the vbo for the model
 */
void Model::assignBuffer() {
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData (GL_ARRAY_BUFFER, vertex_list.size() * sizeof(Vertex), &vertex_list[0], GL_STATIC_DRAW);
}

/**
 * @brief      draw model on screen
 *
 * @param[in]  vPosition         location of position input in vertex shader
 * @param[in]  vColor            location of color input in vertex shader
 * @param[in]  uModelViewMatrix  location of transformation matrix input in vertex shader
 * @param[in]  mode              The mode of drawing the model (GL_TRIANGLES, GL_LINES, GL_POINT)
 * @param[in]  third_person_transform 	transformation matrix from ouside of this model
 * @param[in]  projection_transform  	Matrix of projection from third person (scene) camera
 */
void Model::draw(GLuint vPosition, GLuint vColor, GLuint vTexCoord, GLuint uModelViewMatrix, GLuint uIs_tp, glm::mat4 par_final_transform,
                 glm::mat4 third_person_transform) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0) );
	glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(glm::vec3)) );
	glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(2 * sizeof(glm::vec3)));

	glm::mat4 par_translation_transform = glm::translate(glm::mat4(1.0f), par_translation_vec);
	glm::mat4 self_translation_transform = glm::translate(glm::mat4(1.0f), self_translation_vec);

	glm::mat4 modelling_transform = par_translation_transform  * rotation_mtx * glm::inverse(self_translation_transform);
	glm::mat4 temp_matrix = third_person_transform * par_final_transform *  modelling_transform * scale_mtx;
	glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(temp_matrix));
	glUniform1i(uIs_tp, tex == -1 ? 0 : 1);

	glDrawArrays(GL_TRIANGLES, 0, vertex_list.size());

	for (int i = 0; i < child_model_list.size(); ++i) {
		child_model_list[i]->draw(vPosition, vColor, vTexCoord, uModelViewMatrix, uIs_tp,
		                          par_final_transform * modelling_transform,
		                          third_person_transform);
	}
}

/**
 * @brief get in heirarchy model pointer by id
 *
 * @param id [description]
 * @return [description]
 */
Model* Model::find_by_id(std::string id) {
	if (std::string(this->id) == id)
		return this;
	for (int i = 0; i < child_model_list.size(); ++i) {
		Model* m = child_model_list[i]->find_by_id(id);
		if (m != NULL)
			return m;
	}
	return NULL;
}

/**
 * @brief recalculate rotation matrix of model in scene
 * @param i 					model index in model_list of scene
 * @param key_state_rotation 	key press boolean vector input
 */
void Model::rotate(std::vector<bool> key_state_rotation) {
	if (key_state_rotation[0]) {
		rotation_mtx = glm::rotate(rotation_mtx, -ROT_DELTA, glm::vec3(glm::transpose(rotation_mtx) * X_UNIT));
	}
	else if (key_state_rotation[1]) {
		rotation_mtx = glm::rotate(rotation_mtx, ROT_DELTA, glm::vec3(glm::transpose(rotation_mtx) * X_UNIT));
	}

	if (key_state_rotation[2]) {

		rotation_mtx = glm::rotate(rotation_mtx, -ROT_DELTA, glm::vec3(glm::transpose(rotation_mtx) * Y_UNIT));
	}
	else if (key_state_rotation[3]) {
		rotation_mtx = glm::rotate(rotation_mtx, ROT_DELTA, glm::vec3(glm::transpose(rotation_mtx) * Y_UNIT));
	}

	if (key_state_rotation[4]) {
		rotation_mtx = glm::rotate(rotation_mtx, ROT_DELTA, glm::vec3(glm::transpose(rotation_mtx) * Z_UNIT));
	}
	else if (key_state_rotation[5]) {
		rotation_mtx = glm::rotate(rotation_mtx, -ROT_DELTA, glm::vec3(glm::transpose(rotation_mtx) * Z_UNIT));
	}
}

Model::~Model() {
	for (int i = 0; i < child_model_list.size(); ++i) {
		delete child_model_list[i];
	}
}