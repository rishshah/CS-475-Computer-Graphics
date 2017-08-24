#include "render.hpp"

// Step rotation and translation
const float ROT_90 = glm::half_pi<float>();
const float FIXED_TRANS_DELTA = 0.1;

// For handling distance in out of plane direction
float z = 0.0;

// For handling modes of entry
int vertex_num_to_start = 0;
int mode = 0;

std::vector<int> prevmodes(1, 0);
std::vector<int> mode_indexes(1, 0);

// For handling color values
float red_value = 1.0;
float green_value = 1.0;
float blue_value = 1.0;

// For handling drawn points buffer
GLuint vbo_point = 0;
GLuint vao_point = 0;
std::vector<glm::vec3> mouse_point_position(2);
std::vector<glm::vec3> mouse_point_color(2, glm::vec3(1.0f, 1.0f, 1.0f));

// Extern variables
std::vector<bool> key_state_io(3, false);
std::vector<bool> key_state_color(6, false);
std::vector<bool> key_state_entry(3, false);

bool left_click = false;
bool key_state_mouse_location = false;

//-----------------------------------------------------------------


/**
 * @brief      Generate and assign vertex buffer objects and vertex array objects for the model according to vertex_list
 */
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


/**
 * @brief      This function is called when a mouse click occurs. It gives the x-coordinate and y-coordinate, in relative terms to the window size.
 *
 * @param      window  The window from which we will get cursor position
 * @param      x       The x-coordinate on the screen in the range -2,2 which is passed by reference and set in this function
 * @param      y       The y-coordinate on the screen in the range -2,2 which is passed by reference and set in this function
 */
void print_abs_rel_cursor_pos(GLFWwindow* window, float &x, float &y) {
    double x_pos, y_pos;
    glfwGetCursorPos(window, &x_pos, &y_pos);
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    float xwid = width / 2.0;
    float yht = height / 2.0;
    x = int((x_pos - xwid) * 100 / xwid + 0.5) / 50.0 ;
    y = -int((y_pos - yht) * 100 / yht + 0.5) / 50.0 ;

    //Point snapping
    x = round(x * 10) / 10.0;
    y = round(y * 10) / 10.0;
}


/**
 * @brief      This function is used to determine how to add points to vertex list of model based on triangle mode, strip mode or fan mode
 *
 * @param[in]  v     Latest vertex created by user on mouse click
 */
void modify_configurations(Vertex v) {
    if (prevmodes.rbegin()[0] != mode) {
        prevmodes.push_back(mode);
        mode_indexes.push_back(m.vertex_list.size() / 3);
    }
    if (mode == 0) {
        m.vertex_list.push_back(v);
        if (m.vertex_list.size() % 3 == 0) {
            initBuffersGL();
        }
    }
    else if (mode == 1) {
        if (mode_indexes.rbegin()[0] == m.vertex_list.size() / 3) {
            m.vertex_list.push_back(v);
            if (m.vertex_list.size() % 3 == 0) {
                initBuffersGL();
            }
        }
        else {
            m.vertex_list.push_back(m.vertex_list.rbegin()[1]);
            m.vertex_list.push_back(m.vertex_list.rbegin()[1]);
            m.vertex_list.push_back(v);
            initBuffersGL();
        }
    }
    else if (mode == 2) {
        if (mode_indexes.rbegin()[0] == m.vertex_list.size() / 3) {
            m.vertex_list.push_back(v);
            if (m.vertex_list.size() % 3 == 0) {
                initBuffersGL();
            }
        }
        else {
            m.vertex_list.push_back(m.vertex_list[(mode_indexes.rbegin()[0]) * 3]);
            m.vertex_list.push_back(m.vertex_list.rbegin()[1]);
            m.vertex_list.push_back(v);
            initBuffersGL();
        }
    }
    return;
}


/**
 * @brief      Based on window relative x & y coordinates obtained from print_abs_rel_cursor_pos(), the translation matrix & the rotation matrix,
 * This function calculates the actual 3d position of the latest vertex to be added to buffer. Then calls modify_configuration() which adds vertex to vertex_list.
 *  
 *
 * @param[in]  x     The x-coordinate obtained from print_rel_abs_pos()
 * @param[in]  y     The y-coordinate obtained from print_rel_abs_pos()
 */
