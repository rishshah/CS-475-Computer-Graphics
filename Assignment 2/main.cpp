#include "main.hpp"
#include <vector>

//extern variables
GLuint shaderProgram = 0;
Scene scene;

float xp = 20.0f;
float zp = 100.0f;
float zn = -100.0f;

glm::mat4 ortho_projection_matrix = glm::ortho(-20.0, 20.0, -20.0, 20.0, -100.0, 100.0);

//Scene center
glm::vec3 center;

// Translation  and Rotation Parameters
const float TRANS_DELTA = 0.04;
const float ROT_DELTA = 0.04;

const glm::vec4 X_UNIT = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
const glm::vec4 Y_UNIT = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
const glm::vec4 Z_UNIT = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

//extern variables
glm::mat4 rotation_matrix = glm::mat4(1.0f);
glm::mat4 translation_matrix = glm::mat4(1.0f);

std::vector<bool> key_state_translation(6, false);
std::vector<bool> key_state_rotation(6, false);

bool key_state_recenter = false;

float xpos = 0.0, ypos = 0.0, zpos = 0.0;

void handle_rotation() {
    if (key_state_rotation[0]) {
        rotation_matrix = glm::rotate(rotation_matrix, -ROT_DELTA, glm::vec3(glm::transpose(rotation_matrix) * X_UNIT));
    }
    else if (key_state_rotation[1]) {
        rotation_matrix = glm::rotate(rotation_matrix, ROT_DELTA, glm::vec3(glm::transpose(rotation_matrix) * X_UNIT));
    }

    if (key_state_rotation[2]) {
        rotation_matrix = glm::rotate(rotation_matrix, -ROT_DELTA, glm::vec3(glm::transpose(rotation_matrix) * Y_UNIT));
    }
    else if (key_state_rotation[3]) {
        rotation_matrix = glm::rotate(rotation_matrix, ROT_DELTA, glm::vec3(glm::transpose(rotation_matrix) * Y_UNIT));
    }

    if (key_state_rotation[4]) {
        rotation_matrix = glm::rotate(rotation_matrix, ROT_DELTA, glm::vec3(glm::transpose(rotation_matrix) * Z_UNIT));
    }
    else if (key_state_rotation[5]) {
        rotation_matrix = glm::rotate(rotation_matrix, -ROT_DELTA, glm::vec3(glm::transpose(rotation_matrix) * Z_UNIT));
    }
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
            //zpos += TRANS_DELTA;
            xp -= TRANS_DELTA ;
        }
        else if (key_state_translation[5]) {
            //zpos -= TRANS_DELTA;
            xp += TRANS_DELTA ;
        }
    }

    translation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, zpos));
}


/**
 * @brief      The render function which in turn calls the inspection mode render or modelling mode render depending on the current mode
 */
void renderGL(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ortho_projection_matrix = glm::ortho(-1.0f*xp, xp, -1.0f*xp, xp, zn, zp);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    handle_translation();
    handle_rotation();
    scene.draw(ortho_projection_matrix * glm::translate(glm::mat4(1.0f), scene.center)
               * translation_matrix * rotation_matrix  * glm::translate(glm::mat4(1.0f), -scene.center));
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
    window = glfwCreateWindow(700, 700, "CS475 Assignment 1: Modelling and Inspection", NULL, NULL);
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

    //Keyboard and Mouse Callback
    glfwSetKeyCallback(window, base::key_callback);
    //Framebuffer resize callback
    glfwSetFramebufferSizeCallback(window, base::framebuffer_size_callback);

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //Initialize GL state
    base::initGL();

    //Load shader Program
    std::string vertex_shader_file("./shaders/vshader.glsl");
    std::string fragment_shader_file("./shaders/fshader.glsl");

    std::vector<GLuint> shaderList;
    shaderList.push_back(base::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
    shaderList.push_back(base::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

    shaderProgram = base::CreateProgramGL(shaderList);
    glUseProgram( shaderProgram );

    if (!scene.load())
        return 0;

    while (glfwWindowShouldClose(window) == 0) {

        renderGL(window);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
