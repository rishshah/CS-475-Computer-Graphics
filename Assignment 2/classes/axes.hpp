#ifndef _AXES_HPP_
#define _AXES_HPP_

#include "../global.hpp"
#include "./model.hpp"
/**
 * @brief      Class for world coordinate system axes.
 */
class Axes {
public:

	Model m;
	glm::mat4 dummy_matrix = glm::mat4(1.0f);

	GLuint vao = 0;
	GLuint vPosition, vColor, uModelViewMatrix;
	GLuint uNDCS;


	void create_axes();
	void draw(glm::mat4 transformation_mtx);
};

#endif