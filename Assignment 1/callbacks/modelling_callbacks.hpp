#ifndef _MODELLING_CALLBACKS_HPP_
#define _MODELLING_CALLBACKS_HPP_

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>


extern std::vector<bool> key_state_io;
// 0 - Save
// 1 - Load
// 2 - Shift
extern bool left_click;

namespace modellingMode {
	void io_callback(int key, int action);
	void mouse_callback(int button, int action);
};

#endif
