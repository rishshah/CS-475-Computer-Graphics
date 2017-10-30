#version 400

in vec4 color;
in vec2 tex;
in float spec_shine;
in float light_inten;
flat in int is_texture_present;

uniform sampler2D texture;

out vec4 frag_color;

void main () 
{
  if(is_texture_present == 1){
  	vec4 tex_color = texture2D(texture, tex);
  	vec3 temp_vec3 = vec3(min(tex_color.x,1.0), min(tex_color.y,1.0), min(tex_color.z,1.0));
  	vec4 new_color = vec4(min((temp_vec3*light_inten + vec3(spec_shine, spec_shine, spec_shine)), vec3(1.0)), 1.0);
  	frag_color = new_color;

  } else {
  	frag_color = color;
  }
}
