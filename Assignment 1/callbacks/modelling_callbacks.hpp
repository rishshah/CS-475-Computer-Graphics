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
extern std::vector<bool> key_state_color;
// 0 - Red
// 1 - Green
// 2 - Blue
extern std::vector<bool> key_state_entry;
// 0 - All the points form triangle in sequence of 3(GL_TRIANGLES)
// 1 - All the points form triangle with last 2 (GL_TRIANGLES_STRIP)
// 2 - All the points form triangle with fist and last (GL_TRIANGLES_FAN)

extern bool left_click;

namespace modellingMode {
	void io_callback(int key, int action);
	void mouse_callback(int button, int action);
	void color_callback(int key, int action);
	void entry_mode_callback(int key, int action);
};

#endif
