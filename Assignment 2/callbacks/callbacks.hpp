#ifndef _CALLBACKS_HPP_
#define _CALLBACKS_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vector>
#include <iostream>


#include "../../glm/vec4.hpp"

extern bool mode_inspection;

namespace base {
	/**
	 * @brief  handle button presses for changing modes of viewing
	 */
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif
