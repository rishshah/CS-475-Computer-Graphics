#include "main.hpp"
#include <vector>

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

std::vector<glm::vec3> grid_points_position;
std::vector<glm::vec3> grid_points_color;
GLuint vbo_grid;
GLuint vao_grid;

void drawgrid() {
    glGenBuffers (1, &vbo_grid);
    glBindBuffer (GL_ARRAY_BUFFER, vbo_grid);

    glGenVertexArrays (1, &vao_grid);
    glBindVertexArray (vao_grid);

    GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
    glEnableVertexAttribArray( vPosition );

    GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" );
    glEnableVertexAttribArray( vColor );

    size_t size_points = sizeof(glm::vec3) * grid_points_position.size();

    glBufferData (GL_ARRAY_BUFFER, 2 * size_points , NULL, GL_STATIC_DRAW);
    glBufferSubData( GL_ARRAY_BUFFER, 0, size_points, &grid_points_position[0] );
    glBufferSubData( GL_ARRAY_BUFFER, size_points, size_points, &grid_points_color[0] );

    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(size_points) );
}

void initgrid() {
    for (float x = -1; x < 1.01; x += 0.1) {
        grid_points_position.push_back(glm::vec3(x, 1.0f, 0.0f));
        grid_points_position.push_back(glm::vec3(x, -1.0f, 0.0f));

        grid_points_color.push_back(glm::vec3(0.2f, 0.2f, 0.2f));
        grid_points_color.push_back(glm::vec3(0.2f, 0.2f, 0.2f));
    }
    for (float y = -1; y < 1.01; y += 0.1) {
        grid_points_position.push_back(glm::vec3(1.0f, y, 0.0f));
        grid_points_position.push_back(glm::vec3(-1.0f, y, 0.0f));

        grid_points_color.push_back(glm::vec3(0.2f, 0.2f, 0.2f));
        grid_points_color.push_back(glm::vec3(0.2f, 0.2f, 0.2f));
    }
    drawgrid();
}

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

void hanldle_camera() {
    camera_matrix = glm::lookAt(camera_position, camera_target, look_at_vec);
}

void renderGL(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (mode_inspection) {
        hanldle_projection(false);
        inspectMode::renderGL();
        hanldle_camera();
        modelview_matrix = projection_matrix * camera_matrix * translation_matrix * rotation_matrix;
    }
    else {
        hanldle_projection(true);
        modellingMode::renderGL(window);
        modelview_matrix = projection_matrix * translation_matrix * rotation_matrix;
    }

    glBindVertexArray(vao);
    glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
    glDrawArrays(GL_TRIANGLES, 0, m.num_of_triangles * 3);


    if (!mode_inspection) {
        glBindVertexArray(vao_grid);
        modelview_matrix = glm::mat4(1.0f);
        glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
        glDrawArrays(GL_LINES, 0, grid_points_position.size());
    }
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
    initgrid();
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