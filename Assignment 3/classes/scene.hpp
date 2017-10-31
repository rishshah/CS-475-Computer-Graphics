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

	const float field_of_view = 60.0f;
	const float aspect_ratio = 1.0f;
	const float near_plane = 0.1f;
	const float far_plane = 1000.0f;

	const glm::vec3 eye_position = glm::vec3(0.0f, 2.0f, 5.0f);
	const glm::vec3 lookat_center = glm::vec3(0.0f, 0.0f, 0.0f);
	const glm::vec3 up =  glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 projection_transform;

	GLuint vao = 0;
	GLuint vPosition, vColor, vNormal, vTexCoord;
	GLuint uModelViewMatrix, uIs_tp, uNormalMatrix, uViewMatrix, multMatrix;

	glm::mat4 translation_matrix = glm::mat4(1.0f);
	glm::mat4 rotation_matrix = glm::mat4(1.0f);
	glm::mat4 scaling_matrix = glm::mat4(1.0f);

public:
	std::vector<HeirarchicalModel*> model_list;

	void init();
	void load_new_model(std::string filename, std::string id, glm::vec3 scale_vec, glm::vec3 translation_vec);
	void draw();
	HeirarchicalModel* find_heirarchical_model_by_id(std::string id);

	void rotate(std::vector<bool> key_state_rotation);
	void translate(std::vector<bool> key_state_translation, bool key_state_recenter);
	~Scene();
};

#include "../main.hpp"

extern Scene scene;

#endif