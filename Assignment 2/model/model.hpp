#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include <stdio.h>
#include "../../glm/vec4.hpp"
#include "../../glm/vec3.hpp"
#include "../../glm/mat4x4.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../framework/gl_framework.hpp"


/**
 * @brief      Class for vertex position and color data.
 */
class Vertex {
public:
	Vertex();
	Vertex(glm::vec3 p, glm::vec3 c);
	glm::vec3 position;
	glm::vec3 color;
};


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


/**
 * @brief      Class for storing the entire scene data.
 */
class Scene {
public:

	std::vector<WorldModel> model_list;
	WorldCamera cam;
	Axes axes;

	GLuint vao = 0;
	GLuint vPosition, vColor, uModelViewMatrix;

	glm::mat4 dummy_matrix = glm::mat4(1.0f);
	glm::mat4 frustum_dummy_matrix = glm::mat4(1.0f);
	glm::mat4 reverse_vcs = glm::mat4(1.0f);
	
	glm::mat4 A_wcs_vcs = glm::mat4(1.0f);
	glm::mat4 A_vcs_ccs = glm::mat4(1.0f);
	glm::mat4 A_ccs_ndcs = glm::mat4(1.0f);
	glm::mat4 A_ndcs_dcs = glm::mat4(1.0f);

	int ndcs_divide = 0;
	GLuint uNDCS;
	
	glm::vec3 center;
	void calc_center();

	bool load();

	void draw(glm::mat4 transformation_mtx);

	void calc_WCS_VCS();

	void calc_VCS_CCS();

	void calc_CCS_NDCS();

	void calc_NDCS_DCS();
};

#include "../main.hpp"

#endif
