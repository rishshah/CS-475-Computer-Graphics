#ifndef _HEIRARCHICAL_MODEL_HPP_
#define _HEIRARCHICAL_MODEL_HPP_

#include "./global.hpp"
#include "./openglParams.hpp"
#include "./model.hpp"

/**
 * @brief      Class for complete heirarchical model independent of others.
 */
class HeirarchicalModel : public Model {
private:
	const float TRANS_DELTA = 0.2;
	
	float xpos = 0.0, ypos = 0.0, zpos = 0.0;
	float xscale = 1.0, yscale = 1.0, zscale = 1.0;

	glm::mat4 translation_matrix = glm::mat4(1.0f);
	glm::mat4 rotation_matrix = glm::mat4(1.0f);
	glm::mat4 scaling_matrix = glm::mat4(1.0f);
	
public:
	std::string hm_id;
	HeirarchicalModel();
	HeirarchicalModel(std::string id, glm::vec3 scale_vec, glm::vec3 translation_vec);
	void draw_hm(OpenglParams* params, int, glm::mat4, glm::mat4);
	void translate(std::vector<bool> key_state_translation, bool key_state_recenter);
};

#endif