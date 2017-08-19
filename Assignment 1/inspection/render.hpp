#ifndef _INSPECTION_RENDER_HPP_
#define _INSPECTION_RENDER_HPP_

#include "../main.hpp"

const glm::vec4 X_UNIT = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
const glm::vec4 Z_UNIT = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
const glm::vec4 Y_UNIT = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

namespace inspectMode{
    void renderGL();
};

#endif
