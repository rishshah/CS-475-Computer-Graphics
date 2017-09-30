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


/**
 * @brief      Class for camera, frustum and projectors postioned in world coordinate system.
 */
class WorldCamera {
public:
	glm::vec3 eye_position;
	glm::vec3 look_at;
	glm::vec3 up;

	float L, R, T, B, N, F;

	GLuint vao;
	GLuint vPosition, vColor, uModelViewMatrix;
	GLuint uNDCS;

	Model frustum, middle, eye;
	int display_eye = 1;

	void create_frustum();
	void draw(glm::mat4 transformation_mtx);
};

/**
 * @brief      Class for world coordinate system axes.
 */
class Axes {
public:

	Model m;
	glm::mat4 dummy_matrix = glm::mat4(1.0f);

	GLuint vao = 0;
	GLuint vPosition, vColor, uModelViewMatrix;
	GLuint uNDCS;


	void create_axes();
	void draw(glm::mat4 transformation_mtx);
};


#include "../main.hpp"

#endif
