#include "./scene.hpp"

void Scene::init() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");

	vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
	glEnableVertexAttribArray( vPosition );

	vColor = glGetAttribLocation( shaderProgram, "vColor" );
	glEnableVertexAttribArray( vColor );

	model_list.resize(0);
}
/**
 * @brief     Load new model in scene
 */
void Scene::load_new_model(std::string model_filename) {
	Model m;
	m.load("./models/" + model_filename + ".raw");
	model_list.push_back(m);
}

void Scene::save_model(int i) {
	model_list[i].save();
}

/**
 * @brief      draw all contents of the screen
 * @param[in]  third_person_transform  the third person transformation matrix to be used
 */
void Scene::draw(glm::mat4 third_person_transform, glm::mat4 projection_transform) {
	glBindVertexArray(vao);
	for (int i = 0; i < model_list.size(); ++i){
		model_list[i].draw(vPosition, vColor, uModelViewMatrix, GL_TRIANGLES, third_person_transform, projection_transform);
	}
}
