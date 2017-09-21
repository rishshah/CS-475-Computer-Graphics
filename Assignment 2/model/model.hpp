#ifndef _MODEL_HPP_
#define _MODEL_HPP_
#include <stdio.h>
#include "../../glm/vec4.hpp"
#include "../../glm/vec3.hpp"
#include "../../glm/mat4x4.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../framework/gl_framework.hpp"

/**
 * @brief      Class for storing vertex attributes.
 */
class Vertex {
public:
	glm::vec3 position;
	glm::vec3 color;
};


/**
 * @brief      Class for storing model data.
 */
class Model {
public:

	std::vector<Vertex> vertex_list;
	GLuint vbo;
	/**
	 * @brief      load model from a file
	 *
	 * @return     true if successfully loaded
	 */
	bool load(char* filename);

	/**
	 * @brief      assign model buffer to vbo and accordingly adjust how the
	 *             values will be interpreted by vertex shader
	 *
	 * @param      vPosition  The varible pointing to location of vertex
	 *                        position in shader
	 * @param      vColor     The varible pointing to location of vertex color
	 *                        in shader
	 */
	void assignBuffer(GLuint &vPosition, GLuint &vColor);
};


/**
 * @brief      Class for storing model attributes in the world
 */
class WorldModel {
public:
	Model m;

	glm::vec3 scale_vec;
	glm::vec3 rotation_vec;
	glm::vec3 position_vec;

	glm::mat4 transformation_mtx;
	/**
	 * @brief      Use position, scale and rotation to get modelling
	 *             transformation.
	 *
	 * @return     The modelling transformation matrix in homogemous space.
	 */
	void calc_modelling_transformation();
};

/**
 * @brief      Class for camera data.
 */
class WorldCamera {
public:
	glm::vec3 eye_position;
	glm::vec3 look_at;
	glm::vec3 up;

	float L, R, T, B, N, F;
};

/**
 * @brief      Class for storing scene data.
 */
class Scene {
public:

	std::vector<WorldModel> model_list;
	WorldCamera cam;
	
	GLuint vao = 0;
	GLuint uModelViewMatrix = 0;
	GLuint vPosition, vColor;

	glm::mat4 modelview_matrix;
	
	/**
	 * @brief      load scene from a file
	 *
	 * @return     true if successfully loaded
	 */
	bool load();

	void draw();
};

#include "../main.hpp"

#endif
