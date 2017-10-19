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
	else if (key == GLFW_KEY_C and action == GLFW_PRESS) {
		key_state_scaling_mode = !key_state_scaling_mode;
		printf("SCALING MODE %d\n", key_state_scaling_mode);
	}


	// Modelling Mode Callbacks
	else if (key == GLFW_KEY_L and action == GLFW_PRESS) {
		std::string model_filename;
		printf("Enter File:");
		std::cin >> model_filename;
		scene.load_new_model(model_filename);
	}
	else if (key == GLFW_KEY_K and action == GLFW_PRESS) {
		scene.save_model(selected_model_number);
		printf("Saved model %d\n", selected_model_number);
	}
	else if (key == GLFW_KEY_1 and action == GLFW_PRESS) {
		selected_model_number = 1;
		printf("SELECTED MODEL %d\n", selected_model_number);
	}
	else if (key == GLFW_KEY_2 and action == GLFW_PRESS) {
		selected_model_number = 1;
		printf("SELECTED MODEL %d\n", selected_model_number);
	}
	else if (key == GLFW_KEY_3 and action == GLFW_PRESS) {
		selected_model_number = 3;
		printf("SELECTED MODEL %d\n", selected_model_number);
	}
	else if (key == GLFW_KEY_4 and action == GLFW_PRESS) {
		selected_model_number = 4;
		printf("SELECTED MODEL %d\n", selected_model_number);
	}
	else if (key == GLFW_KEY_J) {
		std::cout << "Enter parent and child:";
		int a, b; std::cin >> a >> b ;
		std::cout << "Enter parent point:";
		float x, y, z; std::cin >> x >> y >> z;
		std::cout << "Enter child point:";
		float x1, y1, z1; std::cin >> x1 >> y1 >> z1;
		scene.model_list[a].join_child(scene.model_list[b], glm::vec3(x, y, z), glm::vec3(x1, y1, z1));
	}
}

};
