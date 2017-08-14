#include "inspect.hpp"

GLuint shaderProgram;
GLuint vbo, vao;

Model m;

glm::mat4 rotation_matrix;
glm::mat4 translation_matrix;

glm::mat4 projection_matrix;
glm::mat4 camera_matrix;

glm::mat4 modelview_matrix;

GLuint uModelViewMatrix;

//-----------------------------------------------------------------
void initBuffersGL() {
    m.load((char*)"./model/model.raw");

    std::string vertex_shader_file("./shaders/vshader.glsl");
    std::string fragment_shader_file("./shaders/fshader.glsl");

    std::vector<GLuint> shaderList;
    shaderList.push_back(base::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
    shaderList.push_back(base::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

    shaderProgram = base::CreateProgramGL(shaderList);
    glUseProgram( shaderProgram );

    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);

    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);

    GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
    glEnableVertexAttribArray( vPosition );

    GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" );
    glEnableVertexAttribArray( vColor );

    m.assignBuffer(vao, vbo, vPosition, vColor);

    uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
}

void handle_roatation() {
    if (key_state_rotation[0]) {
        xrot += ROT_DELTA;
    }
    else if (key_state_rotation[1]) {
        xrot -= ROT_DELTA;
    }

    if (key_state_rotation[2]) {
        yrot += ROT_DELTA;
    }
    else if (key_state_rotation[3]) {
        yrot -= ROT_DELTA;
    }

    if (key_state_rotation[4]) {
        zrot += ROT_DELTA;
    }
    else if (key_state_rotation[5]) {
        zrot -= ROT_DELTA;
    }

    rotation_matrix = glm::rotate(glm::mat4(1.0f), xrot, glm::vec3(1.0f, 0.0f, 0.0f));
    rotation_matrix = glm::rotate(rotation_matrix, yrot, glm::vec3(0.0f, 1.0f, 0.0f));
    rotation_matrix = glm::rotate(rotation_matrix, zrot, glm::vec3(0.0f, 0.0f, 1.0f));
}
void handle_translation() {
    if (key_state_recenter) {
        xpos = ypos = zpos = 0.0f;
    }
    else {
        if (key_state_translation[0]) {
            xpos -= TRANS_DELTA;
        }
        else if (key_state_translation[1]) {
            xpos += TRANS_DELTA;
        }

        if (key_state_translation[2]) {
            ypos += TRANS_DELTA;
        }
        else if (key_state_translation[3]) {
            ypos -= TRANS_DELTA;
        }

        if (key_state_translation[4]) {
            zpos += TRANS_DELTA;
        }
        else if (key_state_translation[5]) {
            zpos -= TRANS_DELTA;
        }
    }
    
    translation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, zpos));
}
void hanldle_projection(bool ortho) {
    if (ortho)
        projection_matrix = glm::ortho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
    else
        projection_matrix = glm::perspective(glm::radians(60.0f), 1.0f / 1.0f, 0.1f, 100.0f);
}
void hanldle_camera() {
    camera_matrix = glm::lookAt(
                        glm::vec3(0.0f, 0.0f, 5.0f),    // the position of your camera, in world space
                        glm::vec3(0.0f, 0.0f, 0.0f),    // where you want to look at, in world space
                        glm::vec3(0.0f, 1.0f, 0.0f)     // probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too
                    );
}

void renderGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    handle_roatation();
    handle_translation();
    hanldle_projection(false);
    hanldle_camera();

    modelview_matrix = projection_matrix * camera_matrix * translation_matrix * rotation_matrix;
    glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
    // Draw
    glDrawArrays(GL_TRIANGLES, 0, m.get_num_of_triangles() * 3);
}

int main() {
    //! The pointer to the GLFW window
    GLFWwindow* window;

    //! Setting up the GLFW Error callback
    glfwSetErrorCallback(base::error_callback);

    //! Initialize GLFW
    if (!glfwInit())
        return -1;

    //We want OpenGL 4.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    //This is for MacOSX - can be omitted otherwise
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //We don't want the old OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //! Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(512, 512, "CS475/CS675 Tutorial 3: Rotating  Colorcube", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    //! Make the window's context current
    glfwMakeContextCurrent(window);

    //Initialize GLEW
    //Turn this on to get Shader based OpenGL
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        //Problem: glewInit failed, something is seriously wrong.
        std::cerr << "GLEW Init Failed : %s" << std::endl;
    }

    //Print and see what context got enabled
    std::cout << "Vendor: " << glGetString (GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString (GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString (GL_VERSION) << std::endl;
    std::cout << "GLSL Version: " << glGetString (GL_SHADING_LANGUAGE_VERSION) << std::endl;

    //Keyboard Callback
    glfwSetKeyCallback(window, base::key_callback);
    //Framebuffer resize callback
    glfwSetFramebufferSizeCallback(window, base::framebuffer_size_callback);

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //Initialize GL state
    base::initGL();
    initBuffersGL();

    // Loop until the user closes the window
    while (glfwWindowShouldClose(window) == 0)
    {

        // Render here
        renderGL();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}