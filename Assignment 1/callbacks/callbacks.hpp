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

extern bool mode_inspection;

namespace base{
	void key_callback(int key, int action);
	void mouse_callback(int key, int action);
};

#endif
