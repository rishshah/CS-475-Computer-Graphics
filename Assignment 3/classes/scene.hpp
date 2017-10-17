#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include "./model.hpp"

/**
 * @brief      Class for storing the entire scene data.
 */
class Scene {
public:

	std::vector<WorldModel> model_list;

	GLuint vao = 0;
	GLuint vPosition, vColor, uModelViewMatrix;

	bool load();

	void draw(glm::mat4 transformation_mtx);
};

#include "../main.hpp"

extern Scene scene;

#endif