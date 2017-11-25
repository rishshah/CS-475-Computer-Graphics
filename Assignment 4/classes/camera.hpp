#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include "../global.hpp"
/**
 * @brief Class to store camera related constants and perspective projection
 */
class Camera {
private:
	const float field_of_view = 60.0f;
	const float aspect_ratio = 1.0f;
	const float near_plane = 0.1f;
	const float far_plane = 1000.0f;

	const glm::vec3 lookat_center = glm::vec3(4.0f, 5.0f, 0.0f);
	const glm::vec3 up =  glm::vec3(0.0f, 1.0f, 0.0f);
	const glm::vec3 eye_position = glm::vec3(-10.0f, 8.0f, -5.0f);
	glm::mat4 projection_transform;
	
public:
 	Camera();	
 	glm::vec3 get_eye_position();
	glm::mat4 get_projection_transform();
};

#endif