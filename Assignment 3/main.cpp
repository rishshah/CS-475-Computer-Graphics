#include "main.hpp"
#include <vector>

//Externed variables defined here
GLuint shaderProgram = 0;
Scene scene;

std::vector<bool> key_state_trans_or_scale(6, false);
std::vector<bool> key_state_rotation(6, false);

bool key_state_recenter = false;
bool key_state_scaling_mode = false;

bool pan_mode = true;
bool modelling_mode = false;

HeirarchicalModel* curr_heirarchical_model = NULL;
Model* curr_model = NULL;
Model* sky_model = NULL;

//-----------------------------------------------


/**
 * @brief      Adjust rotation matrix according to key_state_rotation shared
 *             variable
 */
void handle_rotation() {
    if (pan_mode)
        scene.rotate(key_state_rotation);
    else if (modelling_mode)
        curr_model->rotate(key_state_rotation);
}

/**
 * @brief      Adjust translation matrix according to key_state_recenter and
 *             key_state_trans_or_scale shared variables
 */
void handle_translation_and_scaling() {
    if (pan_mode)
        scene.trans_scale(key_state_trans_or_scale, key_state_recenter, key_state_scaling_mode);
}

/**
 * @brief      Display everything and handle third-person-view matrix callbacks continuously
 */
void renderGL(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    if (scene.model_list.size() > 0) {
        handle_translation_and_scaling();
        handle_rotation();
        sky_model->rotate(std::vector<bool>{0, 0, 1, 0, 0, 0});
        scene.draw();
    }
}

void set_up_scene(){
    scene.init();
    scene.load_new_model("body", "scene", glm::vec3(10,10,10), glm::vec3(0,0,0));
    sky_model = scene.find_heirarchical_model_by_id("scene")->find_by_id("sky");
    scene.load_new_model("body", "phineas", glm::vec3(1,1,1), glm::vec3(0,2.7,2));
    scene.load_new_model("body", "perry", glm::vec3(1,1,1), glm::vec3(0,1.3,0));
}

int main() {
    //! The pointer to the GLFW window;
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
    window = glfwCreateWindow(700, 700, "CS475 Assignment 3: Modelling, Shading and Texturing", NULL, NULL);
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

    set_up_scene();

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
