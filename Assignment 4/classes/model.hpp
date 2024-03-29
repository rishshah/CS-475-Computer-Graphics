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
	
	glm::vec3 scale_vec, next_scale_vec;
	glm::vec3 rotation_vec, next_rotation_vec;

	glm::mat4 scale_mtx;
	
	GLuint vbo, tex;
	void assignBuffer();
	void calc_rotation_mtx();

public:

	bool load(std::string id, std::string filename, glm::mat4 scale_mtx);
	void save_keyframe(FILE* fp);
	void load_next_keyframe(FILE* fp);
	void draw(OpenglParams* params, int, glm::mat4, glm::mat4, glm::mat4, glm::mat4, float);
	Model* find_by_id(std::string id);
	void rotate(std::vector<bool> key_state_rotation);
	void reload_last_keyframe();
	~Model();
};
#endif
