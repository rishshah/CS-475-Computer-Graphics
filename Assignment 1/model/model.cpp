#include "model.hpp"

bool Model::load(char* filename) {
	FILE *fp_input = fopen(filename, "r" );
	if (fp_input ==  NULL) {
		printf("Error opening file %s\n", filename);
		return false;
	}

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

bool Model::save(char* filename) {
	FILE *fp_output = fopen(filename, "w");
	if (fp_output ==  NULL) {
		printf("Error creating file %s\n", filename);
		return false;
	}

	for (int i = 0; i < vertex_list.size(); ++i) {
		fprintf (fp_output, "%.1f %.1f %.1f \t %.1f %.1f %.1f \n", (float)vertex_list[i].position[0], (float)vertex_list[i].position[1], (float)vertex_list[i].position[2],
		         (float)vertex_list[i].color[0], (float)vertex_list[i].color[1], (float)vertex_list[i].color[2]);
	}

	fclose(fp_output);
	return true;
}

void Model::assignBuffer(GLuint &vao, GLuint &vbo, GLuint &vPosition, GLuint &vColor) {
	size_t size_points = vertex_list.size() * sizeof (glm::vec3);

	glBufferData (GL_ARRAY_BUFFER, size_points * 2, &vertex_list[0], GL_STATIC_DRAW);
	
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0) );
	glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(glm::vec3)) );
}


void Model::calc_centroid() {
	centroid = glm::vec3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < vertex_list.size(); ++i) {
		centroid += vertex_list[i].position;
	}
	if(vertex_list.size()!=0)
		centroid /= vertex_list.size();
	centroid_translation_matrix = glm::translate(glm::mat4(1.0f), -centroid);
}
