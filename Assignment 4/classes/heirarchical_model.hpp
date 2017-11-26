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
	const float TRANS_DELTA = 0.05;
	float xpos = 0.0, ypos = 0.0, zpos = 0.0;
	float next_xpos = 0.0, next_ypos = 0.0, next_zpos = 0.0;

	glm::vec3 scale_vec, next_scale_vec;
	std::string hm_id;

public:
	std::string get_id();
	HeirarchicalModel();
	HeirarchicalModel(std::string id, glm::vec3 scale_vec, glm::vec3 translation_vec);
	void draw_hm(OpenglParams* params, int, glm::mat4, glm::mat4, float);
	void save_keyframe_hm(FILE* fp);
	void load_next_keyframe_hm(FILE* fp);
	void translate(std::vector<bool> key_state_translation);
};

#endif
