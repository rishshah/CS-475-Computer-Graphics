#ifndef _INSPECTION_MODE_HPP_
#define _INSPECTION_MODE_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include <vector>
#include "../framework/gl_framework.hpp"
#include "../model/model.hpp"
#include "../shader_utils/shader_util.hpp"
#include "../glm/vec3.hpp"
#include "../glm/vec4.hpp"
#include "../glm/mat4x4.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

// Translation Parameters
GLfloat xpos=0.0,ypos=0.0,zpos=0.0;
std::vector<bool> key_state_translation(6);
const GLfloat TRANS_DELTA = 0.03;

// Rotation Parameters
GLfloat xrot=0.0,yrot=0.0,zrot=0.0;
std::vector<bool> key_state_rotation(6);
const GLfloat ROT_DELTA = 0.03;

//Recenter Parameters
bool key_state_recenter=false;

//Running variable to toggle culling on/off
bool enable_culling=true;
//Running variable to toggle wireframe/solid modelling
bool solid=true;

//-------------------------------------------------------------------------

#endif