void add_point_to_buffer(float x, float y) {
    Vertex v;
    v.position = glm::vec3( glm::transpose(rotation_matrix) * glm::vec4(x - xpos, y - ypos, z - zpos, 1.0));
    printf("Real position on screen: %.1f \t %.1f \t %.1f\n", v.position.x, v.position.y, v.position.z);
    v.color = glm::vec3(red_value, green_value, blue_value);
    modify_configurations(v);
    m.calc_centroid();
}


/**
 * @brief      Based on previous modes of drawing triangles, this function carefully removes the previously added point.
 */
void remove_point_from_buffer(void) {
    if (m.vertex_list.empty()) {
        return;
    }
    if (m.vertex_list.size() % 3 != 0) {
        m.vertex_list.pop_back();
    }
    else {
        int the_mode;
        while (1) {
            the_mode = prevmodes.rbegin()[0];
            if (m.vertex_list.size() / 3 > mode_indexes.rbegin()[0]) {
                if ( the_mode == 0 ) {
                    m.vertex_list.pop_back();
                    initBuffersGL();
                    break;
                }
                else if (m.vertex_list.size() / 3 == mode_indexes.rbegin()[0] + 1) {
                    m.vertex_list.pop_back();
                    initBuffersGL();
                    break;
                }
                else
                {
                    m.vertex_list.pop_back();
                    m.vertex_list.pop_back();
                    m.vertex_list.pop_back();
                    initBuffersGL();
                    break;
                }
            }
            else {
                if ( prevmodes.size() == 1) {
                    break;
                }
                mode_indexes.pop_back();
                prevmodes.pop_back();
                continue;
            }
        }
    }
}


/**
 * @brief      Similar to initBuffersGL, but for displaying last 2 mouse points
 */
void draw_last_mouse_click() {
    glGenBuffers (1, &vbo_point);
    glBindBuffer (GL_ARRAY_BUFFER, vbo_point);

    glGenVertexArrays (1, &vao_point);
    glBindVertexArray (vao_point);

    GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
    glEnableVertexAttribArray( vPosition );

    GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" );
    glEnableVertexAttribArray( vColor );

    glBufferData (GL_ARRAY_BUFFER, 4 * sizeof(glm::vec3) , NULL, GL_STATIC_DRAW);
    glBufferSubData( GL_ARRAY_BUFFER, 0, 2 * sizeof(glm::vec3), &mouse_point_position[0] );
    glBufferSubData( GL_ARRAY_BUFFER, 2 * sizeof(glm::vec3), 2 * sizeof(glm::vec3), &mouse_point_color[0] );

    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(2 * sizeof(glm::vec3)) );
}

//-----------------------------------------------------------------

/**
 * @brief      In modelling mode, whenever up, down, left, right, Pg Up, Pg Dn is pressed, this function calculates the change on the rotation matrix and updates it. 
 */
void handle_fixed_rotation() {
    if (key_state_rotation[0]) {
        rotation_matrix = glm::rotate(rotation_matrix, -ROT_90, glm::vec3(glm::transpose(rotation_matrix) * X_UNIT));
        key_state_rotation[0] = false;
    }
    else if (key_state_rotation[1]) {
        rotation_matrix = glm::rotate(rotation_matrix, ROT_90, glm::vec3(glm::transpose(rotation_matrix) * X_UNIT));
        key_state_rotation[1] = false;
    }

    if (key_state_rotation[2]) {
        rotation_matrix = glm::rotate(rotation_matrix, -ROT_90, glm::vec3(glm::transpose(rotation_matrix) * Y_UNIT));
        key_state_rotation[2] = false;
    }
    else if (key_state_rotation[3]) {
        rotation_matrix = glm::rotate(rotation_matrix, ROT_90, glm::vec3(glm::transpose(rotation_matrix) * Y_UNIT));
        key_state_rotation[3] = false;
    }

    if (key_state_rotation[4]) {
        rotation_matrix = glm::rotate(rotation_matrix, ROT_90, glm::vec3(glm::transpose(rotation_matrix) * Z_UNIT));
        key_state_rotation[4] = false;
    }
    else if (key_state_rotation[5]) {
        rotation_matrix = glm::rotate(rotation_matrix, -ROT_90, glm::vec3(glm::transpose(rotation_matrix) * Z_UNIT));
        key_state_rotation[5] = false;
    }
}


