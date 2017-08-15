#include "model.hpp"

void Model::combine_configuration_and_vertices() {
	position_ptr.resize(num_of_triangles * 3);
	color_ptr.resize(num_of_triangles * 3);

	for (int i = 0; i < 3 * num_of_triangles; ++i) {
		position_ptr[i] = vertex_list[configuration_list[i]].position;
		color_ptr[i] = vertex_list[configuration_list[i]].color;
	}
}

bool Model::load(char* filename) {
	FILE *fp_input = fopen(filename, "r" );
	if (fp_input ==  NULL) {
		printf("Error opening file %s\n", filename);
		return false;
	}

	fscanf(fp_input, "%d", &num_of_vertices);
	vertex_list.resize(num_of_vertices);
	for (int i = 0; i < num_of_vertices; ++i) {
		float vx, vy, vz, cx, cy, cz;
		fscanf (fp_input, "%f %f %f %f %f %f", &vx, &vy, &vz, &cx, &cy, &cz);

		vertex_list[i].position = glm::vec3(vx, vy, vz);
		vertex_list[i].color = glm::vec3(cx, cy, cz);
	}

	fscanf(fp_input, "\n%d", &num_of_triangles);
	configuration_list.resize(3 * num_of_triangles);
	for (int i = 0; i < 3 * num_of_triangles; ++i) {
		fscanf (fp_input, "%d", &configuration_list[i]);
	}

	fclose(fp_input);

	combine_configuration_and_vertices();
	return true;
}

bool Model::save(char* filename) {
	FILE *fp_output = fopen(filename, "w");
	if (fp_output ==  NULL) {
		printf("Error creating file %s\n", filename);
		return false;
	}

	fprintf(fp_output, "%d\n", num_of_vertices);

	for (int i = 0; i < num_of_vertices; ++i) {
		fprintf (fp_output, "%.1f %.1f %.1f \t %.1f %.1f %.1f \n", (float)vertex_list[i].position[0], (float)vertex_list[i].position[1], (float)vertex_list[i].position[2],
		         (float)vertex_list[i].color[0], (float)vertex_list[i].color[1], (float)vertex_list[i].color[2]);
	}

	fprintf(fp_output, "%d\n", num_of_triangles);

	for (int i = 0; i < num_of_triangles * 3; i = i + 3) {
		fprintf (fp_output, "%d %d %d \n", (int)configuration_list[i], (int)configuration_list[i + 1], (int)configuration_list[i + 2]);
	}

	fclose(fp_output);
	return true;
}

int Model::get_num_of_triangles() {
	return num_of_triangles;
}

void Model::assignBuffer(GLuint &vao, GLuint &vbo, GLuint &vPosition, GLuint &vColor) {
	size_t size_points = 3 * num_of_triangles * sizeof (glm::vec3);

	glBufferData (GL_ARRAY_BUFFER, size_points * 2, NULL, GL_STATIC_DRAW);
	glBufferSubData( GL_ARRAY_BUFFER, 0, size_points, &position_ptr[0] );
	glBufferSubData( GL_ARRAY_BUFFER, size_points, size_points, &color_ptr[0] );

	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
	glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(size_points) );
}

void Model::calc_centroid() {
	centroid = glm::vec3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < num_of_vertices; ++i) {
		centroid += vertex_list[i].position;
	}
	centroid /= num_of_vertices;
}

glm::vec3 Model::get_centroid() {
	return centroid;
}