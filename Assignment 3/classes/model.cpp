#include "model.hpp"

const std::string FILE_NAME = "./models/";

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
 *
 * @param filename 	the .raw file that contains the model
 * @param hm_id 	the heirarchical model id (folder name)
 * @param par_scale_mtx  scaling matrix of parent for calculation of par_relative translation
 * @return true iff file loaded successfully
 */
bool Model::load(std::string hm_id, std::string filename, glm::mat4 par_scale_mtx ) {
	FILE *fp_input = fopen(filename.c_str(), "r" );
	if (fp_input ==  NULL) {
		printf("Error opening file %s\n", filename.c_str());
		return false;
	}

	int num_vertices, num_children, is_texture_present = -1;
	fscanf (fp_input, "%s", id);

	float x, y, z;

	//scale
	fscanf(fp_input, "%f %f %f", &x, &y, &z);
	scale_vec = glm::vec3(x, y, z);

	//rotation
	fscanf(fp_input, "%f %f %f", &x, &y, &z);
	rotation_vec = glm::vec3(x, y, z);

	//joint rotation constraints
	fscanf(fp_input, "%f %f %f", &x, &y, &z);
	rotation_lim_base = glm::vec3(x, y, z);
	fscanf(fp_input, "%f %f %f", &x, &y, &z);
	rotation_lim_top = glm::vec3(x, y, z);

	calc_matrices();

	//par_translation
	fscanf(fp_input, "%f %f %f", &x, &y, &z);
	par_translation_vec = glm::vec3(par_scale_mtx * glm::vec4(x, y, z, 1.0f));

	//self_translation
	fscanf(fp_input, "%f %f %f", &x, &y, &z);
	self_translation_vec = glm::vec3(scale_mtx * glm::vec4(x, y, z, 1.0f));

	//children models
	fscanf (fp_input, "%d", &num_children);
	child_model_list.resize(num_children);
	for (int i = 0; i < num_children; ++i) {
		char child_filename[100];
		fscanf(fp_input, "%s\n", child_filename);
		child_model_list[i] = new Model;
		child_model_list[i]->load(hm_id, FILE_NAME + hm_id + "/" + std::string(child_filename) + ".raw", scale_mtx);
		child_model_list[i]->assignBuffer();
	}

	//texture dependent file vertices read
	fscanf (fp_input, "%d", &is_texture_present);
	fscanf (fp_input, "%d", &num_vertices);
	vertex_list.resize(num_vertices);
	if (is_texture_present == 1) {
		char texture_filename[30]; fscanf (fp_input, "%s", texture_filename);
		tex = LoadTexture(texture_filename, 256, 256);
		for (int i = 0; i < num_vertices; ++i) {
			float vx, vy, vz, tx, ty;
			fscanf(fp_input, "%f %f %f %f %f", &vx, &vy, &vz, &tx, &ty);
			Vertex v;
			v.position = glm::vec3(vx, vy, vz);
			v.texture = glm::vec2(tx, ty);
			v.normal = v.position;
			vertex_list[i] = v;
			if (i % 3 == 2) {
				glm::vec3 vec1 = vertex_list[i - 2].position - vertex_list[i - 1].position;
				glm::vec3 vec2 = vertex_list[i].position - vertex_list[i - 1].position;
				glm::vec3 crossproduct = glm::cross(vec1, vec2);
				vertex_list[i - 2].normal = crossproduct;
				vertex_list[i - 1].normal = crossproduct;
				vertex_list[i].normal = crossproduct;
			}

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
			v.normal = v.position;
			vertex_list[i] = v;
			if (i % 3 == 2) {
				glm::vec3 vec1 = vertex_list[i - 2].position - vertex_list[i - 1].position;
				glm::vec3 vec2 = vertex_list[i].position - vertex_list[i - 1].position;
				glm::vec3 crossproduct = glm::cross(vec1, vec2);
				vertex_list[i - 2].normal = crossproduct;
				vertex_list[i - 1].normal = crossproduct;
				vertex_list[i].normal = crossproduct;
			}
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
 * @brief draw the model on the screen
 * 
 * @param vPosition 			shader reference to vPosition variable
 * @param vColor 				shader reference to vColor variable
 * @param vNormal 				shader reference to vNormal variable
 * @param vTexCoord 			shader reference to vTexCoord variable
 * @param uModelViewMatrix 		shader reference to uModelViewMatrix variable
 * @param uNormalMatrix 		shader reference to uNormalMatrix variable
 * @param uViewMatrix 			shader reference to uViewMatrix variable
 * @param multMatrix 			shader reference to multMatrix variable
 * @param uIs_tp 				shader reference to uIs_tp variable
 * @param uLight_flag 			shader reference to uLight_flag variable
 * @param light_flag 			spotlight on/off status
 * @param par_final_transform 	matrix accounting for parent model rotation and translation
 * @param projection_transform  projection perspective matrix of inital setup camera
 * @param half_third_person 	Only camera movements matrix
 * @param third_person_transform camera movements * heirarchial initial setup matrix
 */
void Model::draw(GLuint vPosition, GLuint vColor, GLuint vNormal, GLuint vTexCoord, GLuint uModelViewMatrix,
                 GLuint uNormalMatrix, GLuint uViewMatrix, GLuint multMatrix, GLuint uIs_tp, GLuint uLight_flag, int light_flag, glm::mat4 par_final_transform,
                 glm::mat4 projection_transform, glm::mat4 half_third_person, glm::mat4 third_person_transform) {

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindTexture(GL_TEXTURE_2D, tex);

	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0) );
	glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(glm::vec3)) );
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(2 * sizeof(glm::vec3)));
	glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(3 * sizeof(glm::vec3)));

	glm::mat4 par_translation_transform = glm::translate(glm::mat4(1.0f), par_translation_vec);
	glm::mat4 self_translation_transform = glm::translate(glm::mat4(1.0f), self_translation_vec);

	glm::mat4 modelling_transform = par_translation_transform  * rotation_mtx * glm::inverse(self_translation_transform);
	glm::mat4 temp_matrix = projection_transform * third_person_transform * par_final_transform *  modelling_transform * scale_mtx;

	glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(temp_matrix));
	glUniformMatrix4fv(uViewMatrix, 1, GL_FALSE, glm::value_ptr(projection_transform));

	glm::mat3 normal_mat = glm::transpose( glm::inverse( glm::mat3(temp_matrix)));

	glUniformMatrix3fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normal_mat));

	glm::mat4 mult_mat = half_third_person;

	glUniformMatrix4fv(multMatrix, 1, GL_FALSE, glm::value_ptr(mult_mat));

	glUniform1i(uIs_tp, tex == -1 ? 0 : 1);
	glUniform1i(uLight_flag, light_flag);


	glDrawArrays(GL_TRIANGLES, 0, vertex_list.size());

	for (int i = 0; i < child_model_list.size(); ++i) {
		child_model_list[i]->draw(vPosition, vColor, vNormal, vTexCoord, uModelViewMatrix, uNormalMatrix,
		                          uViewMatrix, multMatrix, uIs_tp, uLight_flag, light_flag,
		                          par_final_transform * modelling_transform,
		                          projection_transform, half_third_person, third_person_transform);
	}
}

