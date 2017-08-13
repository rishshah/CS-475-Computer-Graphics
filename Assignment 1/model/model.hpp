#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "../glm/vec4.hpp"
#include "../glm/vec3.hpp"
#include "../framework/gl_framework.hpp"

class Vertex{
public:
	glm::vec3 position;
	glm::vec4 color;
};

class Model{
private:
	int num_of_vertices;
	Vertex* vertex_list;
	
	int num_of_triangles;
	int* configuration_list;
	
	glm::vec3 centroid;
	void calc_centroid();

public:	
	
	glm::vec4* position_ptr;
	glm::vec4* color_ptr;

	int get_num_of_triangles();
	glm::vec4 get_centroid();

	bool load(char* filename);
	bool save(char* filename);
	void assignBuffer(GLuint &vbo, GLuint &vao, GLuint &vPosition, GLuint &vColor);
};

#endif
