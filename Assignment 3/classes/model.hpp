#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "../global.hpp"
#include "./vertex.hpp"
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
	glm::mat4 rotation_mtx, scale_mtx;

	GLuint vbo, tex;
	void assignBuffer();
	void calc_matrices();

public:

	glm::vec3 scale_vec, rotation_vec;
	bool load(std::string id, std::string filename, glm::mat4 scale_mtx);
	void draw(GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, int, glm::mat4, glm::mat4, glm::mat4);
	Model* find_by_id(std::string id);
	void rotate(std::vector<bool> key_state_rotation);
	~Model();
};

/**
 * @brief      Class for complete heirarchical model independent of others.
 */
class HeirarchicalModel : public Model {
public:
	std::string hm_id;
	float xpos = 0.0, ypos = 0.0, zpos = 0.0;
	float xscale = 1.0, yscale = 1.0, zscale = 1.0;

	glm::mat4 translation_matrix = glm::mat4(1.0f);
	glm::mat4 rotation_matrix = glm::mat4(1.0f);
	glm::mat4 scaling_matrix = glm::mat4(1.0f);
};

#endif
