#include "callbacks.hpp"

namespace base {

/**
 * @brief      Update(Set/Reset) global shared varible key_state_rotation according to
 *             the key used.
 *             0 - Up   |
 *             1 - Down     |
 *             2 - Left     |
 *             3 - Right    |
 *             4 - PageUp   |
 *             5 - PageDown
 *
 * @param[in]  key     The key pressed
 * @param[in]  action  The action (release or press)
 */
void rotation_callback(int key, int action) {
	// Rotate about Xaxis
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		key_state_rotation[0] = true;
		key_state_rotation[1] = false;

	}
	else if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {
		key_state_rotation[0] = false;
		key_state_rotation[1] = false;
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		key_state_rotation[1] = true;
		key_state_rotation[0] = false;
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
		key_state_rotation[1] = false;
		key_state_rotation[0] = false;
	}

	// Rotate about Yaxis
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		key_state_rotation[2] = true;
		key_state_rotation[3] = false;
	}
	else if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
		key_state_rotation[2] = false;
		key_state_rotation[3] = false;
	}
	else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		key_state_rotation[3] = true;
		key_state_rotation[2] = false;
	}
	else if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
		key_state_rotation[3] = false;
		key_state_rotation[2] = false;
	}

	// Rotate about Zaxis
	else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS) {
		key_state_rotation[4] = true;
		key_state_rotation[5] = false;
	}
	else if (key == GLFW_KEY_PAGE_UP && action == GLFW_RELEASE) {
		key_state_rotation[4] = false;
		key_state_rotation[5] = false;
	}
	else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS) {
		key_state_rotation[5] = true;
		key_state_rotation[4] = false;
	}
	else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_RELEASE) {
		key_state_rotation[5] = false;
		key_state_rotation[4] = false;
	}
}

/**
 * @brief      Update(Set/Reset) global shared varible key_state_trans_or_scale according to
 *             the key used.
 *             0 - A    |
 *             1 - D    |
 *             2 - W    |
 *             3 - S    |
 *             4 - Z    |
 *             5 - X
 *
 * @param[in]  key     The key pressed
 * @param[in]  action  The action (release or press)
 */
void trans_and_scale_callback(int key, int action) {
	// Translate along Xaxis
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		key_state_trans_or_scale[0] = true;
		key_state_trans_or_scale[1] = false;
	}
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
		key_state_trans_or_scale[0] = false;
		key_state_trans_or_scale[1] = false;
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		key_state_trans_or_scale[1] = true;
		key_state_trans_or_scale[0] = false;
	}
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
		key_state_trans_or_scale[1] = false;
		key_state_trans_or_scale[0] = false;
	}

	// Translate along Yaxis
	else if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		key_state_trans_or_scale[2] = true;
		key_state_trans_or_scale[3] = false;
	}
	else if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
		key_state_trans_or_scale[2] = false;
		key_state_trans_or_scale[3] = false;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		key_state_trans_or_scale[3] = true;
		key_state_trans_or_scale[2] = false;
	}
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
		key_state_trans_or_scale[3] = false;
		key_state_trans_or_scale[2] = false;
	}

	// Translate along Zaxis
	else if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		key_state_trans_or_scale[4] = true;
		key_state_trans_or_scale[5] = false;
	}
	else if (key == GLFW_KEY_Z && action == GLFW_RELEASE) {
		key_state_trans_or_scale[4] = false;
		key_state_trans_or_scale[5] = false;
	}
	else if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		key_state_trans_or_scale[5] = true;
		key_state_trans_or_scale[4] = false;
	}
	else if (key == GLFW_KEY_X && action == GLFW_RELEASE) {
		key_state_trans_or_scale[5] = false;
		key_state_trans_or_scale[4] = false;
	}
}

/**
 * @brief      Update(Set/Reset) global shared varible key_state_recenter according to
 *             usage of key R.
 *
 *
 * @param[in]  key     The key pressed
 * @param[in]  action  The action (release or press)
 */
void recenter_callback(int key, int action) {
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		key_state_recenter = true;
	}
	else if (key == GLFW_KEY_R && action == GLFW_RELEASE) {
		key_state_recenter = false;
	}
}

/**
 * @brief select part of model based on which key is pressed
 * 
 * @param key key pressed
 * @return returns id of selected part
 */
std::string handle_modelling_callback(int key) {
	switch (key) {
	case GLFW_KEY_1:
		return "eye_ball_left";
	case GLFW_KEY_2:
		return "eye_ball_right";
	case GLFW_KEY_3:
		return "lower_mouth";
	case GLFW_KEY_4:
		return "tail";
	case GLFW_KEY_5:
		return "front_left_leg";
	case GLFW_KEY_6:
		return "front_right_leg";
	case GLFW_KEY_7:
		return "back_left_leg";
	case GLFW_KEY_8:
		return "back_right_leg";
	default:
		return "body";
	}
}

/**
 * @brief handle input key presses from keyboard
 */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	// Third Person View Callbacks
	else if ( key == GLFW_KEY_UP or key == GLFW_KEY_DOWN or
	          key == GLFW_KEY_LEFT or key == GLFW_KEY_RIGHT or
	          key == GLFW_KEY_PAGE_UP or key == GLFW_KEY_PAGE_DOWN) {
		rotation_callback(key, action);
	}
	else if ( key == GLFW_KEY_R) {
		recenter_callback(key, action);
	}
	else if ( key == GLFW_KEY_W or
	          key == GLFW_KEY_S or
	          key == GLFW_KEY_A or
	          key == GLFW_KEY_D or
	          key == GLFW_KEY_Z or
	          key == GLFW_KEY_X) {
		trans_and_scale_callback(key, action);
	}
	// toggle scaling mode
	else if (key == GLFW_KEY_C and action == GLFW_PRESS) {
		key_state_scaling_mode = !key_state_scaling_mode;
		printf("SCALING MODE %d\n", key_state_scaling_mode);
	}


	// Modelling Mode Callbacks
	// Load a new model
	else if (key == GLFW_KEY_L and action == GLFW_PRESS) {
		std::string model_filename, id;
		printf("Enter File and id:");
		std::cin >> model_filename >> id;
		scene.load_new_model(model_filename, id);
	}

	// Switch to Pan mode
	else if (key == GLFW_KEY_P and action == GLFW_PRESS) {
		pan_mode = true;
		modelling_mode = false;
		printf("Scene pan mode\n");
	}

	//Modelling mode
	else if (key == GLFW_KEY_M and action == GLFW_PRESS) {
		modelling_mode = true;
		pan_mode = false;
		printf("Select heirarchical model:\n");
		std::string id; std::cin >> id;
		curr_heirarchical_model = scene.find_heirarchical_model_by_id(id);
		curr_model = curr_heirarchical_model->find_by_id("body");
	}
	else if (modelling_mode and action == GLFW_PRESS and
	         (key == GLFW_KEY_1 or
	          key == GLFW_KEY_2 or
	          key == GLFW_KEY_3 or
	          key == GLFW_KEY_4 or
	          key == GLFW_KEY_5 or
	          key == GLFW_KEY_6 or
	          key == GLFW_KEY_7 or
	          key == GLFW_KEY_8)
	        ) {
		std::string id = handle_modelling_callback(key);
		curr_model = curr_heirarchical_model->find_by_id(id);
		if (curr_model != NULL)
			printf("modelling %s now!\n", id.c_str());
	}
}
};
