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
 * @param      filename the .raw file that contains the model
 *
 * @return     true iff file loaded successfully
 */
bool Model::load(std::string hm_id, std::string filename, glm::vec3 cumu_translation, glm::mat4 par_rotation_mtx, glm::mat4 par_scale_mtx) {
	FILE *fp_input = fopen(filename.c_str(), "r" );
	if (fp_input ==  NULL) {
		printf("Error opening file %s\n", filename.c_str());
		return false;
	}

	int num_vertices, num_children;
	fscanf (fp_input, "%s", id);
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
	par_translation_vec = glm::vec3(par_rotation_mtx * par_scale_mtx * glm::vec4(x, y, z, 1.0f));

	//self_translation
	fscanf(fp_input, "%f %f %f", &x, &y, &z);
	self_translation_vec = glm::vec3(rotation_mtx * scale_mtx * glm::vec4(x, y, z, 1.0f));

	//final_translation
	final_translation_vec = par_translation_vec - self_translation_vec + cumu_translation;

	child_model_list.resize(num_children);
	for (int i = 0; i < num_children; ++i) {
		char child_filename[100];
		fscanf(fp_input, "%s\n", child_filename);
		child_model_list[i] = new Model;
		child_model_list[i]->load(hm_id, FILE_NAME + hm_id + "/" + std::string(child_filename) + ".raw", final_translation_vec, rotation_mtx, scale_mtx);
		child_model_list[i]->assignBuffer();
	}

	vertex_list.resize(num_vertices);
	for (int i = 0; i < num_vertices; ++i) {
		float vx, vy, vz, cx, cy, cz;
		fscanf(fp_input, "%f %f %f %f %f %f", &vx, &vy, &vz, &cx, &cy, &cz);
		Vertex v;
		v.position = glm::vec3(vx, vy, vz);
		v.color = glm::vec3(cx, cy, cz);
		vertex_list[i] = v;
	}
	assignBuffer();
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
 * @param[in]  mode              The mode of drawing the model (GL_TRIANGLES, GL_LINES, GL_POINT)
 * @param[in]  third_person_transform 	transformation matrix from ouside of this model
 * @param[in]  projection_transform  	Matrix of projection from third person (scene) camera
 */
void Model::draw(GLuint vPosition, GLuint vColor, GLuint uModelViewMatrix, GLenum mode, glm::mat4 third_person_transform,  glm::mat4 projection_transform) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0) );
	glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(glm::vec3)) );

	glm::mat4 final_translation_transform = glm::translate(glm::mat4(1.0f), final_translation_vec);
	glm::mat4 self_translation_transform = glm::translate(glm::mat4(1.0f), self_translation_vec);
	glm::mat4 modelling_transform = self_translation_transform * rotation_mtx * glm::inverse(self_translation_transform) * scale_mtx;
	glm::mat4 temp_matrix = projection_transform * third_person_transform * final_translation_transform * modelling_transform;
	glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(temp_matrix));

	glDrawArrays(mode, 0, vertex_list.size());

	for (int i = 0; i < child_model_list.size(); ++i) {
		child_model_list[i]->draw(vPosition, vColor, uModelViewMatrix, mode, third_person_transform * final_translation_transform * 
			self_translation_transform * rotation_mtx * glm::inverse(self_translation_transform) * glm::inverse(final_translation_transform),
			projection_transform);
	}
}

/**
 * @brief get in heirarchy model pointer by id
 * 
 * @param id [description]
 * @return [description]
 */
Model* Model::find_by_id(std::string id){
	if(std::string(this->id) == id)
		return this;
	for (int i = 0; i < child_model_list.size(); ++i){
		Model* m = child_model_list[i]->find_by_id(id);
		if(m != NULL)
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

Model::~Model(){
	for (int i = 0; i < child_model_list.size(); ++i){
		delete child_model_list[i];
	}
}