#include "heirarchical_model.hpp"

HeirarchicalModel::HeirarchicalModel() {}

HeirarchicalModel::HeirarchicalModel(std::string id_str, glm::vec3 scale_vec, glm::vec3 translation_vec) {
	hm_id = id_str;
	scaling_matrix = glm::scale(glm::mat4(1.0f), scale_vec);
	xpos = next_xpos = translation_vec.x;
	ypos = next_ypos = translation_vec.y;
	zpos = next_zpos = translation_vec.z;

}

std::string HeirarchicalModel::get_id() {
	return hm_id;
}

void HeirarchicalModel::draw_hm(OpenglParams* params, int light_flag, glm::mat4 projection_transform, glm::mat4 tpt,
                                double interpolation_factor) {
	xpos += interpolation_factor * (next_xpos - xpos);
	ypos += interpolation_factor * (next_ypos - ypos);
	zpos += interpolation_factor * (next_zpos - zpos);
	translation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, zpos));
	draw(params, light_flag, glm::mat4(1.0f), projection_transform, tpt, tpt * translation_matrix * scaling_matrix, interpolation_factor);
}

void HeirarchicalModel::save_keyframe_hm(FILE* fp) {
	// fprintf(fp, "%s~Tx ", hm_id.c_str());
	// fprintf(fp, "%s~Ty ", hm_id.c_str());
	// fprintf(fp, "%s~Tz ", hm_id.c_str());
	fprintf(fp, "%.2f ", xpos);
	fprintf(fp, "%.2f ", ypos);
	fprintf(fp, "%.2f ", zpos);
	save_keyframe(fp);
}
void HeirarchicalModel::load_next_keyframe_hm(FILE* fp) {
	fscanf(fp, "%f ", &next_xpos);
	fscanf(fp, "%f ", &next_ypos);
	fscanf(fp, "%f ", &next_zpos);
	load_next_keyframe(fp);
}

void HeirarchicalModel::translate(std::vector<bool> key_state_translation, bool key_state_recenter) {
	if (key_state_recenter) {
		xpos = ypos = zpos = 0.0f;
	}
	else {
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
}