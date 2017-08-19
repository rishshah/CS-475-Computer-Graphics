#include "modelling_callbacks.hpp"

namespace modellingMode {

void io_callback(int key, int action) {
    if (key == GLFW_KEY_K && action == GLFW_PRESS) {
        key_state_io[0] = true;
    }
    else if (key == GLFW_KEY_K && action == GLFW_RELEASE) {
        key_state_io[0] = false;
    }
    else if (key == GLFW_KEY_L && action == GLFW_PRESS) {
        key_state_io[1] = true;
    }
    else if (key == GLFW_KEY_L && action == GLFW_RELEASE) {
        key_state_io[1] = false;
    }
    else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
        key_state_io[2] = true;
    }
    else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) {
        key_state_io[2] = false;
    }
}

void mouse_callback(int button, int action) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        left_click = true;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        left_click = false;    
    }
}

};



