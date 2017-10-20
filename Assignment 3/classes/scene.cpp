#include "./scene.hpp"

const std::string FILE_NAME = "./models/perry/";
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
	HeirarchicalModel hm;
	hm.load(FILE_NAME + model_filename + ".raw", glm::vec3(0.0f), glm::vec3(1.0f));
	model_list.push_back(hm);
}

void Scene::save_model(int i) {
	model_list[i].scale_vec = glm::vec3(model_list[i].scaling_matrix * glm::scale(glm::mat4(1.0f), model_list[i].scale_vec) * glm::vec4(1.0));
	model_list[i].save();
}

/**
 * @brief      draw all contents of the screen
 * @param[in]  third_person_transform  the third person transformation matrix to be used
 */
void Scene::draw(glm::mat4 projection_transform) {
	glBindVertexArray(vao);
	for (int i = 0; i < model_list.size(); ++i) {
		model_list[i].draw(vPosition, vColor, uModelViewMatrix, GL_TRIANGLES, translation_matrix * rotation_matrix
		                   * scaling_matrix * model_list[i].translation_matrix * model_list[i].rotation_matrix
		                   * model_list[i].scaling_matrix, projection_transform);
	}
}

void Scene::rotate(std::vector<bool> key_state_rotation) {
	if (key_state_rotation[0]) {
		rotation_matrix = glm::rotate(rotation_matrix, -ROT_DELTA, glm::vec3(glm::transpose(rotation_matrix) * X_UNIT));
	}
	else if (key_state_rotation[1]) {
		rotation_matrix = glm::rotate(rotation_matrix, ROT_DELTA, glm::vec3(glm::transpose(rotation_matrix) * X_UNIT));
	}

	if (key_state_rotation[2]) {
		rotation_matrix = glm::rotate(rotation_matrix, -ROT_DELTA, glm::vec3(glm::transpose(rotation_matrix) * Y_UNIT));
	}
	else if (key_state_rotation[3]) {
		rotation_matrix = glm::rotate(rotation_matrix, ROT_DELTA, glm::vec3(glm::transpose(rotation_matrix) * Y_UNIT));
	}

	if (key_state_rotation[4]) {
		rotation_matrix = glm::rotate(rotation_matrix, ROT_DELTA, glm::vec3(glm::transpose(rotation_matrix) * Z_UNIT));
	}
	else if (key_state_rotation[5]) {
		rotation_matrix = glm::rotate(rotation_matrix, -ROT_DELTA, glm::vec3(glm::transpose(rotation_matrix) * Z_UNIT));
	}
}

void Scene::rotate_model(int i, std::vector<bool> key_state_rotation) {
	if (key_state_rotation[0]) {
		model_list[i].rotation_matrix = glm::rotate(model_list[i].rotation_matrix, -ROT_DELTA, glm::vec3(glm::transpose(model_list[i].rotation_matrix) * X_UNIT));
	}
	else if (key_state_rotation[1]) {
		model_list[i].rotation_matrix = glm::rotate(model_list[i].rotation_matrix, ROT_DELTA, glm::vec3(glm::transpose(model_list[i].rotation_matrix) * X_UNIT));
	}

	if (key_state_rotation[2]) {
		model_list[i].rotation_matrix = glm::rotate(model_list[i].rotation_matrix, -ROT_DELTA, glm::vec3(glm::transpose(model_list[i].rotation_matrix) * Y_UNIT));
	}
	else if (key_state_rotation[3]) {
		model_list[i].rotation_matrix = glm::rotate(model_list[i].rotation_matrix, ROT_DELTA, glm::vec3(glm::transpose(model_list[i].rotation_matrix) * Y_UNIT));
	}

	if (key_state_rotation[4]) {
		model_list[i].rotation_matrix = glm::rotate(model_list[i].rotation_matrix, ROT_DELTA, glm::vec3(glm::transpose(model_list[i].rotation_matrix) * Z_UNIT));
	}
	else if (key_state_rotation[5]) {
		model_list[i].rotation_matrix = glm::rotate(model_list[i].rotation_matrix, -ROT_DELTA, glm::vec3(glm::transpose(model_list[i].rotation_matrix) * Z_UNIT));
	}
}

