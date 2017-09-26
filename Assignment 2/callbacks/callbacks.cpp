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
 * @brief      Update(Set/Reset) global shared varible key_state_translation according to
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
void translation_callback(int key, int action) {
	// Translate along Xaxis
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		key_state_translation[0] = true;
		key_state_translation[1] = false;
	}
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
		key_state_translation[0] = false;
		key_state_translation[1] = false;
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		key_state_translation[1] = true;
		key_state_translation[0] = false;
	}
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
		key_state_translation[1] = false;
		key_state_translation[0] = false;
	}

	// Translate along Yaxis
	else if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		key_state_translation[2] = true;
		key_state_translation[3] = false;
	}
	else if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
		key_state_translation[2] = false;
		key_state_translation[3] = false;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		key_state_translation[3] = true;
		key_state_translation[2] = false;
	}
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
		key_state_translation[3] = false;
		key_state_translation[2] = false;
	}

	// Translate along Zaxis
	else if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		key_state_translation[4] = true;
		key_state_translation[5] = false;
	}
	else if (key == GLFW_KEY_Z && action == GLFW_RELEASE) {
		key_state_translation[4] = false;
		key_state_translation[5] = false;
	}
	else if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		key_state_translation[5] = true;
		key_state_translation[4] = false;
	}
	else if (key == GLFW_KEY_X && action == GLFW_RELEASE) {
		key_state_translation[5] = false;
		key_state_translation[4] = false;
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
	//!Close the window if the ESC key was pressed
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	else if (key == GLFW_KEY_1 and action == GLFW_PRESS) {
		printf("1 pressed\n");
		scene.dummy_matrix = scene.reverse_vcs * scene.A_wcs_vcs;
		scene.axes.dummy_matrix = scene.reverse_vcs ;
	}
	else if (key == GLFW_KEY_2 and action == GLFW_PRESS) {
		printf("2 pressed\n");
		scene.dummy_matrix = scene.reverse_vcs * scene.A_vcs_ccs * scene.A_wcs_vcs;
		scene.axes.dummy_matrix = scene.reverse_vcs ;
	}
	else if (key == GLFW_KEY_3 and action == GLFW_PRESS) {
		printf("3 pressed\n");
		scene.dummy_matrix = scene.reverse_vcs * scene.A_ccs_ndcs * scene.A_vcs_ccs * scene.A_wcs_vcs;
	}
	else if (key == GLFW_KEY_4 and action == GLFW_PRESS) {
		printf("4 pressed\n");
		scene.dummy_matrix = scene.A_ndcs_dcs * scene.A_ccs_ndcs * scene.A_vcs_ccs * scene.A_wcs_vcs;
	}
	// Inspection callbacks
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
		translation_callback(key, action);
	}
}
};
