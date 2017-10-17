#include "./vertex.hpp"
/**
 * @brief      Constructs the default vertex.
 */
Vertex::Vertex() {
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	color = glm::vec3(0.0f, 0.0f, 0.0f);
}
/**
 * @brief      Constructs the vertex given position and color.
 *
 * @param[in]  p     position vec3
 * @param[in]  c     color vec3
 */
Vertex::Vertex(glm::vec3 p, glm::vec3 c) {
	position = p;
	color = c;
}
