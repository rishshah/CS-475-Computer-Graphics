#version 400

in vec3 vPosition;
in vec3 vColor;
in vec3 vNormal;
in vec2 vTexCoord;

out vec4 color;
out vec2 tex;
flat out int is_texture_present;

uniform int uIs_tp;
uniform mat4 uModelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 viewMatrix;

void main (void) 
{

  //vec4 diffuse = vec4(0.4, 0.4, 0.4, 1.0); 
  //vec4 ambient = vec4(0.6, 0.6, 0.6, 1.0);
  //vec4 specular = vec4(1.0, 0.5, 0.5, 1.0);
  //vec4 spec = vec4(0.0); 
  float diffuse = 0.7;
  float ambient = 0.3;
  float specular = 0.2;
  float spec = 0.0;

  float shininess = 0.05;
  
  
  // Defining Light 
  vec4 lightPos = vec4(0.0, 0.0, 10.0, 0.0);
  vec3 lightDir = vec3(viewMatrix * lightPos); 
  lightDir = normalize(lightDir);  

  // gl_Position = uModelViewMatrix * vPosition
  
  vec3 n = normalize(normalMatrix * normalize(vNormal));
  float dotProduct = dot(n, lightDir);
  float intensity =  max( dotProduct, 0.0);

  // Compute specular component only if light falls on vertex
  
  gl_Position = uModelViewMatrix * vec4(vPosition, 1.0f);

  if(intensity > 0.0)
  {
	vec3 eye = normalize(vec3(-gl_Position));
	vec3 h = normalize(lightDir + eye );
   	float intSpec = max(dot(h,n), 0.0);	
    spec = specular * pow(intSpec, shininess);
  }  	
  
  float inten_color = max((intensity * diffuse), ambient);

  vec4 new_color = vec4(min((vColor*inten_color + vec3(spec, spec, spec)), 1.0), 1.0);

  // color = vec4(vColor, 1.0);
  
  color = new_color;

  tex = vTexCoord;
  is_texture_present = uIs_tp;

}
