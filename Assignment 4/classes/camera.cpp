#include "camera.hpp"

Camera::Camera(){
	projection_transform = glm::perspective(glm::radians(field_of_view), aspect_ratio, near_plane, far_plane) *
                       glm::lookAt(eye_position, lookat_center, up);
}

glm::vec3 Camera::get_eye_position(){
	return eye_position;
}

glm::mat4 Camera::get_projection_transform(){
	return projection_transform;
}