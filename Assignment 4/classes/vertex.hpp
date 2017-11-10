#ifndef _VERTEX_HPP_
#define _VERTEX_HPP_

#include "../global.hpp"

/**
 * @brief      Class for vertex position and color data.
 */
class Vertex {
public:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal = glm::vec3(1.0f);
	glm::vec2 texture = glm::vec2(0.0f);
};

#endif