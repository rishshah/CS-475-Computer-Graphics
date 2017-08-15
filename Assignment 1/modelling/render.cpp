#include "render.hpp"

//extern variables
Model m;
GLuint vbo = 0, vao = 0;

std::vector<bool> key_state_io(2, false);
bool left_click = false;

//-----------------------------------------------------------------

void initBuffersGL() {
    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);

    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);

    GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
    glEnableVertexAttribArray( vPosition );

    GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" );
    glEnableVertexAttribArray( vColor );

    m.assignBuffer(vao, vbo, vPosition, vColor);
}

void handle_io() {
    if (key_state_io[0]) {
        m.save((char*)"./model/saved_model.raw");
        printf("Model saved in saved_model.raw!\n");
        key_state_io[0] = false;
    }
    if (key_state_io[1]) {
        m.load((char*)"./model/model.raw");
        initBuffersGL();
        printf("Model loaded from model.raw!\n");
        key_state_io[1] = false;
    }
}

void handle_mouse_click() {
    if (left_click) {
        printf("Clicked!\n");
        left_click = false;
    }
}

namespace modellingMode {
    void renderGL() {
        handle_io();
        handle_mouse_click();
    }
};

