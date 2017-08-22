#ifndef _INSPECTION_RENDER_HPP_
#define _INSPECTION_RENDER_HPP_

#include "../main.hpp"

const glm::vec4 X_UNIT = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
const glm::vec4 Z_UNIT = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
const glm::vec4 Y_UNIT = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
extern GLfloat xpos, ypos, zpos;
/**
 * @brief      { Adjust rotation matrix in inspection mode according to
 *             key_state_rotation shared variable}
 */
void handle_rotation();
/**
 * @brief      { Adjust translation matrix according to key_state_recenter and
 *             key_state_translation shared variables}
 */
void handle_translation();


namespace inspectMode{
    /**
     * @brief      { Use current buffer ofject and render the image in
     *             inspection mode}
     */
    void renderGL();
};

#endif
