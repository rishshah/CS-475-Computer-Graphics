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
	delete params;
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
	hm->load(id, MODEL_FILE_NAME + id + "/" + model_filename + ".raw", glm::mat4(1.0f));
	model_list.push_back(hm);
}

/**
 * @brief      draw all contents of scene of the screen
 */
void Scene::draw(double interpolation_factor) {
	glBindVertexArray(params->vao);
	glm::mat4 cam_movement_transform = translation_matrix * glm::translate(glm::mat4(1.0f), cam->get_eye_position()) * glm::inverse(translation_matrix) *
	                                   rotation_matrix * translation_matrix * glm::translate(glm::mat4(1.0f), -cam->get_eye_position());

	for (int i = 0; i < model_list.size(); ++i) {
		model_list[i]->draw_hm(params, light_flag, cam->get_projection_transform(), cam_movement_transform, interpolation_factor);
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
		if (model_list[i]->get_id() == id)
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

void Scene::save_keyframe(int frame_num) {
	FILE *fp = fopen(KEY_FRAME_FILE_NAME.c_str(), "a" );
	if (fp ==  NULL) {
		printf("Error opening file %s\n", KEY_FRAME_FILE_NAME.c_str());
		return;
	}
	// fprintf(fp,"keyframe_no ");

	fprintf(fp, "%d ", frame_num);
	for (int i = 1; i < model_list.size(); ++i) {
		model_list[i]->save_keyframe_hm(fp);
	}
	fprintf(fp, "\n");

	fclose(fp);
	return;
}

void Scene::save_animation_frame(int frame_num, int windowWidth, int windowHeight) {
	FILE *fp_out = fopen((IMAGES_FILE_NAME + "out" + std::to_string(frame_num) + ".tga").c_str(), "wb");
	if (fp_out == NULL) {
		printf("Error opening file %s\n", (IMAGES_FILE_NAME + "out.bmp").c_str());
	}

	unsigned char *pixel_data = new unsigned char[windowWidth * windowHeight * 3];
	printf("%d %d\n", short(windowWidth), short(windowHeight));
	short TGAhead[] = { 0, 2, 0, 0, 0, 0, windowWidth, windowHeight, 24 };

	glReadBuffer(GL_BACK);
	glReadPixels(0, 0, windowWidth, windowWidth, GL_BGR, GL_UNSIGNED_BYTE, pixel_data);

	fwrite(TGAhead, sizeof(TGAhead), 1, fp_out);
	fwrite(pixel_data, 3 * windowWidth * windowHeight, 1, fp_out);

	fclose(fp_out);
	delete[] pixel_data;
}

void Scene::play(GLFWwindow* window) {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	
	FILE *fp = fopen(KEY_FRAME_FILE_NAME.c_str(), "r" );
	if (fp ==  NULL) {
		printf("Error opening file %s\n", KEY_FRAME_FILE_NAME.c_str());
		return;
	}
	while (fgetc(fp) != '\n');
	int frane_num = 0;
	// double super_init_timer = glfwGetTime();
	while (fscanf(fp, "%d ", &next_frame_num) != EOF) {
		for (int i = 1; i < model_list.size(); ++i) {
			model_list[i]->load_next_keyframe_hm(fp);
		}

		double current_frame_time = current_frame_num / FPS ;
		double next_frame_time = next_frame_num / FPS ;
		
		double init_timer = glfwGetTime();
		double curr_timer = glfwGetTime();
		while (curr_timer - init_timer <= next_frame_time - current_frame_time) {
			
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// printf("%f %f\n", (curr_timer - init_timer) / (next_frame_time - current_frame_time), glfwGetTime() - super_init_timer);
			draw((curr_timer - init_timer) / (next_frame_time - current_frame_time));
			
			save_animation_frame(frane_num++, width, height);
			
			glfwSwapBuffers(window);
			
			curr_timer = glfwGetTime();
		}
		current_frame_num = next_frame_num;
		// printf("Next frame %d \n", next_frame_num);
	}

	fclose(fp);
}
