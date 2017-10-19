#include "model.hpp"

void printmat4(glm::mat4 Awv) {
	printf("\n");
	printf("%f, %f, %f, %f \n", Awv[0][0], Awv[1][0], Awv[2][0], Awv[3][0]);
	printf("%f, %f, %f, %f \n", Awv[0][1], Awv[1][1], Awv[2][1], Awv[3][1]);
	printf("%f, %f, %f, %f \n", Awv[0][2], Awv[1][2], Awv[2][2], Awv[3][2]);
	printf("%f, %f, %f, %f \n", Awv[0][3], Awv[1][3], Awv[2][3], Awv[3][3]);
	printf("\n");
}


//--------------------------------------------------------------


/**
 * @brief      Load model from a .raw file  and store its vertex data
 *
 * @param      filename the .raw file that contains the model
 *
 * @return     true iff file loaded successfully
 */
bool Model::load(std::string filename) {
	FILE *fp_input = fopen(filename.c_str(), "r" );
	if (fp_input ==  NULL) {
		printf("Error opening file %s\n", filename.c_str());
		return false;
	}

	int num_vertices, num_children;
	fscanf (fp_input, "%s", id);
	fscanf (fp_input, "%d", &num_children);
	fscanf (fp_input, "%d", &num_vertices);

	float x, y, z;

	//scale
	fscanf(fp_input, "%f %f %f", &x, &y, &z);
	scale_vec = glm::vec3(x, y, z);

	//par_translation
	fscanf(fp_input, "%f %f %f", &x, &y, &z);
	par_translation_vec = glm::vec3(x, y, z);

	//self_translation
	fscanf(fp_input, "%f %f %f", &x, &y, &z);
	self_translation_vec = glm::vec3(x, y, z);

	child_model_list.resize(num_children);
	for (int i = 0; i < num_children; ++i) {
		char child_filename[100]; 
		fscanf(fp_input, "%s\n", child_filename);
		Model m;
		m.load("./models/" + std::string(child_filename) + ".raw");
		m.assignBuffer();
		child_model_list[i] = m;
	}

	vertex_list.resize(num_vertices);
	for (int i = 0; i < num_vertices; ++i) {
		float vx, vy, vz, cx, cy, cz;
		fscanf(fp_input, "%f %f %f %f %f %f", &vx, &vy, &vz, &cx, &cy, &cz);
		Vertex v;
		v.position = glm::vec3(vx, vy, vz);
		v.color = glm::vec3(cx, cy, cz);
		vertex_list[i] = v;
	}
	assignBuffer();
	fclose(fp_input);
	return true;
}

/**
 * @brief      Load model from a .raw file  and store its vertex data
 *
 * @param      filename the .raw file that contains the model
 *
 * @return     true iff file loaded successfully
 */
bool Model::save() {
	FILE *fp_output = fopen(("./models/" + std::string(id) + ".raw").c_str(), "w" );
	if (fp_output ==  NULL) {
		printf("Error opening file %s\n", ("./models/" + std::string(id) + ".raw").c_str());
		return false;
	}
	fprintf (fp_output, "%s\n", id);
	fprintf (fp_output, "%zu\n", child_model_list.size());
	fprintf (fp_output, "%zu\n", vertex_list.size());
	fprintf (fp_output, "%.1f %.1f %.1f\n", scale_vec.x, scale_vec.y, scale_vec.z);
	fprintf (fp_output, "%.1f %.1f %.1f\n", par_translation_vec.x, par_translation_vec.y, par_translation_vec.z);
	fprintf (fp_output, "%.1f %.1f %.1f\n", self_translation_vec.x, self_translation_vec.y, self_translation_vec.z);

	for (int i = 0; i < child_model_list.size(); ++i) {
		fprintf (fp_output, "%s\n", child_model_list[i].id);
		child_model_list[i].save();
	}
	for (int i = 0; i < vertex_list.size(); ++i) {
		fprintf (fp_output, "%.1f %.1f %.1f \t %.1f %.1f %.1f \n", (float)vertex_list[i].position[0], (float)vertex_list[i].position[1], (float)vertex_list[i].position[2],
		         (float)vertex_list[i].color[0], (float)vertex_list[i].color[1], (float)vertex_list[i].color[2]);
	}
	fclose(fp_output);
	return true;
}


/**
 * @brief      fill the vbo for the model
 */
void Model::assignBuffer() {
	size_t size_points = vertex_list.size() * sizeof (glm::vec3);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData (GL_ARRAY_BUFFER, size_points * 2, &vertex_list[0], GL_STATIC_DRAW);
}

/**
 * @brief      draw model on screen
 *
 * @param[in]  vPosition         location of position input in vertex shader
 * @param[in]  vColor            location of color input in vertex shader
 * @param[in]  uModelViewMatrix  location of transformation matrix input in vertex shader
 * @param[in]  mode              The mode of drawing the model (GL_TRIANGLES, GL_LINES, GL_POINT)
 */
void Model::draw(GLuint vPosition, GLuint vColor, GLuint uModelViewMatrix, GLenum mode, glm::mat4 third_person_transform,  glm::mat4 projection_transform) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0) );
	glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(glm::vec3)) );

	glm::mat4 par_translation_transform = glm::translate(glm::mat4(1.0f), par_translation_vec);
	glm::mat4 self_translation_transform = glm::translate(glm::mat4(1.0f), self_translation_vec); 
	glm::mat4 modelling_transform = glm::scale(glm::mat4(1.0f), scale_vec);
	glm::mat4 temp_matrix = projection_transform * par_translation_transform * third_person_transform * glm::inverse(self_translation_transform) * modelling_transform;
	glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(temp_matrix));

	glDrawArrays(mode, 0, vertex_list.size());

	for (int i = 0; i < child_model_list.size(); ++i) {
		child_model_list[i].draw(vPosition, vColor, uModelViewMatrix, mode, third_person_transform, projection_transform);
	}
}

/**
 * @brief calculate transform to join parent to child
 *
 * @param m Child model
 * @param point_child Point on child to join to parent (in opengl coordinates)
 * @param point_parent Point on parent to join to child (in opengl coordinates)
 */
void Model::join_child(Model m, glm::vec3 point_child, glm::vec3 point_parent) {
	m.self_translation_vec = point_child;
	m.par_translation_vec = point_parent;
	child_model_list.push_back(m);
};
