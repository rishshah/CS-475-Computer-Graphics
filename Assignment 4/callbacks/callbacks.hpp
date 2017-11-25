#ifndef _CALLBACKS_HPP_
#define _CALLBACKS_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vector>
#include <iostream>

#include "../global.hpp"
#include "../classes/model.hpp"
#include "../classes/heirarchical_model.hpp"
#include "../classes/scene.hpp"
#include "../main.hpp"

extern std::vector<bool> key_state_translation;
//X     0 -> A      1 -> D
//Y     2 -> W      3 -> S
//Z     4 -> Z      5 -> X

extern std::vector<bool> key_state_rotation;
//X     0 -> Up     1 -> Down	
//Y     2 -> Left   3 -> Right
//Z     4 -> pgUp   5 -> PgDown


extern HeirarchicalModel* curr_heirarchical_model;
extern Model* curr_model;
extern Scene* scene;

extern int mode;

namespace base {
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	const int VIEW_MODE = 0;
	const int RECORD_MODE = 1;
	const int PLAYBACK_MODE = 2;
};

#endif
