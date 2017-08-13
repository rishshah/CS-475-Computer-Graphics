#ifndef _INSPECTION_CALLBACKS_HPP_
#define _INSPECTION_CALLBACKS_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

namespace inspectMode
{
void rotation_callback(int key, int action);
void recenter_callback(int key, int action);
void translation_callback(int key, int action);
};

#endif
