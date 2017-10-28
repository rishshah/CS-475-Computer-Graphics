#version 400

in vec3 vPosition;
in vec3 vColor;
in vec2 vTexCoord;

out vec4 color;
out vec2 tex;
flat out int is_texture_present;

uniform int uIs_tp;
uniform mat4 uModelViewMatrix;

void main (void) 
{
  gl_Position = uModelViewMatrix * vec4(vPosition, 1.0f);
  color = vec4(vColor, 1.0f);
  tex = vTexCoord;
  is_texture_present = uIs_tp;
}
