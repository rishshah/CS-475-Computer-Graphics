#include "camera.hpp"

Camera::Camera(){
	projection_transform = glm::perspective(glm::radians(field_of_view), aspect_ratio, near_plane, far_plane) *
                       glm::lookAt(eye_position, lookat_center, up);
}
