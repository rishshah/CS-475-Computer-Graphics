#include "callbacks.hpp"

namespace base {
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//!Close the window if the ESC key was pressed
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	
	else if (key == GLFW_KEY_1 and action == GLFW_PRESS) {
		printf("1 pressed\n");
	}
	else if (key == GLFW_KEY_2 and action == GLFW_PRESS) {
		printf("2 pressed\n");
	}
	else if (key == GLFW_KEY_3 and action == GLFW_PRESS) {
		printf("3 pressed\n");
	}
	else if (key == GLFW_KEY_4 and action == GLFW_PRESS) {
		printf("4 pressed\n");
	}
}
};