/**
 * @brief      In modelling mode, whenever W, A, S, D is pressed, this function calculates the change on the translation matrix and updates it.       
 */
void handle_fixed_translation() {
    if (key_state_translation[0]) {
        xpos -= FIXED_TRANS_DELTA;
    }
    else if (key_state_translation[1]) {
        xpos += FIXED_TRANS_DELTA;
    }

    if (key_state_translation[2]) {
        ypos += FIXED_TRANS_DELTA;
    }
    else if (key_state_translation[3]) {
        ypos -= FIXED_TRANS_DELTA;
    }

    translation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, zpos));
}


/**
 * @brief      Handles the 3rd dimension. Updates the z coordinate when z or x is pressed with or without left shift.
 */
void handle_depth() {
    if (key_state_translation[4]) {
        if (!key_state_io[2])
            z += 1;
        else
            z += 0.1;
        printf("z plane at %f \n ", z);
        key_state_translation[4] = false;
    }
    else if (key_state_translation[5]) {
        if (!key_state_io[2])
            z -= 1;
        else
            z -= 0.1;
        printf("z plane at %f \n ", z);
        key_state_translation[5] = false;
    }
}


/**
 * @brief      Handles Color changes for the next vertex to be drawn. For increase & decrease in R, G, B values by 0.5, use the keys (R,T) ; (G,H) ; (B,N) respectively. The range for the color values is from (0,1). Press left shift along with the previous keys to alter the values by 0.1 instead of 0.5 
 *               
 */
void handle_color() {
    if ( key_state_color[0] ) {
        if (key_state_io[2])
            red_value += 0.1 ;
        else
            red_value += 0.5 ;
        key_state_color[0] = false;

        if (red_value >= 1.0)
            red_value = 1.0;

        printf("Red value is %f \n", red_value);

    }

    else if ( key_state_color[1] ) {
        if (key_state_io[2])
            green_value += 0.1 ;
        else
            green_value += 0.5 ;
        key_state_color[1] = false;

        if (green_value >= 1.0)
            green_value = 1.0;

        printf("Green value is %f \n", green_value);
    }

    else if ( key_state_color[2] ) {
        if (key_state_io[2])
            blue_value += 0.1 ;
        else
            blue_value += 0.5 ;
        key_state_color[2] = false;

        if (blue_value >= 1.0)
            blue_value = 1.0;

        printf("Blue value is %f \n", blue_value);
    }

    else if ( key_state_color[3] ) {
        if (key_state_io[2])
            red_value -= 0.1 ;
        else
            red_value -= 0.5 ;
        key_state_color[3] = false;

        if (red_value <= 0.0)
            red_value = 0.0;

        printf("Red value is %f \n", red_value);

    }

    else if ( key_state_color[4] ) {
        if (key_state_io[2])
            green_value -= 0.1 ;
        else
            green_value -= 0.5 ;
        key_state_color[4] = false;

        if (green_value <= 0.0)
            green_value = 0.0;

        printf("Green value is %f \n", green_value);
    }

    else if ( key_state_color[5] ) {
        if (key_state_io[2])
            blue_value -= 0.1 ;
        else
            blue_value -= 0.5 ;
        key_state_color[5] = false;

        if (blue_value <= 0.0)
            blue_value = 0.0;

        printf("Blue value is %f \n", blue_value);
    }
}


/**
 * @brief      Press 1, 2, 3 to switch to Triangle mode, Strip mode, Fan mode respectively. 
 */

void handle_entry_mode() {
    if (key_state_entry[0]) {
        printf("Entry Mode: GL_TRIANGLES\n");
        mode = 0;
        mode_indexes.push_back(m.vertex_list.size() / 3);
        prevmodes.push_back(0);
        key_state_entry[0] = false;
    }
    if (key_state_entry[1]) {
        printf("Entry Mode: GL_STRIP\n");
        mode = 1;
        mode_indexes.push_back(m.vertex_list.size() / 3);
        prevmodes.push_back(1);
        key_state_entry[1] = false;
    }
    if (key_state_entry[2]) {
        printf("Entry Mode: GL_FAN\n");
        mode = 2;
        mode_indexes.push_back(m.vertex_list.size() / 3);
        prevmodes.push_back(2);
        key_state_entry[2] = false;
    }
}


