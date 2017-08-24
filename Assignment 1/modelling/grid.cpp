#include "grid.hpp"

std::vector<glm::vec3> grid_points_position;
std::vector<glm::vec3> grid_points_color;
GLuint vbo_grid;
GLuint vao_grid;

namespace modellingMode {

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

void render_grid() {
    glBindVertexArray(vao_grid);
    modelview_matrix = glm::mat4(1.0f);
    glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
    glDrawArrays(GL_LINES, 0, grid_points_position.size());
}
}