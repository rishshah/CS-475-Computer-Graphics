#include "model.hpp"


/**
 * @brief      Loads the model stored in model.raw by default in  X Y Z R G B format
 */
bool Model::load() {
	std::string filename;
	printf("Enter the filename\n");
	std::cin >> filename;
	FILE *fp_input = fopen(("./binary_models/" + filename).c_str(), "r" );
	if (fp_input ==  NULL) {
		printf("Error opening file %s\n", filename.c_str());
		return false;
	}

	
	vertex_list.resize(0);

	float vx, vy, vz, cx, cy, cz;
	while(fscanf (fp_input, "%f %f %f %f %f %f", &vx, &vy, &vz, &cx, &cy, &cz) != EOF){
		Vertex v;
		v.position = glm::vec3(vx, vy, vz);
		v.color = glm::vec3(cx, cy, cz);
		vertex_list.push_back(v);
	}

	fclose(fp_input);
	calc_centroid();
	return true;
}


/**
 * @brief 		Saves the model in filename saved_model.raw by default in  X Y Z R G B format    
 */
bool Model::save() {
	std::string filename;
	printf("Enter the filename\n");
	std::cin >> filename;
	FILE *fp_output = fopen(("./binary_models/" + filename).c_str(), "w");
	if (fp_output ==  NULL) {
		printf("Error creating file %s\n", filename.c_str());
		return false;
	}

	for (int i = 0; i < vertex_list.size(); ++i) {
		fprintf (fp_output, "%.1f %.1f %.1f \t %.1f %.1f %.1f \n", (float)vertex_list[i].position[0], (float)vertex_list[i].position[1], (float)vertex_list[i].position[2],
		         (float)vertex_list[i].color[0], (float)vertex_list[i].color[1], (float)vertex_list[i].color[2]);
	}

	fclose(fp_output);
	return true;
}


/**
 * @brief      Assigns vertex list to the vertex buffer object and corresponding shader file attributes.
 *
 * @param      vao        The vao
 * @param      vbo        The vbo
 * @param      vPosition  The vertex_list positions
 * @param      vColor     The vertex_list colors
 */

void Model::assignBuffer(GLuint &vao, GLuint &vbo, GLuint &vPosition, GLuint &vColor) {
	size_t size_points = vertex_list.size() * sizeof (glm::vec3);

	glBufferData (GL_ARRAY_BUFFER, size_points * 2, &vertex_list[0], GL_STATIC_DRAW);
	
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0) );
	glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(glm::vec3)) );
}


/**
 * @brief      Calculates the centroid.
 */
void Model::calc_centroid() {
	centroid = glm::vec3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < vertex_list.size(); ++i) {
		centroid += vertex_list[i].position;
	}
	if(vertex_list.size()!=0)
		centroid /= vertex_list.size();
	centroid_translation_matrix = glm::translate(glm::mat4(1.0f), -centroid);
}
