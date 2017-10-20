#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "../global.hpp"
#include "./vertex.hpp"


/**
 * @brief      Class for a generic model or model part.
 */
class Model {
private:
	glm::mat4 rotation_mtx, scale_mtx;
	char id[100];
	std::vector<Vertex> vertex_list;
	std::vector<Model> child_model_list;

	glm::vec3 par_translation_vec = glm::vec3(0.0f);
	glm::vec3 self_translation_vec = glm::vec3(0.0f);
	glm::vec3 scale_vec = glm::vec3(1.0f);
	glm::vec3 rotation_vec = glm::vec3(1.0f);


	glm::vec3 final_translation_vec = glm::vec3(0.0f);
	GLuint vbo;

public:
	void calc_matrices();
	bool load(std::string filename, glm::vec3 cumu_translation, glm::mat4 par_rotation_mtx, glm::mat4 par_scale_mtx);
	void assignBuffer();
	void draw(GLuint vPosition, GLuint vColor, GLuint uModelViewMatrix,
	          GLenum mode, glm::mat4 third_person_transform, glm::mat4 projection_transform);
};

/**
 * @brief      Class for complete heirarchical model independent of others.
 */
class HeirarchicalModel : public Model {
public:
	float xpos = 0.0, ypos = 0.0, zpos = 0.0;
	float xscale = 1.0, yscale = 1.0, zscale = 1.0;

	glm::mat4 translation_matrix = glm::mat4(1.0f);
	glm::mat4 rotation_matrix = glm::mat4(1.0f);
	glm::mat4 scaling_matrix = glm::mat4(1.0f);
};

#endif
