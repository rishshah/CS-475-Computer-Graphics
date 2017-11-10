#include "./scene.hpp"

/**
 * @brief Initialize scene, camera and opengl shader variable locations
 */
Scene::Scene() {
	params = new OpenglParams();
	cam = new Camera();
	model_list.resize(0);
}
/**
 * @brief destructor to deallocate all models
 */
Scene::~Scene() {
	for (int i = 0; i < model_list.size(); ++i) {
		delete model_list[i];
	}
	delete cam;
};


/**
 * @brief toggle Spotlight
 * @dreturn spotlight status on/off
 */
bool Scene::toggle_light() {
	light_flag = 1 - light_flag;
	return light_flag == 1;
}

/**
 * @brief Load new model in scene
 * @details [long description]
 *
 * @param model_filename filename to load the model from relative to FILENAME path
 * @param id the folder which is the root of heirarchitiacal model to load
 * @param scale_vec scaling vector for heirarchical model
 * @param translation_vec positioning model initially in the scene
 */
void Scene::load_new_model(std::string model_filename, std::string id, glm::vec3 scale_vec, glm::vec3 translation_vec) {
	HeirarchicalModel* hm = new HeirarchicalModel(id, scale_vec, translation_vec);
	hm->load(id, FILE_NAME + id + "/" + model_filename + ".raw", glm::mat4(1.0f));
	model_list.push_back(hm);
}

/**
 * @brief      draw all contents of scene of the screen
 */
void Scene::draw() {
	glBindVertexArray(params->vao);
	glm::mat4 cam_movement_transform = translation_matrix * glm::translate(glm::mat4(1.0f), cam->eye_position) * glm::inverse(translation_matrix) *
	                                   rotation_matrix * translation_matrix * glm::translate(glm::mat4(1.0f), -cam->eye_position);

	for (int i = 0; i < model_list.size(); ++i) {
		model_list[i]->draw_hm(params, light_flag, cam->projection_transform, cam_movement_transform);
	}
}

/**
 * @brief get pointer to heirarchical model by searching them in scene by id
 *
 * @param id id of model to search in the scene
 * @return pointer to resulting model
 */
HeirarchicalModel* Scene::find_heirarchical_model_by_id(std::string id) {
	for (int i = 0; i < model_list.size(); ++i) {
		if (model_list[i]->hm_id == id)
			return model_list[i];
	}
	return NULL;
}

/**
 * @brief recalculate rotation matrix of scene
 * @param key_state_rotation 	key press boolean vector input
 */
void Scene::rotate(std::vector<bool> key_state_rotation) {
	if (key_state_rotation[0]) {
		rotation_matrix = glm::rotate(rotation_matrix, -ROT_DELTA, glm::vec3(glm::transpose(rotation_matrix) * Z_UNIT));
	}
	else if (key_state_rotation[1]) {
		rotation_matrix = glm::rotate(rotation_matrix, ROT_DELTA, glm::vec3(glm::transpose(rotation_matrix) * Z_UNIT));
	}

	if (key_state_rotation[2]) {
		rotation_matrix = glm::rotate(rotation_matrix, -ROT_DELTA, glm::vec3(glm::transpose(rotation_matrix) * Y_UNIT));
	}
	else if (key_state_rotation[3]) {
		rotation_matrix = glm::rotate(rotation_matrix, ROT_DELTA, glm::vec3(glm::transpose(rotation_matrix) * Y_UNIT));
	}

	if (key_state_rotation[4]) {
		rotation_matrix = glm::rotate(rotation_matrix, ROT_DELTA, glm::vec3(glm::transpose(rotation_matrix) * X_UNIT));
	}
	else if (key_state_rotation[5]) {
		rotation_matrix = glm::rotate(rotation_matrix, -ROT_DELTA, glm::vec3(glm::transpose(rotation_matrix) * X_UNIT));
	}
}

/**
 * @brief recalculate translation matrix of scene corresponding to third person camera
 * @param key_state_translation 	key press boolean vector input 	{WASDZX}
 * @param key_state_recenter 	key press boolean vector inputs 	{R}
 */
void Scene::translate(std::vector<bool> key_state_translation, bool key_state_recenter) {
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

void Scene::save_keyframe(){}
void Scene::save_animation(){}
