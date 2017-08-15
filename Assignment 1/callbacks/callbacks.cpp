#include "callbacks.hpp"

namespace base {

//keyboard callbacks
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//!Close the window if the ESC key was pressed
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	// Switching Mode
	else if (key == GLFW_KEY_M and action == GLFW_PRESS) {
		mode_inspection = false;
		printf("MODELLING MODE\n");
	}
	else if (key == GLFW_KEY_I and action == GLFW_PRESS) {
		mode_inspection = true;
		printf("INSPECTION MODE\n");
	}

	// Inspection callbacks
	else if ( key == GLFW_KEY_UP or key == GLFW_KEY_DOWN or
	          key == GLFW_KEY_LEFT or key == GLFW_KEY_RIGHT or
	          key == GLFW_KEY_PAGE_UP or key == GLFW_KEY_PAGE_DOWN) {
		inspectMode::rotation_callback(key, action);
	}
	else if ( key == GLFW_KEY_R) {
		inspectMode::recenter_callback(key, action);
	}
	else if ( key == GLFW_KEY_W or
	          key == GLFW_KEY_S or
	          key == GLFW_KEY_A or
	          key == GLFW_KEY_D or
	          key == GLFW_KEY_Z or
	          key == GLFW_KEY_X) {
		inspectMode::translation_callback(key, action);
	}

	//Modelling callbacks
	else if ( key == GLFW_KEY_K or
	          key == GLFW_KEY_L) {
		modellingMode::io_callback(key, action);
	}
}

//Mouse callbacks
void mouse_callback(GLFWwindow* window, int button, int action, int mods) {
	modellingMode::mouse_callback(button, action);
}

};
