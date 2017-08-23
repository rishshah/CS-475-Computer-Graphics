#include "render.hpp"

const float ROT_90 = glm::half_pi<float>();
const float FIXED_TRANS_DELTA = 0.1;

float z = 0.0;
int vertex_num_to_start = 0;
int mode = 0;

//extern variables
std::vector<bool> key_state_io(3, false);
std::vector<bool> key_state_color(3, false);
std::vector<bool> key_state_entry(3, false);
std::vector<int> prevmodes(1,0);
std::vector<int> mode_indexes(1,0);
// std::prevmodes.resize(0);
// std::mode_indexes.resize(0);

bool left_click = false;
bool key_state_mouse_location = false;


std::vector<glm::vec3> mouse_point_position(2);
std::vector<glm::vec3> mouse_point_color(2, glm::vec3(1.0f, 1.0f, 1.0f));

GLuint vbo_point = 0;
GLuint vao_point = 0;

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

void print_abs_rel_cursor_pos(GLFWwindow* window, float &x, float &y) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    int width, height;
    // std::cout << xpos << " " << ypos << "\n";
    glfwGetWindowSize(window, &width, &height);
    float xwid = width / 2.0;
    float yht = height / 2.0;
    x = int((xpos - xwid) * 100 / xwid + 0.5) / 50.0 ;
    y = -int((ypos - yht) * 100 / yht + 0.5) / 50.0 ;
    x = round(x * 10) / 10.0;
    y = round(y * 10) / 10.0;
    printf("%.1f \t %.1f \t %.1f\n", x, y, z);
}

void modify_configurations(Vertex v) {
    if (mode == 0) {
        m.vertex_list.push_back(v);
        if(m.vertex_list.size()%3==0){
        	//m.num_of_triangles++;
   			m.segregate_vertices();
   			initBuffersGL();
   	    	// create triangle
        }
    }
    else if (mode == 1) {
        if(mode_indexes.rbegin()[0]==m.vertex_list.size()/3){
        	m.vertex_list.push_back(v);
        	if(m.vertex_list.size()%3==0){
        		//m.num_of_triangles++;
        		m.segregate_vertices();
        		initBuffersGL();
        		// create triangle
        	}
        }
        else{
        	//m.num_of_triangles++;
        	m.vertex_list.push_back(m.vertex_list.rbegin()[1]);
        	m.vertex_list.push_back(m.vertex_list.rbegin()[1]);
        	m.vertex_list.push_back(v);
        	m.segregate_vertices();
        	initBuffersGL();
        }
    }
    else if (mode == 2) {
     	if(mode_indexes.rbegin()[0]==m.vertex_list.size()/3){
        	m.vertex_list.push_back(v);
        	if(m.vertex_list.size()%3==0){
        		//m.num_of_triangles++;
        		m.segregate_vertices();
        		initBuffersGL();
        		// create triangle
        	}
        }
        else{
        	//m.num_of_triangles++;
        	m.vertex_list.push_back(m.vertex_list[(mode_indexes.rbegin()[0])*3]);
        	m.vertex_list.push_back(m.vertex_list.rbegin()[1]);
        	m.vertex_list.push_back(v);
        	m.segregate_vertices();
        	initBuffersGL();
        }   
    }
    return;
}

void add_point_to_buffer(float x, float y) {
    Vertex v;
    v.position = glm::vec3( glm::transpose(rotation_matrix) * glm::vec4(x, y, z, 1.0));
    v.color = glm::vec3(m.red_value, m.green_value, m.blue_value);
    modify_configurations(v);
    m.calc_centroid();
}

void remove_point_from_buffer(void) {
	
	std::cout << m.vertex_list.size() << prevmodes.size() << mode_indexes.size() << "\n";
	if(m.vertex_list.empty()){
    	return;
    }
    if(prevmodes.empty()){
    	return;
    }
    if(m.vertex_list.size()%3!=0){
    	m.vertex_list.pop_back();	
    }
    else{
    	int the_mode;
    	while(1){
    		the_mode = prevmodes.rbegin()[0];
			if(m.vertex_list.size()/3 > mode_indexes.rbegin()[0]){
				if ( the_mode == 0 ) {
					//m.num_of_triangles--;
					m.vertex_list.pop_back();
					m.segregate_vertices();
					initBuffersGL();
					break;
				}
				else if(m.vertex_list.size()/3==mode_indexes.rbegin()[0]+1){
					m.vertex_list.pop_back();
					m.segregate_vertices();
					initBuffersGL();
					break;	
				}
				else
				{
					//m.num_of_triangles--;
					m.vertex_list.pop_back();
					m.vertex_list.pop_back();
					m.vertex_list.pop_back();
					m.segregate_vertices();
					initBuffersGL();
					break;	
				}
			}
			else{
				mode_indexes.pop_back();
				prevmodes.pop_back();
				continue;
			}
    	}
    }
}
    

