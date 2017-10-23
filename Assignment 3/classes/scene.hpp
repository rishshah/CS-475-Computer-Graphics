#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include "./model.hpp"

/**
 * @brief      Class for storing the entire scene data.
 */
class Scene {
private:
	// Translation  and Rotation Parameters
	const float TRANS_DELTA = 0.1;
	const float SCALE_DELTA = 0.02;
	const float ROT_DELTA = 0.05;

	const glm::vec4 X_UNIT = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	const glm::vec4 Y_UNIT = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	const glm::vec4 Z_UNIT = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	float xpos = 0.0, ypos = 0.0, zpos = 0.0;
	float xscale = 1.0, yscale = 1.0, zscale = 1.0;


	GLuint vao = 0;
	GLuint vPosition, vColor, uModelViewMatrix;

	glm::mat4 translation_matrix = glm::mat4(1.0f);
	glm::mat4 rotation_matrix = glm::mat4(1.0f);
	glm::mat4 scaling_matrix = glm::mat4(1.0f);

public:
	std::vector<HeirarchicalModel*> model_list;
	
	void init();
	void load_new_model(std::string filename, std::string id);
	void draw(glm::mat4 projection_transform);
	HeirarchicalModel* find_heirarchical_model_by_id(std::string id);

	void rotate(std::vector<bool> key_state_rotation);
	void trans_scale(std::vector<bool> key_state_trans_or_scale, bool key_state_recenter, bool key_state_scaling_mode);
	~Scene();
};

#include "../main.hpp"

extern Scene scene;

#endif