#ifndef _MAIN_HPP_
#define _MAIN_HPP__

#include <iostream>
#include <vector>

#include "./framework/gl_framework.hpp"
#include "./shader_utils/shader_util.hpp"

#include "./model/model.hpp"
#include "./callbacks/callbacks.hpp"

#include "../glm/vec3.hpp"
#include "../glm/vec4.hpp"
#include "../glm/mat4x4.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"


extern GLuint shaderProgram;
extern Scene scene;
extern glm::mat4 rotation_matrix;
extern float xp;


//-------------------------------------------------------------------------
#endif
