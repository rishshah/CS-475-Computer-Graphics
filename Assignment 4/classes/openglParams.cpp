#include "openglParams.hpp"

OpenglParams::OpenglParams(){
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
	uNormalMatrix = glGetUniformLocation( shaderProgram, "normalMatrix");
	uViewMatrix = glGetUniformLocation( shaderProgram, "viewMatrix");
	multMatrix = glGetUniformLocation( shaderProgram, "multMatrix");

	uIs_tp = glGetUniformLocation( shaderProgram, "uIs_tp" );
	uLight_flag = glGetUniformLocation( shaderProgram, "uLight_flag" );

	vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
	glEnableVertexAttribArray( vPosition );

	vColor = glGetAttribLocation( shaderProgram, "vColor" );
	glEnableVertexAttribArray( vColor );

	vNormal = glGetAttribLocation( shaderProgram, "vNormal" );
	glEnableVertexAttribArray( vNormal );

	vTexCoord = glGetAttribLocation( shaderProgram, "vTexCoord" );
	glEnableVertexAttribArray( vTexCoord );
}