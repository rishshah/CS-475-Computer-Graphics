#ifndef _CALLBACKS_HPP_
#define _CALLBACKS_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vector>
#include <iostream>


#include "modelling_callbacks.hpp"
#include "inspection_callbacks.hpp"
#include "../../glm/vec4.hpp"
#include "../main.hpp" // for modiying the rotation matrix

extern bool mode_inspection;

namespace base {
/**
 * @brief      distribute Keyboard callbacks to inspection and modelling modes
 */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
/**
 * @brief      Mouse Callbacks distribute to modelling Mode
 */
void mouse_callback(GLFWwindow* window, int button, int action, int mods);
};

#endif
