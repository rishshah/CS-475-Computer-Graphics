#include "model.hpp"

const std::string FILE_NAME = "./models/";

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
	scale_vec = next_scale_vec = glm::vec3(x, y, z);
	scale_mtx = glm::scale(glm::mat4(1.0f), scale_vec); 

	//rotation
	fscanf(fp_input, "%f %f %f", &x, &y, &z);
	rotation_vec = glm::vec3(x, y, z);
	next_rotation_vec = rotation_vec;

	//joint rotation constraints
	fscanf(fp_input, "%f %f %f", &x, &y, &z);
	rotation_lim_base = glm::vec3(x, y, z);
	fscanf(fp_input, "%f %f %f", &x, &y, &z);
	rotation_lim_top = glm::vec3(x, y, z);

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
 * @param params 				Opengl location of important variables in shaders
 * @param light_flag 			spotlight on/off status
 * @param par_final_transform 	matrix accounting for parent model rotation and translation
 * @param projection_transform  projection perspective matrix of inital setup camera
 * @param half_third_person 	Only camera movements matrix
 * @param third_person_transform camera movements * heirarchial initial setup matrix
 */
void Model::draw(OpenglParams* params, int light_flag, glm::mat4 par_final_transform, glm::mat4 projection_transform, glm::mat4 half_third_person, glm::mat4 third_person_transform, float interpolation_factor) {

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindTexture(GL_TEXTURE_2D, tex);

	glVertexAttribPointer(params->vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0) );
	glVertexAttribPointer(params->vColor, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(glm::vec3)) );
	glVertexAttribPointer(params->vNormal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(2 * sizeof(glm::vec3)));
	glVertexAttribPointer(params->vTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(3 * sizeof(glm::vec3)));

	glm::mat4 par_translation_transform = glm::translate(glm::mat4(1.0f), par_translation_vec);
	glm::mat4 self_translation_transform = glm::translate(glm::mat4(1.0f), self_translation_vec);

	glm::mat4 rotation_mtx_x = glm::rotate( glm::mat4(1.0f), glm::radians(float(rotation_vec.x + interpolation_factor * (next_rotation_vec.x - rotation_vec.x))), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotation_mtx_y = glm::rotate( glm::mat4(1.0f), glm::radians(float(rotation_vec.y + interpolation_factor * (next_rotation_vec.y - rotation_vec.y))), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotation_mtx_z = glm::rotate( glm::mat4(1.0f), glm::radians(float(rotation_vec.z + interpolation_factor * (next_rotation_vec.z - rotation_vec.z))), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 rotation_matrix = rotation_mtx_z * rotation_mtx_y * rotation_mtx_x;

	scale_mtx = glm::scale(glm::mat4(1.0f), scale_vec + interpolation_factor * (next_scale_vec - scale_vec));

	glm::mat4 modelling_transform = par_translation_transform  * rotation_matrix * glm::inverse(self_translation_transform);
	glm::mat4 temp_matrix = projection_transform * third_person_transform * par_final_transform *  modelling_transform * scale_mtx;

	glUniformMatrix4fv(params->uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(temp_matrix));
	glUniformMatrix4fv(params->uViewMatrix, 1, GL_FALSE, glm::value_ptr(projection_transform));

	glm::mat3 normal_mat = glm::transpose( glm::inverse( glm::mat3(temp_matrix)));

	glUniformMatrix3fv(params->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normal_mat));

	glm::mat4 mult_mat = half_third_person;

	glUniformMatrix4fv(params->multMatrix, 1, GL_FALSE, glm::value_ptr(mult_mat));

	glUniform1i(params->uIs_tp, tex == -1 ? 0 : 1);
	glUniform1i(params->uLight_flag, light_flag);


	glDrawArrays(GL_TRIANGLES, 0, vertex_list.size());

	for (int i = 0; i < child_model_list.size(); ++i) {
		child_model_list[i]->draw(params, light_flag, par_final_transform * modelling_transform,
		                          projection_transform, half_third_person, third_person_transform, interpolation_factor);
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
}

/**
 * @brief Load next key frame part in memory of model to get interpolation information
 * 
 * @param fp keyframe file pointer
 */
void Model::load_next_keyframe(FILE* fp) {
	printf("%.2f %.2f %.2f\n", scale_vec.x, scale_vec.y, scale_vec.z);
	printf("%.2f %.2f %.2f\n", next_scale_vec.x, next_scale_vec.y, next_scale_vec.z);
	printf("xxxx :: %s \n", id);
	scale_vec = next_scale_vec;	
	rotation_vec = next_rotation_vec;
	
	fscanf(fp, "%f ", &next_rotation_vec.x);
	fscanf(fp, "%f ", &next_rotation_vec.y);
	fscanf(fp, "%f ", &next_rotation_vec.z);

	fscanf(fp, "%f ", &next_scale_vec.x);
	fscanf(fp, "%f ", &next_scale_vec.y);
	fscanf(fp, "%f ", &next_scale_vec.z);

	for (int i = 0; i < child_model_list.size(); ++i) {
		child_model_list[i]->load_next_keyframe(fp);
	}
}

/**
 * @brief save current keyframe part for this model
 * 
 * @param fp keyframe file pointer
 */
void Model::save_keyframe(FILE* fp) {
	// fprintf(fp, "%s-Rx ", id);
	// fprintf(fp, "%s-Ry ", id);
	// fprintf(fp, "%s-Rz ", id);
	
	// fprintf(fp, "%s-Sx ", id);
	// fprintf(fp, "%s-Sy ", id);
	// fprintf(fp, "%s-Sz ", id);

	fprintf(fp, "%.2f ", rotation_vec.x);
	fprintf(fp, "%.2f ", rotation_vec.y);
	fprintf(fp, "%.2f ", rotation_vec.z);

	fprintf(fp, "%.2f ", scale_vec.x);
	fprintf(fp, "%.2f ", scale_vec.y);
	fprintf(fp, "%.2f ", scale_vec.z);


	for (int i = 0; i < child_model_list.size(); ++i) {
		child_model_list[i]->save_keyframe(fp);
	}
}


/**
 * @brief Destructor to deallocate child models recursively
 */
Model::~Model() {
	for (int i = 0; i < child_model_list.size(); ++i) {
		delete child_model_list[i];
	}
}