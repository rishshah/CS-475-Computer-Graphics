#include "render.hpp"

// Translation  and Rotation Parameters
const GLfloat TRANS_DELTA = 0.04;
const GLfloat ROT_DELTA = 0.04;

//extern variables
glm::mat4 rotation_matrix = glm::mat4(1.0f);
glm::mat4 translation_matrix = glm::mat4(1.0f);

std::vector<bool> key_state_translation(6, false);
std::vector<bool> key_state_rotation(6, false);

bool key_state_recenter = false;

GLfloat xpos = 0.0, ypos = 0.0, zpos = 0.0;

//-----------------------------------------------------------------
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
            zpos += TRANS_DELTA;
        }
        else if (key_state_translation[5]) {
            zpos -= TRANS_DELTA;
        }
    }

    translation_matrix = glm::translate(glm::mat4(1.0f), m.centroid + glm::vec3(xpos, ypos, zpos));
}

namespace inspectMode {
void renderGL() {
    handle_rotation();
    handle_translation();
    modelview_matrix = perspective_projection_matrix * camera_matrix * translation_matrix * rotation_matrix * m.centroid_translation_matrix;
    glBindVertexArray(vao);
    glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
    glDrawArrays(GL_TRIANGLES, 0, m.num_of_triangles * 3);
}
};
