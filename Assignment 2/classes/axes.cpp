#include "axes.hpp"



/**
 * @brief      Creates WCC axes model.
 */
void Axes::create_axes() {
	glm::vec3 red = glm::vec3(1.0f, 0.0f, 0.0f);  //x
	glm::vec3 green = glm::vec3(0.0f, 1.0f, 0.0f); //y
	glm::vec3 blue = glm::vec3(0.0f, 0.0f, 1.0f); //z

	float length = 3;

	m.vertex_list.resize(0);

	m.vertex_list.push_back(Vertex(glm::vec3(0, 0, 0), red));
	m.vertex_list.push_back(Vertex(glm::vec3(length, 0, 0), red));

	m.vertex_list.push_back(Vertex(glm::vec3(0, 0, 0), green));
	m.vertex_list.push_back(Vertex(glm::vec3(0, length, 0), green));

	m.vertex_list.push_back(Vertex(glm::vec3(0, 0, 0), blue));
	m.vertex_list.push_back(Vertex(glm::vec3(0, 0, length), blue));

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
	uNDCS = glGetUniformLocation( shaderProgram, "uNDCS");

	vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
	glEnableVertexAttribArray( vPosition );

	vColor = glGetAttribLocation( shaderProgram, "vColor" );
	glEnableVertexAttribArray( vColor );

	m.assignBuffer();
}

/**
 * @brief      draw the WWC axes model on the screen
 *
 * @param[in]  transformation_mtx  The transformation mtx to be used as input to this draw call
 */
void Axes::draw(glm::mat4 transformation_mtx) {
	glBindVertexArray(vao);
	m.draw(vPosition, vColor, uModelViewMatrix, uNDCS, GL_LINES, transformation_mtx * dummy_matrix, 0);
}