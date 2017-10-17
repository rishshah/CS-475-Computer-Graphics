#include "worldCamera.hpp"


/**
 * @brief      Creates frustum, eye, and projectors models approriately.
 */
void WorldCamera::create_frustum() {
	glm::vec3 cyan = glm::vec3(0.0f, 1.0f, 1.0f);
	glm::vec3 red = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 magenta = glm::vec3(1.0f, 0.0f, 1.0f);
	float fL = F * L / N, fR = F * R / N, fT = F * T / N, fB = F * B / N;

	frustum.vertex_list.resize(0);
	frustum.vertex_list.push_back(Vertex(glm::vec3(R, T, -N), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(fR, fT, -F), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(L, T, -N), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(fL, fT, -F), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(L, B, -N), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(fL, fB, -F), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(R, B, -N), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(fR, fB, -F), cyan));


	frustum.vertex_list.push_back(Vertex(glm::vec3(R, T, -N), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(L, T, -N), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(L, T, -N), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(L, B, -N), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(L, B, -N), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(R, B, -N), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(R, B, -N), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(R, T, -N), cyan));

	frustum.vertex_list.push_back(Vertex(glm::vec3(fR, fT, -F), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(fL, fT, -F), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(fL, fT, -F), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(fL, fB, -F), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(fL, fB, -F), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(fR, fB, -F), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(fR, fB, -F), cyan));
	frustum.vertex_list.push_back(Vertex(glm::vec3(fR, fT, -F), cyan));

	middle.vertex_list.resize(0);
	middle.vertex_list.push_back(Vertex(glm::vec3(R, T, -N), magenta));
	middle.vertex_list.push_back(Vertex(glm::vec3(0, 0, 0), magenta));
	middle.vertex_list.push_back(Vertex(glm::vec3(L, T, -N), magenta));
	middle.vertex_list.push_back(Vertex(glm::vec3(0, 0, 0), magenta));
	middle.vertex_list.push_back(Vertex(glm::vec3(L, B, -N), magenta));
	middle.vertex_list.push_back(Vertex(glm::vec3(0, 0, 0), magenta));
	middle.vertex_list.push_back(Vertex(glm::vec3(R, B, -N), magenta));
	middle.vertex_list.push_back(Vertex(glm::vec3(0, 0, 0), magenta));

	eye.vertex_list.resize(0);
	eye.vertex_list.push_back(Vertex(glm::vec3(0.0f, 0.0f, 0.0f), red));

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
	uNDCS = glGetUniformLocation( shaderProgram, "uNDCS");

	vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
	glEnableVertexAttribArray( vPosition );

	vColor = glGetAttribLocation( shaderProgram, "vColor" );
	glEnableVertexAttribArray( vColor );

	frustum.assignBuffer();
	middle.assignBuffer();
	eye.assignBuffer();

	display_eye = 1;
}

/**
 * @brief      Draw the camera ( eye, frustum, projectors) on the screen
 *
 * @param[in]  transformation_mtx  The transformation mtx to be given as input to shader for this draw call
 */
void WorldCamera::draw(glm::mat4 transformation_mtx) {
	glBindVertexArray(vao);

	frustum.draw(vPosition, vColor, uModelViewMatrix, uNDCS, GL_LINES, transformation_mtx, 0);
	glPointSize(4.0f);
	if (display_eye == 1) {
		middle.draw(vPosition, vColor, uModelViewMatrix, uNDCS, GL_LINES, transformation_mtx, 0);
		eye.draw(vPosition, vColor, uModelViewMatrix, uNDCS, GL_POINTS, transformation_mtx, 0);
	}
}
