#ifndef _MODEL_HPP_
#define _MODEL_HPP_
#include <stdio.h>
#include "../../glm/vec4.hpp"
#include "../../glm/vec3.hpp"
#include "../framework/gl_framework.hpp"


class Vertex {
public:
	glm::vec3 position;
	glm::vec3 color;
};

class Model {
public:

	float red_value = 1.0;
	float green_value = 1.0;
	float blue_value = 1.0;

	int num_of_vertices = 0;
	std::vector<Vertex> vertex_list;

	int num_of_triangles = 0;
	std::vector<int> configuration_list;

	std::vector<glm::vec3> position_ptr;
	std::vector<glm::vec3> color_ptr;

	void combine_configuration_and_vertices();
	bool load(char* filename);
	bool save(char* filename);
	void assignBuffer(GLuint &vbo, GLuint &vao, GLuint &vPosition, GLuint &vColor);
};

#endif
