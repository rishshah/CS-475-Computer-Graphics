#include "./scene.hpp"

const std::string FILE_NAME = "./models/";


Scene::~Scene() {
	for (int i = 0; i < model_list.size(); ++i) {
		delete model_list[i];
	}
};
/**
 * @brief initialize vao and links to shaders for this scene
 */
void Scene::init() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
	uIs_tp = glGetUniformLocation( shaderProgram, "uIs_tp" );

	vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
	glEnableVertexAttribArray( vPosition );

	vColor = glGetAttribLocation( shaderProgram, "vColor" );
	glEnableVertexAttribArray( vColor );

	vTexCoord = glGetAttribLocation( shaderProgram, "vTexCoord" );
	glEnableVertexAttribArray( vTexCoord );


	model_list.resize(0);
}

/**
 * @brief Load new model in scene
 * @param model_filename filename to load the model from relative to FILENAME path
 */
void Scene::load_new_model(std::string model_filename, std::string id) {
	HeirarchicalModel* hm = new HeirarchicalModel;
	hm->hm_id = id;
	hm->load(id, FILE_NAME + id + "/" + model_filename + ".raw", glm::mat4(1.0f));
	model_list.push_back(hm);
}

/**
 * @brief      draw all contents of the screen
 * @param[in]  projection_transform  the third person camera projection transformation matrix
 */
void Scene::draw(glm::mat4 projection_transform) {
	glBindVertexArray(vao);
	for (int i = 0; i < model_list.size(); ++i) {
		model_list[i]->draw(vPosition, vColor, vTexCoord, uModelViewMatrix, uIs_tp, 
							 glm::mat4(1.0f) ,projection_transform * 
							translation_matrix * rotation_matrix * scaling_matrix * 
							model_list[i]->translation_matrix * model_list[i]->rotation_matrix
		                    * model_list[i]->scaling_matrix);
	}
}

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
		rotation_matrix = glm::rotate(rotation_matrix, -ROT_DELTA, glm::vec3(glm::transpose(rotation_matrix) * X_UNIT));
	}
	else if (key_state_rotation[1]) {
		rotation_matrix = glm::rotate(rotation_matrix, ROT_DELTA, glm::vec3(glm::transpose(rotation_matrix) * X_UNIT));
	}

	if (key_state_rotation[2]) {
		rotation_matrix = glm::rotate(rotation_matrix, -ROT_DELTA, glm::vec3(glm::transpose(rotation_matrix) * Y_UNIT));
	}
	else if (key_state_rotation[3]) {
		rotation_matrix = glm::rotate(rotation_matrix, ROT_DELTA, glm::vec3(glm::transpose(rotation_matrix) * Y_UNIT));
	}

	if (key_state_rotation[4]) {
		rotation_matrix = glm::rotate(rotation_matrix, ROT_DELTA, glm::vec3(glm::transpose(rotation_matrix) * Z_UNIT));
	}
	else if (key_state_rotation[5]) {
		rotation_matrix = glm::rotate(rotation_matrix, -ROT_DELTA, glm::vec3(glm::transpose(rotation_matrix) * Z_UNIT));
	}
}


/**
 * @brief recalculate translation and scaling matrix of scene
 * @param key_state_trans_or_scale 	key press boolean vector input 	{WASDZX}
 * @param key_state_scaling_mode 	key press boolean vector input 	{C}  Scaling is not allowed
 * @param key_state_recenter 	key press boolean vector inputs 	{R}
 */
void Scene::trans_scale(std::vector<bool> key_state_trans_or_scale, bool key_state_recenter, bool key_state_scaling_mode) {
	if (key_state_recenter) {
		xpos = ypos = zpos = 0.0f;
	}
	else if (key_state_scaling_mode) {
		if (key_state_trans_or_scale[0]) {
			xscale = std::max(xscale - SCALE_DELTA, 0.0f);
		}
		else if (key_state_trans_or_scale[1]) {
			xscale = std::max(xscale + SCALE_DELTA, 0.0f);
		}

		if (key_state_trans_or_scale[2]) {
			yscale = std::max(yscale - SCALE_DELTA, 0.0f);
		}
		else if (key_state_trans_or_scale[3]) {
			yscale = std::max(yscale + SCALE_DELTA, 0.0f);
		}

		if (key_state_trans_or_scale[4]) {
			zscale = std::max(zscale + SCALE_DELTA, 0.0f);
		}
		else if (key_state_trans_or_scale[5]) {
			zscale = std::max(zscale - SCALE_DELTA, 0.0f);
		}
	}
	else {
		if (key_state_trans_or_scale[0]) {
			xpos -= TRANS_DELTA;
		}
		else if (key_state_trans_or_scale[1]) {
			xpos += TRANS_DELTA;
		}

		if (key_state_trans_or_scale[2]) {
			ypos += TRANS_DELTA;
		}
		else if (key_state_trans_or_scale[3]) {
			ypos -= TRANS_DELTA;
		}

		if (key_state_trans_or_scale[4]) {
			zpos += TRANS_DELTA;
		}
		else if (key_state_trans_or_scale[5]) {
			zpos -= TRANS_DELTA;
		}
	}
	if (key_state_recenter) {
		rotation_matrix = glm::mat4(1.0f);
	}
	else {
		translation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, zpos));
	}
}