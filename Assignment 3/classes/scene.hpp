#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include "./model.hpp"

/**
 * @brief      Class for storing the entire scene data.
 */
class Scene {
public:
	std::vector<Model> model_list;
	GLuint vao = 0;
	GLuint vPosition, vColor, uModelViewMatrix;

	void init();
	void load_new_model(std::	string filename);
	void save_model(int i);
	void draw(glm::mat4 third_person_transform, glm::mat4 projection_transform);
};

#include "../main.hpp"

extern Scene scene;

#endif