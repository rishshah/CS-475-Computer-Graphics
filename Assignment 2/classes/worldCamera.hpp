#ifndef _WCAM_HPP_
#define _WCAM_HPP_

#include "../global.hpp"
#include "./model.hpp"

/**
 * @brief      Class for camera, frustum and projectors postioned in world coordinate system.
 */
class WorldCamera {
public:
	glm::vec3 eye_position;
	glm::vec3 look_at;
	glm::vec3 up;

	float L, R, T, B, N, F;

	GLuint vao;
	GLuint vPosition, vColor, uModelViewMatrix;
	GLuint uNDCS;

	Model frustum, middle, eye;
	int display_eye = 1;

	void create_frustum();
	void draw(glm::mat4 transformation_mtx);
};

#endif