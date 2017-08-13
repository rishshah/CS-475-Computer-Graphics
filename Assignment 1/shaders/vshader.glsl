#version 400

in vec4 vPosition;
in vec4 vColor;
out vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 uModelViewMatrix;

void main (void) 
{
  gl_Position = uModelViewMatrix * vPosition;
  color = vColor;
}