//-----------------------------------------------------------------

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

void handle_fixed_translation() {
    if (key_state_recenter) {
        xpos = ypos = zpos = 0.0f;
    }
    else {
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
    }

    translation_matrix = glm::translate(glm::mat4(1.0f), m.centroid + glm::vec3(xpos, ypos, zpos));
}

void handle_depth() {
    if (key_state_recenter == true) {
        z = 0;
    }
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

void handle_color() {
    if ( key_state_color[0] ) {
        if (key_state_io[2]) {
            if (m.red_value >= 0.09) {
                m.red_value -= 0.1;
            }
        }
        else {
            if (m.red_value <= 0.91) {
                m.red_value += 0.1;
            }
        }
        key_state_color[0] = false;
        printf("Red value is %f \n", m.red_value);
    }
    if ( key_state_color[1] ) {
        if (key_state_io[2]) {
            if (m.green_value >= 0.09) {
                m.green_value -= 0.1;
            }
        }
        else {
            if (m.green_value <= 0.91) {
                m.green_value += 0.1;
            }
        }
        key_state_color[1] = false;
        printf("Green value is %f \n", m.green_value);
    }
    if ( key_state_color[2] ) {
        if (key_state_io[2]) {
            if (m.blue_value >= 0.09) {
                m.blue_value -= 0.1;
            }
        }
        else {
            if (m.blue_value <= 0.91) {
                m.blue_value += 0.1;
            }
        }
        key_state_color[2] = false;
        printf("Blue value is %f \n", m.blue_value);
    }
}

void handle_entry_mode() {
    if (key_state_entry[0]) {
        printf("Entry Mode: GL_TRIANGLES\n");
        mode = 0;
        mode_indexes.push_back(m.vertex_list.size()/3);
        prevmodes.push_back(0);
        key_state_entry[0] = false;
    }
    if (key_state_entry[1]) {
        printf("Entry Mode: GL_STRIP\n");
        mode = 1;
        mode_indexes.push_back(m.vertex_list.size()/3);
        prevmodes.push_back(1);
        key_state_entry[1] = false;
    }
    if (key_state_entry[2]) {
        printf("Entry Mode: GL_FAN\n");
        mode = 2;
        mode_indexes.push_back(m.vertex_list.size()/3);
        prevmodes.push_back(2);
        key_state_entry[2] = false;
    }
}

void handle_io() {
    if (key_state_io[0]) {
        m.save((char*)"./binary_models/saved_cricket_bat.raw");
        printf("Model saved in cricket_bat.raw!\n");
        key_state_io[0] = false;
    }
    if (key_state_io[1]) {
        m.load((char*)"./binary_models/cricket_bat.raw");
        initBuffersGL();
        printf("Model loaded from cricket_bat.raw!\n");
        key_state_io[1] = false;
    }
}

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

void handle_mouse_click(GLFWwindow* window) {
    if (left_click && !key_state_io[2]) {
        float x, y;
        print_abs_rel_cursor_pos(window, x, y);
        mouse_point_position[1] = mouse_point_position[0];
        mouse_point_position[0] = glm::vec3(x / 2.0, y / 2.0, 0.0f);
        draw_last_mouse_click();
        add_point_to_buffer(x, y);
        left_click = false;
        printf("Point added!\n");
    }
    if (key_state_io[2] and left_click) {
        float x, y;
        print_abs_rel_cursor_pos(window, x, y);
        mouse_point_position[0] = mouse_point_position[1];
        mouse_point_position[1] = glm::vec3(0.0f, 0.0f, 0.0f);
        remove_point_from_buffer();
        left_click = false;
        printf("Point removed!\n");
    }
}

void render_last_mouse_point() {
    if (vao_point != 0) {
        glPointSize(4.0f);
        glBindVertexArray(vao_point);
        modelview_matrix = glm::mat4(1.0f);
        glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
        glDrawArrays(GL_POINTS, 0, 2);
    }
}

void handle_mouse_location(GLFWwindow* window) {
    if (key_state_mouse_location) {
        float x, y;
        print_abs_rel_cursor_pos(window, x, y);
        key_state_mouse_location = false;
    }
}

namespace modellingMode {

/**
 * @brief      { render model in modelling mode }
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
    modelview_matrix = ortho_projection_matrix * translation_matrix * rotation_matrix * m.centroid_translation_matrix;
    glBindVertexArray(vao);
    glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
    glDrawArrays(GL_TRIANGLES, 0, m.vertex_list.size());
}
};

