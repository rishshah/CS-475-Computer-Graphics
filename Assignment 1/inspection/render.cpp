#include "render.hpp"

// Translation Parameters
GLfloat xpos = 0.0, ypos = 0.0, zpos = 0.0;
const GLfloat TRANS_DELTA = 0.04;
//X     0 -> A      1 -> D
//Y     2 -> W      3 -> S
//Z     4 -> Z      5 -> X

// Rotation Parameters
GLfloat xrot = 0.0, yrot = 0.0, zrot = 0.0;
const GLfloat ROT_DELTA = 0.04;
//X     0 -> Up     1 -> Down
//Y     2 -> Left   3 -> Right
//Z     4 -> pgUp   5 -> PgDown


//extern variables
glm::mat4 rotation_matrix = glm::mat4(1.0f);
glm::mat4 translation_matrix = glm::mat4(1.0f);

std::vector<bool> key_state_translation(6, false);
std::vector<bool> key_state_rotation(6, false);
bool key_state_recenter = false;

//-----------------------------------------------------------------

void handle_rotation() {
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

namespace inspectMode {
    void renderGL() {
        handle_rotation();
        handle_translation();
    }
};
