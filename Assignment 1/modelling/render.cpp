#include "render.hpp"

//extern variables
Model m;
GLuint vbo = 0, vao = 0;
std::vector<bool> key_state_io(6, false);
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

void print_abs_rel_cursor_pos(GLFWwindow* window, float &x, float &y){
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    int width, height;
    std::cout << xpos << " " << ypos << "\n";
    glfwGetWindowSize(window, &width, &height);
    float xwid = width/2.0;
    float yht = height/2.0;
    x = int((xpos - xwid)*100/xwid + 0.5)/50.0 ;
    y = -int((ypos - yht)*100/yht + 0.5)/50.0 ;
    std::cout << x << " " << y << "\n" ;
}

void add_point_to_buffer(float x, float y){
    float z = 0.5;
    m.num_of_vertices++;
    m.vertex_list.resize(m.num_of_vertices);
    m.vertex_list[m.num_of_vertices-1].position = glm::vec3(x, y, z);
    m.vertex_list[m.num_of_vertices-1].color = glm::vec3(m.red_value, m.green_value, m.blue_value);
    if(m.num_of_vertices>=3){
        m.num_of_triangles++;
        m.configuration_list.resize(3 * m.num_of_triangles);
        m.configuration_list[3*m.num_of_triangles -3] = m.num_of_vertices-3;
        m.configuration_list[3*m.num_of_triangles -2] = m.num_of_vertices-2;
        m.configuration_list[3*m.num_of_triangles -1] = m.num_of_vertices-1;
        m.combine_configuration_and_vertices();
        initBuffersGL();
    }
}

void remove_point_from_buffer(void){
    m.num_of_vertices--;
    m.vertex_list.resize(m.num_of_vertices);
    int last_triangle = 0;
    for(int h = 0; h < 3 * m.num_of_triangles; h++){
        if(m.configuration_list[h]==m.num_of_vertices){
            last_triangle = h/3;
            m.num_of_triangles=last_triangle;
            m.configuration_list.resize(3 * m.num_of_triangles);
            m.combine_configuration_and_vertices();
            initBuffersGL();
            break;
        }
    }
}

void handle_io(GLFWwindow* window) {
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
    if (key_state_io[2]) {
        if(left_click){
            printf("Shift + Left Click \n");
            float x, y;
            print_abs_rel_cursor_pos(window, x, y);            
            remove_point_from_buffer();
            left_click = false;
        }
    }
    if ( key_state_io[3] ){
        if(key_state_io[2]){
            if(m.red_value >= 0.09){
                m.red_value-=0.1;
            }
            key_state_io[3] = false;
        }
        else{
            if(m.red_value <= 0.91){
                m.red_value+=0.1;
            }
            key_state_io[3] = false;   
        }
        printf("Red value is %f \n", m.red_value);
    }
    if ( key_state_io[4] ){
        if(key_state_io[2]){
            if(m.green_value >= 0.09){
                m.green_value-=0.1;
            }
            key_state_io[4] = false;
        }
        else{
            if(m.green_value <= 0.91){
                m.green_value+=0.1;
            }
            key_state_io[4] = false;   
        }
        printf("Green value is %f \n", m.green_value);
    }
    if ( key_state_io[5] ){
        if(key_state_io[2]){
            if(m.blue_value >= 0.09){
                m.blue_value-=0.1;
            }
            key_state_io[5] = false;
        }
        else{
            if(m.blue_value <= 0.91){
                m.blue_value+=0.1;
            }
            key_state_io[5] = false;   
        }
        printf("Blue value is %f \n", m.blue_value);
    }
}

void handle_mouse_click(GLFWwindow* window) {
    if (left_click && !key_state_io[2]) {
        printf("Clicked!\n");
        float x, y;
        print_abs_rel_cursor_pos(window, x, y);
        add_point_to_buffer(x, y);
        left_click = false;
    }
}


namespace modellingMode {
    void renderGL(GLFWwindow* window) {
        handle_io(window);
        handle_mouse_click(window);
    }
};

