#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "../global.hpp"
#include "./vertex.hpp"


/**
 * @brief      Class for vertex_list and vbo for a generic model.
 */
class Model {
public:
	char id[100];
	std::vector<Vertex> vertex_list;
	std::vector<Model> child_model_list;

	glm::vec3 par_translation_vec = glm::vec3(0.0f);
	glm::vec3 self_translation_vec = glm::vec3(0.0f);
	glm::vec3 scale_vec = glm::vec3(1.0f);

	GLuint vbo;

	bool load(std::string filename);
	bool save();

	void join_child(Model m, glm::vec3 point_child, glm::vec3 point_parent);

	void assignBuffer();

	void draw(GLuint vPosition, GLuint vColor, GLuint uModelViewMatrix, 
		GLenum mode, glm::mat4 third_person_transform, glm::mat4 projection_transform);
};

#endif