void Scene::trans_scale(std::vector<bool> key_state_trans_or_scale, bool key_state_recenter, bool key_state_scaling_mode) {
	if (key_state_recenter) {
		xpos = ypos = zpos = 0.0f;
	}
	else if (key_state_scaling_mode) {
		if (key_state_trans_or_scale[0]) {
			xscale = std::max(xscale - SCALE_DELTA, 0.0f);
		}
		else if (key_state_trans_or_scale[1]) {
			xscale = std::max(xscale + SCALE_DELTA, 0.0f);
		}

		if (key_state_trans_or_scale[2]) {
			yscale = std::max(yscale - SCALE_DELTA, 0.0f);
		}
		else if (key_state_trans_or_scale[3]) {
			yscale = std::max(yscale + SCALE_DELTA, 0.0f);
		}

		if (key_state_trans_or_scale[4]) {
			zscale = std::max(zscale + SCALE_DELTA, 0.0f);
		}
		else if (key_state_trans_or_scale[5]) {
			zscale = std::max(zscale - SCALE_DELTA, 0.0f);
		}
	}
	else {
		if (key_state_trans_or_scale[0]) {
			xpos -= TRANS_DELTA;
		}
		else if (key_state_trans_or_scale[1]) {
			xpos += TRANS_DELTA;
		}

		if (key_state_trans_or_scale[2]) {
			ypos += TRANS_DELTA;
		}
		else if (key_state_trans_or_scale[3]) {
			ypos -= TRANS_DELTA;
		}

		if (key_state_trans_or_scale[4]) {
			zpos += TRANS_DELTA;
		}
		else if (key_state_trans_or_scale[5]) {
			zpos -= TRANS_DELTA;
		}
	}
	if (key_state_recenter) {
		rotation_matrix = glm::mat4(1.0f);
	}
	else {
		translation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, zpos));
	}
}

void Scene::trans_scale_model(int i, std::vector<bool> key_state_trans_or_scale, bool key_state_recenter, bool key_state_scaling_mode) {
	if (key_state_recenter) {
		model_list[i].xpos = model_list[i].ypos = model_list[i].zpos = 0.0f;
	}
	else if (key_state_scaling_mode) {
		if (key_state_trans_or_scale[0]) {
			model_list[i].xscale = std::max(model_list[i].xscale - SCALE_DELTA, 0.0f);
		}
		else if (key_state_trans_or_scale[1]) {
			model_list[i].xscale = std::max(model_list[i].xscale + SCALE_DELTA, 0.0f);
		}

		if (key_state_trans_or_scale[2]) {
			model_list[i].yscale = std::max(model_list[i].yscale - SCALE_DELTA, 0.0f);
		}
		else if (key_state_trans_or_scale[3]) {
			model_list[i].yscale = std::max(model_list[i].yscale + SCALE_DELTA, 0.0f);
		}

		if (key_state_trans_or_scale[4]) {
			model_list[i].zscale = std::max(model_list[i].zscale + SCALE_DELTA, 0.0f);
		}
		else if (key_state_trans_or_scale[5]) {
			model_list[i].zscale = std::max(model_list[i].zscale - SCALE_DELTA, 0.0f);
		}
	}
	else {
		if (key_state_trans_or_scale[0]) {
			model_list[i].xpos -= TRANS_DELTA;
		}
		else if (key_state_trans_or_scale[1]) {
			model_list[i].xpos += TRANS_DELTA;
		}

		if (key_state_trans_or_scale[2]) {
			model_list[i].ypos += TRANS_DELTA;
		}
		else if (key_state_trans_or_scale[3]) {
			model_list[i].ypos -= TRANS_DELTA;
		}

		if (key_state_trans_or_scale[4]) {
			model_list[i].zpos += TRANS_DELTA;
		}
		else if (key_state_trans_or_scale[5]) {
			model_list[i].zpos -= TRANS_DELTA;
		}
	}
	if (key_state_recenter) {
		model_list[i].rotation_matrix = glm::mat4(1.0f);
	}
	else {
		model_list[i].translation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(model_list[i].xpos, model_list[i].ypos, model_list[i].zpos));
		model_list[i].scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(model_list[i].xscale, model_list[i].yscale, model_list[i].zscale));
	}
}

// void Scene::join(int p, int c, glm::vec3 point_p, glm::vec3 point_c) {
// 	Model m = model_list[c];
// 	m.scale_vec = glm::vec3(model_list[c].scaling_matrix * glm::scale(glm::mat4(1.0f), model_list[c].scale_vec) * glm::vec4(1.0));
// 	m.self_translation_vec = glm::vec3(model_list[c].scaling_matrix * glm::scale(glm::mat4(1.0f), model_list[c].scale_vec) * glm::vec4(point_c, 1.0f));
// 	m.par_translation_vec = glm::vec3(model_list[p].scaling_matrix * glm::scale(glm::mat4(1.0f), model_list[p].scale_vec) * glm::vec4(point_p, 1.0f));
// 	printf("self:: %f %f %f\n", m.self_translation_vec.x, m.self_translation_vec.y, m.self_translation_vec.z);
// 	printf("par:: %f %f %f\n", m.par_translation_vec.x, m.par_translation_vec.y, m.par_translation_vec.z);

// 	model_list[p].child_model_list.push_back(m);
// };
