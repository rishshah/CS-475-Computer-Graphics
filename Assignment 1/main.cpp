#include "main.hpp"

//extern variables
GLuint shaderProgram = 0;
glm::mat4 modelview_matrix = glm::mat4(1.0f);
GLuint uModelViewMatrix = 0;
bool mode_inspection = false;

//global variables
glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 4.0f);
glm::vec3 camera_target = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 look_at_vec = glm::vec3(0.0f, 1.0f, 0.0f);

glm::mat4 projection_matrix;
glm::mat4 camera_matrix;

void load_shader_program() {
    std::string vertex_shader_file("./shaders/vshader.glsl");
    std::string fragment_shader_file("./shaders/fshader.glsl");

    std::vector<GLuint> shaderList;
    shaderList.push_back(base::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
    shaderList.push_back(base::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

    shaderProgram = base::CreateProgramGL(shaderList);
    glUseProgram( shaderProgram );
}

void hanldle_projection(bool ortho) {
    if (ortho)
        projection_matrix = glm::ortho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
    else
        projection_matrix = glm::perspective(glm::radians(60.0f), 1.0f / 1.0f, 0.1f, 100.0f);
}

void hanldle_camera(){
    camera_matrix = glm::lookAt(camera_position, camera_target, look_at_vec);
}

void renderGL(GLFWwindow* window){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    hanldle_camera();
    hanldle_projection(false);  

    if(mode_inspection)
        inspectMode::renderGL();
    else
        modellingMode::renderGL(window);  

    modelview_matrix = projection_matrix * camera_matrix * translation_matrix * rotation_matrix;
    glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));

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

    //Keyboard and Mouse Callback
    glfwSetKeyCallback(window, base::key_callback);
    glfwSetMouseButtonCallback(window, base::mouse_callback);
    //Framebuffer resize callback
    glfwSetFramebufferSizeCallback(window, base::framebuffer_size_callback);

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //Initialize GL state
    base::initGL();

    load_shader_program();

    // Loop until the user closes the window
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