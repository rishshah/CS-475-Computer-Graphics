#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "../global.hpp"
#include "./vertex.hpp"
#include "./openglParams.hpp"

#include "../utils/texture_utils.hpp"
#include <algorithm>

/**
 * @brief      Class for a generic model or model part.
 */
class Model {
private:
	const float ROT_DELTA = 0.5f;

	char id[100];
	std::vector<Vertex> vertex_list;
	std::vector<Model*> child_model_list;

	glm::vec3 par_translation_vec, self_translation_vec;
	
	glm::vec3 rotation_lim_base, rotation_lim_top;

	glm::vec3 scale_vec, rotation_vec;
	glm::mat4 scale_mtx, rotation_mtx;
	
	GLuint vbo, tex;
	void assignBuffer();
	void calc_matrices();

public:

	bool load(std::string id, std::string filename, glm::mat4 scale_mtx);
	void draw(OpenglParams* params, int, glm::mat4, glm::mat4, glm::mat4, glm::mat4);
	Model* find_by_id(std::string id);
	void rotate(std::vector<bool> key_state_rotation);
	~Model();
};
#endif
