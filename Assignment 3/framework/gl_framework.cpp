#include "gl_framework.hpp"

namespace base {
//! Initialize GL State
void initGL(void) {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
}

//!GLFW Error Callback
void error_callback(int error, const char* description) {
    std::cerr << description << std::endl;
}

//!GLFW framebuffer resize callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
}
};



