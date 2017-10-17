#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "./clipping.hpp"
#include "../global.hpp"

/**
 * @brief      Class for vertexlist and vbo for a generic model.
 */
class Model {
public:
	std::vector<Vertex> vertex_list;
	GLuint vbo;

	bool load(char* filename);

	void assignBuffer();

	void draw(GLuint vPosition, GLuint vColor, GLuint uModelViewMatrix,
	          GLuint uNDCS, GLenum mode, glm::mat4 modelview_matrix, int ndcs_divide);
	Model clip(glm::mat4 transformation_mtx);
};

/**
 * @brief      Class for model postioned in the world coordinate system.
 */
class WorldModel {
public:
	Model m;

	glm::vec3 scale_vec;
	glm::vec3 rotation_vec;
	glm::vec3 position_vec;

	glm::mat4 transformation_mtx;

	void calc_modelling_transformation();
};

#endif