/**
 * @brief      Function to detect Key press on K for Saving model to saved_model.raw, L for loading model from model.raw
 */
void handle_io() {
    if (key_state_io[0]) {
        if (m.save())
            printf("Model saved!");
        key_state_io[0] = false;
    }
    if (key_state_io[1]) {
        if (m.load())
            printf("Model loaded!");
        initBuffersGL();
        key_state_io[1] = false;
    }
}


/**
 * @brief      Handle mouse Click. Call function to add or remove points based on whether left shift was pressed.
 *
 * @param      window  The window
 */
void handle_mouse_click(GLFWwindow* window) {
    if (left_click && !key_state_io[2]) {
        float x, y;
        print_abs_rel_cursor_pos(window, x, y);

        // handle drawn point buffer
        mouse_point_position[1] = mouse_point_position[0];
        mouse_point_position[0] = glm::vec3(glm::transpose(rotation_matrix) * glm::vec4(x - xpos, y - ypos, z - zpos, 1.0));

        mouse_point_color[1] = mouse_point_color[0];
        mouse_point_color[0] = glm::vec3(red_value, green_value, blue_value);

        draw_last_mouse_click();
        add_point_to_buffer(x, y);
        left_click = false;
        printf("Point added!\n");
    }
    if (key_state_io[2] and left_click) {
        float x, y;
        print_abs_rel_cursor_pos(window, x, y);

        // handle drawn point buffer
        mouse_point_position[0] = mouse_point_position[1];
        mouse_point_color[0] = mouse_point_color[1];

        if (m.vertex_list.size() >= 3) {
            mouse_point_position[1] = glm::vec3(glm::transpose(rotation_matrix) * glm::vec4(m.vertex_list[m.vertex_list.size() - 3].position, 1.0));
            mouse_point_color[1] = m.vertex_list[m.vertex_list.size() - 3].color;
        } else {
            mouse_point_position[1] = glm::vec3(0.0f, 0.0f, 0.0f);
            mouse_point_color[1] = glm::vec3(1.0f, 1.0f, 1.0f);
        }

        draw_last_mouse_click();
        remove_point_from_buffer();
        left_click = false;
        printf("Point removed!\n");
    }
}


/**
 * @brief      When ctrl is pressed, display the x,y,z coordinates of curreny location of mouse. 
 *
 * @param      window  The window
 */
void handle_mouse_location(GLFWwindow* window) {
    if (key_state_mouse_location) {
        float x, y;
        print_abs_rel_cursor_pos(window, x, y);
        Vertex v;
        v.position = glm::vec3( glm::transpose(rotation_matrix) * glm::vec4(x - xpos, y - ypos, z - zpos, 1.0));
        printf("Real position on screen: %.1f \t %.1f \t %.1f\n", v.position.x, v.position.y, v.position.z);
        key_state_mouse_location = false;
    }
}

//-----------------------------------------------------------------


/**
 * @brief     Ensure when object is translated or rotated, the object showing last mouse click also moves. 
 */
void render_last_mouse_point() {
    if (vao_point != 0) {
        glPointSize(4.0f);
        glBindVertexArray(vao_point);
        modelview_matrix = ortho_projection_matrix * translation_matrix * rotation_matrix;
        glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
        glDrawArrays(GL_POINTS, 0, 2);
    }
}

namespace modellingMode {

/**
 * @brief      render model in modelling mode
 *
 * @param      window  The window
 */
void renderGL(GLFWwindow* window) {
    // Load and Save the model
    handle_io();

    // Add/Delete Model and selecct entry mode
    handle_mouse_click(window);
    handle_entry_mode();

    // Extra features
    handle_mouse_location(window);
    render_last_mouse_point();
    handle_depth();
    handle_color();

    //Modelling mode translation and rotation
    handle_fixed_rotation();
    handle_fixed_translation();

    // Render model in modelling mode
    modelview_matrix = ortho_projection_matrix * translation_matrix * rotation_matrix;
    glBindVertexArray(vao);
    glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
    glDrawArrays(GL_TRIANGLES, 0, m.vertex_list.size());
}
};

