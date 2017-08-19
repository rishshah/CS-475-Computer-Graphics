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

void color_callback(int key, int action) {    
    if (key == GLFW_KEY_T && action == GLFW_PRESS) {
        key_state_color[0] = true;
    }
    else if (key == GLFW_KEY_T && action == GLFW_RELEASE) {
        key_state_color[0] = false;
    }
    
    else if (key == GLFW_KEY_G && action == GLFW_PRESS) {
        key_state_color[1] = true;
    }
    else if (key == GLFW_KEY_G && action == GLFW_RELEASE) {
        key_state_color[1] = false;
    }
    
    else if (key == GLFW_KEY_B && action == GLFW_PRESS) {
        key_state_color[2] = true;
    }
    else if (key == GLFW_KEY_B && action == GLFW_RELEASE) {
        key_state_color[2] = false;
    }
}

void entry_mode_callback(int key, int action) {    
    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        key_state_entry[0] = true;
    }
    else if (key == GLFW_KEY_1 && action == GLFW_RELEASE) {
        key_state_entry[0] = false;
    }
    
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        key_state_entry[1] = true;
    }
    else if (key == GLFW_KEY_2 && action == GLFW_RELEASE) {
        key_state_entry[1] = false;
    }
    
    else if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
        key_state_entry[2] = true;
    }
    else if (key == GLFW_KEY_3 && action == GLFW_RELEASE) {
        key_state_entry[2] = false;
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



