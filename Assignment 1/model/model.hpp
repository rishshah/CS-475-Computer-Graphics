#ifndef _MODEL_HPP_
#define _MODEL_HPP_
#include <stdio.h>
#include "../../glm/vec4.hpp"
#include "../../glm/vec3.hpp"
#include "../../glm/mat4x4.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../framework/gl_framework.hpp"

extern std::vector<int> prevmodes;
extern std::vector<int> mode_indexes;
/**
 * @brief      Class for storing vertex attributes.
 */
class Vertex {
public:
	glm::vec3 position;
	glm::vec3 color;
};


/**
 * @brief      Class for storing model data.
 */
class Model {
public:

	float red_value = 1.0;
	float green_value = 1.0;
	float blue_value = 1.0;

	std::vector<Vertex> vertex_list;

	glm::vec3 centroid;
	glm::mat4 centroid_translation_matrix;

	void calc_centroid();
	/**
	 * @brief      {recalculate the vector containting all triangles data to be drawn directly}
	 */
	void segregate_vertices();
	void combine_configuration_and_vertices();
	/**
	* @brief      { load model from a file }
	*
	* @param      filename  The filename to load from
	*
	* @return     { true if successfully loaded }
	*/
	bool load(std::string filenamex);
	/**
	* @brief      { save model to a file }
	*
	* @param      filename  The filename to save the model into
	*
	* @return     { true if successfully saved }
	*/
	bool save(std::string filenamex);
	/**
	* @brief      { assign model buffer to given vbo and vaos and accordingly
	*             adjust how the values will be interpreted by vertex shader}
	*
	* @param      vao        The current context vertex array object
	* @param      vbo        The current context vertex buffer object
	* @param      vPosition  The varible pointing to location of vertex position in
	*                        shader
	* @param      vColor     The varible pointing to location of vertex color in
	*                        shader
	*/
	void assignBuffer(GLuint &vbo, GLuint &vao, GLuint &vPosition, GLuint &vColor);
};

#endif
