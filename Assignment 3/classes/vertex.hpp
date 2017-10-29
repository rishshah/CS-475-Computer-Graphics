#ifndef _VERTEX_HPP_
#define _VERTEX_HPP_

#include <stdio.h>
#include <vector>
#include "../../glm/vec3.hpp"
#include "../framework/gl_framework.hpp"
#include "../../glm/vec4.hpp"
#include "../../glm/mat4x4.hpp"
#include "../../glm/gtc/matrix_transform.hpp"

/**
 * @brief      Class for vertex position and color data.
 */
class Vertex {
public:
	Vertex();
	Vertex(glm::vec3 p, glm::vec3 c);
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texture = glm::vec2(0.0f);
	glm::vec3 normal = glm::vec3(1.0f);
};

#endif