#ifndef _PARAMS_HPP_
#define _PARAMS_HPP_

#include "../global.hpp"

class OpenglParams{
public:
	OpenglParams();
	GLuint vao = 0;
	GLuint vPosition, vColor, vNormal, vTexCoord;
	GLuint uModelViewMatrix, uIs_tp, uNormalMatrix, uViewMatrix, multMatrix, uLight_flag;
};

#endif