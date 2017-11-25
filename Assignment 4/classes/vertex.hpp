#ifndef _VERTEX_HPP_
#define _VERTEX_HPP_

#include "../global.hpp"

/**
 * @brief      Struct for vertex position, color normal and texture data.
 */
struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal = glm::vec3(1.0f);
	glm::vec2 texture = glm::vec2(0.0f);
};

#endif