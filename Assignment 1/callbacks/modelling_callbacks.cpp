#include "modelling_callbacks.hpp"

namespace modellingMode {

/**
 * @brief      { Update(Set/Reset) global shared varible key_state_io according to
 *             the key used. 
 *             0 - K |
 *             1 - L |
 *             2 - Left Shift  
 *             }
 *
 * @param[in]  key     The key pressed
 * @param[in]  action  The action (release or press)
 */
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


/**
 * @brief      { Update(Set/Reset) global shared varible key_state_color according to
 *             the key used. 
 *             0 - T |
 *             1 - G |
 *             2 - B 
 *             }
 *
 * @param[in]  key     The key pressed
 * @param[in]  action  The action (release or press)
 */
void color_callback(int key, int action) {    
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        key_state_color[0] = true;
    }
    else if (key == GLFW_KEY_R && action == GLFW_RELEASE) {
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
    
    else if (key == GLFW_KEY_T && action == GLFW_PRESS) {
        key_state_color[3] = true;
    }
    else if (key == GLFW_KEY_T && action == GLFW_RELEASE) {
        key_state_color[3] = false;
    }
    
    else if (key == GLFW_KEY_H && action == GLFW_PRESS) {
        key_state_color[4] = true;
    }
    else if (key == GLFW_KEY_H && action == GLFW_RELEASE) {
        key_state_color[4] = false;
    }
    
    else if (key == GLFW_KEY_N && action == GLFW_PRESS) {
        key_state_color[5] = true;
    }
    else if (key == GLFW_KEY_N && action == GLFW_RELEASE) {
        key_state_color[5] = false;
    }
}

/**
 * @brief      { Update(Set/Reset) global shared varible key_state_entry according to
 *             the key used. 
 *             0 - Num 1 | 
 *             1 - Num 2 |
 *             2 - Num 3 
 *             }
 *
 * @param[in]  key     The key pressed
 * @param[in]  action  The action (release or press)
 */
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

/**
 * @brief      { Update(Set/Reset) global shared varible key_state_mouse_location
 *             according to the GLFW_KEY_LEFT_CONTROL  key used. }
 *
 * @param[in]  key     The key pressed
 * @param[in]  action  The action (release or press)
 */
void  mouse_locate_callback(int key, int action) {    
    if (key == GLFW_KEY_LEFT_CONTROL  && action == GLFW_PRESS) {
        key_state_mouse_location = true;
    }
    else if (key == GLFW_KEY_LEFT_CONTROL  && action == GLFW_RELEASE) {
        key_state_mouse_location = false;
    }
}

/**
 * @brief      { Update(Set/Reset) global shared varible left_click if button is
 *             clicked or released}
 *
 * @param[in]  button  The button clicked
 * @param[in]  action  The action (release or press)
 */
void mouse_callback(int button, int action) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        left_click = true;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        left_click = false;    
    }
}

};



