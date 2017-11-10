#include "heirarchical_model.hpp"

HeirarchicalModel::HeirarchicalModel() {}

HeirarchicalModel::HeirarchicalModel(std::string id_str, glm::vec3 scale_vec, glm::vec3 translation_vec) {
	hm_id = id_str;
	scaling_matrix = glm::scale(glm::mat4(1.0f), scale_vec);
	xpos = translation_vec.x;
	ypos = translation_vec.y;
	zpos = translation_vec.z;
	translation_matrix = glm::translate(glm::mat4(1.0f), translation_vec);
}

void HeirarchicalModel::draw_hm(OpenglParams* params, int light_flag, glm::mat4 projection_transform, glm::mat4 tpt) {
	draw(params, light_flag, glm::mat4(1.0f), projection_transform, tpt, tpt * translation_matrix * rotation_matrix * scaling_matrix);
}

void HeirarchicalModel::translate(std::vector<bool> key_state_translation, bool key_state_recenter) {
	if (key_state_recenter) {
		xpos = ypos = zpos = 0.0f;
		rotation_matrix = glm::mat4(1.0f);
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
	translation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, zpos));
}