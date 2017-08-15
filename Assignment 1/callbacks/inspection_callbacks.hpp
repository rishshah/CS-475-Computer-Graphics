#ifndef _INSPECTION_CALLBACKS_HPP_
#define _INSPECTION_CALLBACKS_HPP_

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

extern std::vector<bool> key_state_translation;
//X     0 -> A      1 -> D
//Y     2 -> W      3 -> S
//Z     4 -> Z      5 -> X

extern std::vector<bool> key_state_rotation;
//X     0 -> Up     1 -> Down
//Y     2 -> Left   3 -> Right
//Z     4 -> pgUp   5 -> PgDown

extern bool key_state_recenter;


namespace inspectMode {
	void rotation_callback(int key, int action);
	void recenter_callback(int key, int action);
	void translation_callback(int key, int action);
};

#endif
