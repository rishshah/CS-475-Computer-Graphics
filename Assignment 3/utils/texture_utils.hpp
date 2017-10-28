#ifndef _TEXTURE_UTILS_HPP_
#define _TEXTURE_UTILS_HPP_

#include "../framework/gl_framework.hpp"
#include <fstream>
#include <cstdlib>

GLuint LoadTexture( const char * filename, int width, int height );
void FreeTexture( GLuint texture );
#endif 
