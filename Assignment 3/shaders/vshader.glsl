#version 400

in vec3 vPosition;
in vec3 vColor;
in vec3 vNormal;
in vec2 vTexCoord;

out vec4 color;
out vec2 tex;
out float spec_shine;
out float light_inten;
out vec4 position_pt;
out mat4 mult_matrix;
flat out int light_present;
flat out int is_texture_present;

uniform int uIs_tp;
uniform int uLight_flag;

uniform mat4 uModelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 viewMatrix;
uniform mat4 multMatrix;

void main (void) 
{

  //vec4 diffuse = vec4(0.4, 0.4, 0.4, 1.0); 
  //vec4 ambient = vec4(0.6, 0.6, 0.6, 1.0);
  //vec4 specular = vec4(1.0, 0.5, 0.5, 1.0);
  //vec4 spec = vec4(0.0); 
  float diffuse = 0.8;
  float ambient = 0.3;
  float specular = 0.2;
  float spec1 = 0.0;
  float spec2 = 0.0;
  float shininess = 0.05;
  mult_matrix = multMatrix;
  light_present = uLight_flag;
  // Defining Light 
  vec4 lightPos = vec4(1.0, 1.0, 0.0, 0.0);
  vec4 lightPos2 = vec4(-1.0, 1.0, 0.0, 0.0);

  vec3 lightDir = vec3(viewMatrix * lightPos); 
  vec3 lightDir2 = vec3(viewMatrix * lightPos2); 

  mat4 view_matrix = inverse(viewMatrix);

  mat4 another_matrix = inverse(multMatrix);

  mult_matrix = another_matrix * view_matrix ;

  lightDir = normalize(lightDir);
  lightDir2 = normalize(lightDir2);  
  
  vec3 n = normalize(normalMatrix * normalize(vNormal));
  
  float dotProduct = dot(n, lightDir);
  float dotProduct2 = dot(n, lightDir2);
  
  float intensity =  max(abs(dotProduct), 0.0);

  float intensity2 = max(abs(dotProduct2), 0.0);

  
  gl_Position = uModelViewMatrix * vec4(vPosition, 1.0f);
 
  position_pt = gl_Position;

  vec3 eye = normalize(vec3(-gl_Position));

  // Compute specular component only if light falls on vertex
  if(intensity > 0.0)
  {
	  vec3 h = normalize(lightDir + eye );
   	float intSpec = dot(h,n);	
    spec1 = specular * pow(intSpec, shininess); //*10.0*(intensity-0.3);
  }  	

  if(intensity2 > 0.0)
  {
    vec3 h = normalize(lightDir2 + eye );
    float intSpec = dot(h,n);  
    spec2 = specular * pow(intSpec, shininess); //*10.0*(intensity-0.3);
  }

  float spec = max(spec1, spec2);

  spec_shine = spec;

  float inten_color = max( (max(intensity, intensity2) * diffuse) ,  ambient);

  light_inten = inten_color;

  vec4 new_color = vec4(min((vColor*inten_color + vec3(spec, spec, spec)), vec3(1.0)), 1.0);

  // color = vec4(vColor, 1.0);
  
  color = new_color;

  tex = vTexCoord;
  is_texture_present = uIs_tp;

}
