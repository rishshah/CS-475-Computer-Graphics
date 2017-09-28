#version 400

in vec3 vPosition;
in vec3 vColor;

out vec4 color;

uniform mat4 uScene;
uniform mat4 uModelViewMatrix;
uniform int uNDCS;

void main (void) 
{
  vec4 pos = uModelViewMatrix * vec4(vPosition, 1.0f);
  if(uNDCS == 1){
  	pos =  uScene * pos ;
  	pos = vec4(pos.x/pos.w , pos.y/pos.w, pos.z/pos.w, 1.0f);
  	gl_Position = inverse(uScene) * pos ;  
  }
  else{
  	gl_Position = pos;
  }
  color = vec4(vColor, 1.0f);
}
