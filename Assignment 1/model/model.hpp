#ifndef _MODEL_HPP_
#define _MODEL_HPP_
#include <stdio.h>
#include "../../glm/vec4.hpp"
#include "../../glm/vec3.hpp"
#include "../framework/gl_framework.hpp"


class Vertex{
public:
	glm::vec3 position;
	glm::vec3 color;
};

class Model{
private:
	int num_of_vertices;
	std::vector<Vertex> vertex_list;
	
	int num_of_triangles;
	std::vector<int> configuration_list;
	
	glm::vec3 centroid;
	void calc_centroid();
	void combine_configuration_and_vertices();

public:
	std::vector<glm::vec3> position_ptr;
	std::vector<glm::vec3> color_ptr;

	int get_num_of_triangles();
	glm::vec3 get_centroid();

	bool load(char* filename);
	bool save(char* filename);
	void assignBuffer(GLuint &vbo, GLuint &vao, GLuint &vPosition, GLuint &vColor);
};

#endif
