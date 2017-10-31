#version 400

in vec4 color;
in vec2 tex;
in float spec_shine;
in float light_inten;
in vec4 position_pt;
in mat4 mult_matrix;
flat in int light_present;
flat in int is_texture_present;

uniform sampler2D texture;

out vec4 frag_color;

void main () 
{
  // float radius = 0.8;

  float spot_cutoff = 0.8;

  vec4 ori_position = mult_matrix * position_pt ;

  vec3 spot_light_pos = vec3(0.0, 2.0, 0.0);
  
  vec3 spot_light_dir = vec3(0.0, -1.0, 0.0);

  vec3 point_position = vec3(ori_position) - spot_light_pos;

  float val = dot(normalize(spot_light_dir), normalize(point_position));

  // float val = (ori_position.x*ori_position.x) + (ori_position.z*ori_position.z);

  if(is_texture_present == 1){
  	vec4 tex_color = texture2D(texture, tex);
  	vec3 temp_vec3 = vec3(min(tex_color.x,1.0), min(tex_color.y,1.0), min(tex_color.z,1.0));
  	vec4 new_color = vec4(min((temp_vec3*light_inten + vec3(spec_shine, spec_shine, spec_shine)), vec3(1.0)), 1.0);
  	
    if(light_present == 1 && val > spot_cutoff)
  		frag_color = vec4(new_color.x+0.2, new_color.y+0.2, new_color.z+0.2, color.w);
  	else
  		frag_color = new_color;

  } else {
  
  	if(light_present == 1 && val > spot_cutoff)
  		frag_color = vec4(color.x+0.2, color.y+0.2, color.z+0.2, color.w);
  	else
  		frag_color = color;
  }	
  	
}
