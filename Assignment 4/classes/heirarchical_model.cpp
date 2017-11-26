#include "heirarchical_model.hpp"

// void printmat4(glm::mat4 Awv) {
// 	printf("\n");
// 	printf("%f, %f, %f, %f \n", Awv[0][0], Awv[1][0], Awv[2][0], Awv[3][0]);
// 	printf("%f, %f, %f, %f \n", Awv[0][1], Awv[1][1], Awv[2][1], Awv[3][1]);
// 	printf("%f, %f, %f, %f \n", Awv[0][2], Awv[1][2], Awv[2][2], Awv[3][2]);
// 	printf("%f, %f, %f, %f \n", Awv[0][3], Awv[1][3], Awv[2][3], Awv[3][3]);
// 	printf("\n");
// }

HeirarchicalModel::HeirarchicalModel() {
}

/**
 * @brief Initialize heirarchical model
 * 
 * @param id_str id of model
 * @param scale_vec initial scaling vector
 * @param translation_vec initial positioning
 */
HeirarchicalModel::HeirarchicalModel(std::string id_str, glm::vec3 scale_vector, glm::vec3 translation_vec) {
	hm_id = id_str;
	scale_vec = next_scale_vec = scale_vector;
	xpos = next_xpos = translation_vec.x;
	ypos = next_ypos = translation_vec.y;
	zpos = next_zpos = translation_vec.z;
}

std::string HeirarchicalModel::get_id() {
	return hm_id;
}

/**
 * @brief Draw this heirarchical model on the screen
 * 
 * @param params OpenGL parameter to give input to shaders
 * @param light_flag light on/off status
 * @param projection_transform  perspective projection
 * @param tpt third person transform (Camera movement)
 * @param interpolation_factor between current and next frame 
 */
void HeirarchicalModel::draw_hm(OpenglParams* params, int light_flag, glm::mat4 projection_transform, glm::mat4 tpt, float interpolation_factor) {
	glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(xpos + interpolation_factor * (next_xpos - xpos), ypos + interpolation_factor * (next_ypos - ypos), zpos + interpolation_factor * (next_zpos - zpos)));
	glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), scale_vec + interpolation_factor * (next_scale_vec - scale_vec));
	draw(params, light_flag, glm::mat4(1.0f), projection_transform, tpt, tpt * translation_matrix * scaling_matrix, interpolation_factor);
}

/**
 * @brief save translation frame for this model and rotation frame for its tree
 * 
 * @param fp keyframe file pointer
 */
void HeirarchicalModel::save_keyframe_hm(FILE* fp) {
	// fprintf(fp, "%s~Tx ", hm_id.c_str());
	// fprintf(fp, "%s~Ty ", hm_id.c_str());
	// fprintf(fp, "%s~Tz ", hm_id.c_str());
	
	// fprintf(fp, "%s~Sx ", hm_id.c_str());
	// fprintf(fp, "%s~Sy ", hm_id.c_str());
	// fprintf(fp, "%s~Sz ", hm_id.c_str());
	
	fprintf(fp, "%.2f ", xpos);
	fprintf(fp, "%.2f ", ypos);
	fprintf(fp, "%.2f ", zpos);
	
	fprintf(fp, "%.2f ", scale_vec.x);
	fprintf(fp, "%.2f ", scale_vec.y);
	fprintf(fp, "%.2f ", scale_vec.z);
	
	save_keyframe(fp);
}

/**
 * @brief load next frame
 * 
 * @param fp keyframe file pointer
 */
void HeirarchicalModel::load_next_keyframe_hm(FILE* fp) {
	xpos = next_xpos;
	ypos = next_ypos;
	zpos = next_zpos;

	scale_vec = next_scale_vec;

	fscanf(fp, "%f ", &next_xpos);
	fscanf(fp, "%f ", &next_ypos);
	fscanf(fp, "%f ", &next_zpos);

	fscanf(fp, "%f ", &next_scale_vec.x);
	fscanf(fp, "%f ", &next_scale_vec.y);
	fscanf(fp, "%f ", &next_scale_vec.z);

	load_next_keyframe(fp);
}

/**
 * @brief translate the heirarchical model
 * 
 * @param key_state_translation boolean vector giving status of keys pressed
 */
void HeirarchicalModel::translate(std::vector<bool> key_state_translation) {
	if (key_state_translation[4]) {
		xpos -= TRANS_DELTA;
	}
	else if (key_state_translation[5]) {
		xpos += TRANS_DELTA;
	}

	if (key_state_translation[2]) {
		ypos += TRANS_DELTA;
	}
	else if (key_state_translation[3]) {
		ypos -= TRANS_DELTA;
	}

	if (key_state_translation[0]) {
		zpos += TRANS_DELTA;
	}
	else if (key_state_translation[1]) {
		zpos -= TRANS_DELTA;
	}
}