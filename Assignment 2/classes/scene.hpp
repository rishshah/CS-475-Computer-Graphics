#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include "./model.hpp"
#include "./axes.hpp"
#include "./worldCamera.hpp"

/**
 * @brief      Class for storing the entire scene data.
 */
class Scene {
public:

	std::vector<WorldModel> model_list;
	std::vector<WorldModel> clipped_model_list;
	WorldCamera cam;
	Axes axes;

	int should_clip = 0;

	GLuint vao = 0;
	GLuint vPosition, vColor, uModelViewMatrix;

	glm::mat4 dummy_matrix = glm::mat4(1.0f);
	glm::mat4 frustum_dummy_matrix = glm::mat4(1.0f);
	glm::mat4 reverse_vcs = glm::mat4(1.0f);
	
	glm::mat4 A_wcs_vcs = glm::mat4(1.0f);
	glm::mat4 A_vcs_ccs = glm::mat4(1.0f);
	glm::mat4 A_ccs_ndcs = glm::mat4(1.0f);
	glm::mat4 A_ndcs_dcs = glm::mat4(1.0f);

	int ndcs_divide = 0;
	GLuint uNDCS;
	
	glm::vec3 center;
	void calc_center();

	bool load();

	void draw(glm::mat4 transformation_mtx);

	void calc_WCS_VCS();

	void calc_VCS_CCS();

	void calc_CCS_NDCS();

	void calc_NDCS_DCS();
};

#include "../main.hpp"

extern Scene scene;

#endif