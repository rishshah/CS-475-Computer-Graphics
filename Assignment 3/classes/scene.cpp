#include "./scene.hpp"

/**  
 * @brief destructor to deallocate all models
 */
Scene::~Scene() {
	for (int i = 0; i < model_list.size(); ++i) {
		delete model_list[i];
	}
};

/**
 * @brief toggle Spotlight
 */
void Scene::toggle_light(){
	light_flag = 1 - light_flag;
}

/**
 * @brief Get location of uniform and input variables in shader and store them
 */
void Scene::init() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
	uNormalMatrix = glGetUniformLocation( shaderProgram, "normalMatrix");
	uViewMatrix = glGetUniformLocation( shaderProgram, "viewMatrix");

	uIs_tp = glGetUniformLocation( shaderProgram, "uIs_tp" );
	uLight_flag = glGetUniformLocation( shaderProgram, "uLight_flag" );

	vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
	glEnableVertexAttribArray( vPosition );

	vColor = glGetAttribLocation( shaderProgram, "vColor" );
	glEnableVertexAttribArray( vColor );

	vNormal = glGetAttribLocation( shaderProgram, "vNormal" );
	glEnableVertexAttribArray( vNormal );

	vTexCoord = glGetAttribLocation( shaderProgram, "vTexCoord" );
	glEnableVertexAttribArray( vTexCoord );

	projection_transform = glm::perspective(glm::radians(field_of_view), aspect_ratio, near_plane, far_plane) *
	                       glm::lookAt(eye_position, lookat_center, up);

	model_list.resize(0);
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
	HeirarchicalModel* hm = new HeirarchicalModel;
	hm->scaling_matrix = glm::scale(glm::mat4(1.0f), scale_vec);
	hm->translation_matrix = glm::translate(glm::mat4(1.0f), translation_vec);
	hm->hm_id = id;
	hm->load(id, FILE_NAME + id + "/" + model_filename + ".raw", glm::mat4(1.0f));
	model_list.push_back(hm);
}

/**
 * @brief      draw all contents of scene of the screen
 */
void Scene::draw() {
	glBindVertexArray(vao);
	for (int i = 0; i < model_list.size(); ++i) {
		model_list[i]->draw(vPosition, vColor, vNormal, vTexCoord, uModelViewMatrix, uNormalMatrix, uViewMatrix, uIs_tp,  uLight_flag, light_flag,
		                    glm::mat4(1.0f) , projection_transform,
		                    translation_matrix * rotation_matrix * scaling_matrix *
		                    model_list[i]->translation_matrix * model_list[i]->rotation_matrix
		                    * model_list[i]->scaling_matrix);
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
		rotation_vec.x -= ROT_DELTA;
	}
	else if (key_state_rotation[1]) {
		rotation_vec.x += ROT_DELTA;
	}

	if (key_state_rotation[2]) {
		rotation_vec.y -= ROT_DELTA;
	}
	else if (key_state_rotation[3]) {
		rotation_vec.y += ROT_DELTA;
	}

	if (key_state_rotation[4]) {
		rotation_vec.z += ROT_DELTA;
	}
	else if (key_state_rotation[5]) {
		rotation_vec.z -= ROT_DELTA;
	}

	glm::mat4 rotation_mtx_x = glm::rotate( glm::mat4(1.0f), glm::radians(rotation_vec.x), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotation_mtx_y = glm::rotate( glm::mat4(1.0f), glm::radians(rotation_vec.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotation_mtx_z = glm::rotate( glm::mat4(1.0f), glm::radians(rotation_vec.z), glm::vec3(0.0f, 0.0f, 1.0f));
	
	rotation_matrix = glm::translate(glm::mat4(1.0f), eye_position) * glm::inverse(translation_matrix) * rotation_mtx_z * rotation_mtx_y * rotation_mtx_x
	                  * translation_matrix * glm::translate(glm::mat4(1.0f), -eye_position);
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
		if (key_state_translation[0]) {
			xpos -= TRANS_DELTA;
		}
		else if (key_state_translation[1]) {
			xpos += TRANS_DELTA;
		}

		if (key_state_translation[2]) {
			ypos += TRANS_DELTA;
		}
		else if (key_state_translation[3]) {
			ypos -= TRANS_DELTA;
		}

		if (key_state_translation[4]) {
			zpos += TRANS_DELTA;
		}
		else if (key_state_translation[5]) {
			zpos -= TRANS_DELTA;
		}
	}
	translation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, zpos));
}