#version 400

in vec4 color;
in vec2 tex;
flat in int is_texture_present;

uniform sampler2D texture;

out vec4 frag_color;

void main () 
{
  if(is_texture_present == 1){
  	frag_color = texture2D(texture, tex);
  } else {
  	frag_color = color;
  }
}