/**
 * @brief get in heirarchy model pointer by id 
 * @return pointer to found model part
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
 * //X     0 -> Up     1 -> Down
 * //Y     2 -> Left   3 -> Right
 * //Z     4 -> pgUp   5 -> PgDown
 */
void Model::rotate(std::vector<bool> key_state_rotation) {
	if (key_state_rotation[0]) {
		rotation_vec.x = std::max(rotation_lim_base.x, rotation_vec.x - ROT_DELTA);
	}
	else if (key_state_rotation[1]) {
		rotation_vec.x = std::min(rotation_lim_top.x, rotation_vec.x + ROT_DELTA);
	}

	if (key_state_rotation[2]) {
		rotation_vec.y = std::max(rotation_lim_base.y, rotation_vec.y - ROT_DELTA);
	}
	else if (key_state_rotation[3]) {
		rotation_vec.y = std::min(rotation_lim_top.y, rotation_vec.y + ROT_DELTA);
	}

	if (key_state_rotation[4]) {
		rotation_vec.z = std::min(rotation_lim_top.z, rotation_vec.z + ROT_DELTA);
	}
	else if (key_state_rotation[5]) {
		rotation_vec.z = std::max(rotation_lim_base.z, rotation_vec.z - ROT_DELTA);
	}

	glm::mat4 rotation_mtx_x = glm::rotate( glm::mat4(1.0f), glm::radians(rotation_vec.x), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotation_mtx_y = glm::rotate( glm::mat4(1.0f), glm::radians(rotation_vec.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotation_mtx_z = glm::rotate( glm::mat4(1.0f), glm::radians(rotation_vec.z), glm::vec3(0.0f, 0.0f, 1.0f));
	rotation_mtx = rotation_mtx_z * rotation_mtx_y * rotation_mtx_x;
}

/**
 * @brief Destructor to deallocate child models recursively
 */
Model::~Model() {
	for (int i = 0; i < child_model_list.size(); ++i) {
		delete child_model_list[i];
	}
}