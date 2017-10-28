#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "../global.hpp"
#include "./vertex.hpp"


/**
 * @brief      Class for a generic model or model part.
 */
class Model {
private:

	const float ROT_DELTA = 0.05;

	const glm::vec4 X_UNIT = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	const glm::vec4 Y_UNIT = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	const glm::vec4 Z_UNIT = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	char id[100];
	std::vector<Vertex> vertex_list;
	std::vector<Model*> child_model_list;

	glm::vec3 par_translation_vec, self_translation_vec;
	glm::vec3 scale_vec, rotation_vec;
	glm::mat4 rotation_mtx, scale_mtx;

	GLuint vbo;
	void assignBuffer();
	void calc_matrices();
public:
	
	bool load(std::string id, std::string filename, glm::mat4 scale_mtx);
	void draw(GLuint vPosition, GLuint vColor, GLuint uModelViewMatrix, GLenum mode, glm::mat4 par_final_transform, glm::mat4 third_person_transform);
	Model* find_by_id(std::string id);
	void rotate(std::vector<bool> key_state_rotation);	
	~Model();
};

/**
 * @brief      Class for complete heirarchical model independent of others.
 */
class HeirarchicalModel : public Model {
public:
	std::string hm_id;
	float xpos = 0.0, ypos = 0.0, zpos = 0.0;
	float xscale = 1.0, yscale = 1.0, zscale = 1.0;

	glm::mat4 translation_matrix = glm::mat4(1.0f);
	glm::mat4 rotation_matrix = glm::mat4(1.0f);
	glm::mat4 scaling_matrix = glm::mat4(1.0f);
};

#endif
