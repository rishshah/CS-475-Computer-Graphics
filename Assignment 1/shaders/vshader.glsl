#version 400

in vec3 vPosition;
in vec3 vColor;

out vec4 color;

uniform mat4 uModelViewMatrix;

void main (void) 
{
  gl_Position = uModelViewMatrix * vec4(vPosition, 1.0f);
  color = vec4(vColor, 1.0f);
}
