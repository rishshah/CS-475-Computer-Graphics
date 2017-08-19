#ifndef _MAIN_HPP_
#define _MAIN_HPP__

#include <iostream>
#include <vector>

#include "./framework/gl_framework.hpp"
#include "./model/model.hpp"
#include "./model/grid.hpp"
#include "./shader_utils/shader_util.hpp"

#include "./callbacks/callbacks.hpp"
#include "./callbacks/inspection_callbacks.hpp"
#include "./callbacks/modelling_callbacks.hpp"

#include "./modelling/render.hpp"
#include "./inspection/render.hpp"

#include "../glm/vec3.hpp"
#include "../glm/vec4.hpp"
#include "../glm/mat4x4.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

extern GLuint shaderProgram;  // Defined in main, changed in modelling callbacks
extern GLuint vbo, vao;		  // Defined/changed in modelling callbacks


extern glm::mat4 perspective_projection_matrix;
extern glm::mat4 ortho_projection_matrix;
extern glm::mat4 camera_matrix;
// Defined/changed in inspection callbacks
extern glm::mat4 rotation_matrix;
extern glm::mat4 translation_matrix;

extern glm::mat4 modelview_matrix;
extern GLuint uModelViewMatrix;

// Defined/changed in modelling callbacks
extern Model m;
namespace base {
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, int button, int action, int mods);
};
//-------------------------------------------------------------------------
#endif
