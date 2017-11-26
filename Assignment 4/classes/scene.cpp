#include "./scene.hpp"



// void printmat4(glm::mat4 Awv) {
// 	printf("\n");
// 	printf("%f, %f, %f, %f \n", Awv[0][0], Awv[1][0], Awv[2][0], Awv[3][0]);
// 	printf("%f, %f, %f, %f \n", Awv[0][1], Awv[1][1], Awv[2][1], Awv[3][1]);
// 	printf("%f, %f, %f, %f \n", Awv[0][2], Awv[1][2], Awv[2][2], Awv[3][2]);
// 	printf("%f, %f, %f, %f \n", Awv[0][3], Awv[1][3], Awv[2][3], Awv[3][3]);
// 	printf("\n");
// }

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
 *
 * @params 	   interpolation factor to be multiplied in every draw call
 */
void Scene::draw(float interpolation_factor) {
	glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(xpos + interpolation_factor * (next_xpos - xpos), ypos + interpolation_factor * (next_ypos - ypos), zpos + interpolation_factor * (next_zpos - zpos)));
	
	glm::mat4 rotation_mtx_x = glm::rotate( glm::mat4(1.0f), glm::radians(float(rotation_vec.x + interpolation_factor * (next_rotation_vec.x - rotation_vec.x))), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotation_mtx_y = glm::rotate( glm::mat4(1.0f), glm::radians(float(rotation_vec.y + interpolation_factor * (next_rotation_vec.y - rotation_vec.y))), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotation_mtx_z = glm::rotate( glm::mat4(1.0f), glm::radians(float(rotation_vec.z + interpolation_factor * (next_rotation_vec.z - rotation_vec.z))), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 rotation_matrix = rotation_mtx_z * rotation_mtx_y * rotation_mtx_x;

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
}

/**
 * @brief recalculate translation matrix of scene corresponding to third person camera
 *
 * @param key_state_translation 	key press boolean vector input 	{WASDZX}
 */
void Scene::translate(std::vector<bool> key_state_translation) {	
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

/**
 * @brief Saving keyframe for all models of this scene
 * 
 * @param frame_number 
 */
void Scene::save_keyframe(int frame_num) {
	FILE *fp = fopen(KEY_FRAME_FILE_NAME.c_str(), "a" );
	if (fp ==  NULL) {
		printf("Error opening file %s\n", KEY_FRAME_FILE_NAME.c_str());
		return;
	}

	// fprintf(fp, "Keyframe_no cam_Tx cam_Ty cam_Tz cam_Rx cam_Ry cam_Rz Light_status ");
	fprintf(fp, "%d ", frame_num);
	
	fprintf(fp, "%.2f ", xpos);
	fprintf(fp, "%.2f ", ypos);
	fprintf(fp, "%.2f ", zpos);
	
	fprintf(fp, "%.2f ", rotation_vec.x);
	fprintf(fp, "%.2f ", rotation_vec.y);
	fprintf(fp, "%.2f ", rotation_vec.z);
	fprintf(fp, "%d ", light_flag);

	for (int i = 1; i < model_list.size(); ++i) {
		printf("NAME %s\n", model_list[i]->get_id().c_str());
		model_list[i]->save_keyframe_hm(fp);
	}
	fprintf(fp, "\n");

	fclose(fp);
	return;
}

/*
 * @brief save current animation frame in out{{frame_num}}.tga
 * 
 * @param frame_num frame number to save (deciding image name)
 * @param windowWidth window width
 * @param windowHeight window height
*/ 
void Scene::save_animation_frame(int frame_num, int windowWidth, int windowHeight) {
	FILE *fp_out = fopen((IMAGES_FILE_NAME + "out" + std::to_string(frame_num) + ".tga").c_str(), "wb");
	if (fp_out == NULL) {
		printf("Error opening file %s\n", (IMAGES_FILE_NAME + "out.bmp").c_str());
	}

	unsigned char *pixel_data = new unsigned char[windowWidth * windowHeight * 3];
	short TGAhead[] = { 0, 2, 0, 0, 0, 0, windowWidth, windowHeight, 24 };

	glReadBuffer(GL_BACK);
	glReadPixels(0, 0, windowWidth, windowWidth, GL_BGR, GL_UNSIGNED_BYTE, pixel_data);

	fwrite(TGAhead, sizeof(TGAhead), 1, fp_out);
	fwrite(pixel_data, 3 * windowWidth * windowHeight, 1, fp_out);

	fclose(fp_out);
	delete[] pixel_data;
}

/**
 * @brief play the animation
 * 
 * @param window [description]
 */
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
	float super_init_timer = glfwGetTime();
	while (fscanf(fp, "%d ", &next_frame_num) != EOF) {
		
		fscanf(fp, "%f ", &next_xpos);
		fscanf(fp, "%f ", &next_ypos);
		fscanf(fp, "%f ", &next_zpos);

		fscanf(fp, "%f ", &next_rotation_vec.x);
		fscanf(fp, "%f ", &next_rotation_vec.y);
		fscanf(fp, "%f ", &next_rotation_vec.z);
		
		fscanf(fp, "%d ", &light_flag);

		for (int i = 1; i < model_list.size(); ++i) {
			model_list[i]->load_next_keyframe_hm(fp);
		}
		// printf("C :%d, N :%d\n", current_frame_num, next_frame_num);
		float current_frame_time = float(current_frame_num) / FPS ;
		float next_frame_time = float(next_frame_num) / FPS ;
		
		float init_timer = glfwGetTime();
		float curr_timer = init_timer;

		while (curr_timer - init_timer <= next_frame_time - current_frame_time) {
			
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// printf("%f %f %f %f\n", (curr_timer - init_timer) / (next_frame_time - current_frame_time), (curr_timer - init_timer),  glfwGetTime() - super_init_timer);
			draw((curr_timer - init_timer) / (next_frame_time - current_frame_time));
			
			save_animation_frame(frane_num++, width, height);
			
			glfwSwapBuffers(window);
			
			curr_timer = glfwGetTime();
		}
		current_frame_num = next_frame_num;
		xpos = next_xpos;
		ypos = next_ypos;
		zpos = next_zpos;
		rotation_vec = next_rotation_vec;
		printf("Next frame %d \n", next_frame_num);
	}
	printf("\n");
	for (int i = 1; i < model_list.size(); ++i) {
		model_list[i]->reload_last_keyframe_hm();
	}
	
	fclose(fp);
}
