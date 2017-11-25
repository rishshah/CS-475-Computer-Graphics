#include "callbacks.hpp"

/**
 * @brief      Update(Set/Reset) global shared varible key_state_rotation according to
 *             the key used.
 *             0 - Up   |
 *             1 - Down     |
 *             2 - Left     |
 *             3 - Right    |
 *             4 - PageUp   |
 *             5 - PageDown
 *
 * @param[in]  key     The key pressed
 * @param[in]  action  The action (release or press)
 */
void rotation_callback(int key, int action) {
	// Rotate about Xaxis
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		key_state_rotation[0] = true;
		key_state_rotation[1] = false;

	}
	else if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {
		key_state_rotation[0] = false;
		key_state_rotation[1] = false;
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		key_state_rotation[1] = true;
		key_state_rotation[0] = false;
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
		key_state_rotation[1] = false;
		key_state_rotation[0] = false;
	}

	// Rotate about Yaxis
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		key_state_rotation[2] = true;
		key_state_rotation[3] = false;
	}
	else if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
		key_state_rotation[2] = false;
		key_state_rotation[3] = false;
	}
	else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		key_state_rotation[3] = true;
		key_state_rotation[2] = false;
	}
	else if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
		key_state_rotation[3] = false;
		key_state_rotation[2] = false;
	}

	// Rotate about Zaxis
	else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS) {
		key_state_rotation[4] = true;
		key_state_rotation[5] = false;
	}
	else if (key == GLFW_KEY_PAGE_UP && action == GLFW_RELEASE) {
		key_state_rotation[4] = false;
		key_state_rotation[5] = false;
	}
	else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS) {
		key_state_rotation[5] = true;
		key_state_rotation[4] = false;
	}
	else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_RELEASE) {
		key_state_rotation[5] = false;
		key_state_rotation[4] = false;
	}
}

/**
 * @brief      Update(Set/Reset) global shared varible key_state_translation according to
 *             the key used.
 *             0 - A    |
 *             1 - D    |
 *             2 - W    |
 *             3 - S    |
 *             4 - Z    |
 *             5 - X
 *
 * @param[in]  key     The key pressed
 * @param[in]  action  The action (release or press)
 */
void translation_callback(int key, int action) {
	// Translate along Xaxis
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		key_state_translation[0] = true;
		key_state_translation[1] = false;
	}
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
		key_state_translation[0] = false;
		key_state_translation[1] = false;
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		key_state_translation[1] = true;
		key_state_translation[0] = false;
	}
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
		key_state_translation[1] = false;
		key_state_translation[0] = false;
	}

	// Translate along Yaxis
	else if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		key_state_translation[2] = true;
		key_state_translation[3] = false;
	}
	else if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
		key_state_translation[2] = false;
		key_state_translation[3] = false;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		key_state_translation[3] = true;
		key_state_translation[2] = false;
	}
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
		key_state_translation[3] = false;
		key_state_translation[2] = false;
	}

	// Translate along Zaxis
	else if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		key_state_translation[4] = true;
		key_state_translation[5] = false;
	}
	else if (key == GLFW_KEY_Z && action == GLFW_RELEASE) {
		key_state_translation[4] = false;
		key_state_translation[5] = false;
	}
	else if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		key_state_translation[5] = true;
		key_state_translation[4] = false;
	}
	else if (key == GLFW_KEY_X && action == GLFW_RELEASE) {
		key_state_translation[5] = false;
		key_state_translation[4] = false;
	}
}

/**
 * @brief select part of model based on which key is pressed
 *
 * @param key key pressed
 * @return returns id of selected part
 */
std::string handle_modelling_callback(std::string model_id, int key) {
	if (model_id == "perry") {
		switch (key) {
		case GLFW_KEY_1:
			return "eye_ball_left";
		case GLFW_KEY_2:
			return "eye_ball_right";
		case GLFW_KEY_3:
			return "lower_mouth";
		case GLFW_KEY_4:
			return "tail";
		case GLFW_KEY_5:
			return "front_left_leg";
		case GLFW_KEY_6:
			return "front_right_leg";
		case GLFW_KEY_7:
			return "back_left_leg";
		case GLFW_KEY_8:
			return "back_right_leg";
		case GLFW_KEY_9:
			return "body";
		}
	}
	else if (model_id == "phineas") {
		switch (key) {
		case GLFW_KEY_1:
			return "face";
		case GLFW_KEY_2:
			return "sleeve_left";
		case GLFW_KEY_3:
			return "sleeve_right";
		case GLFW_KEY_4:
			return "hand_left";
		case GLFW_KEY_5:
			return "hand_right";
		case GLFW_KEY_6:
			return "thigh_left";
		case GLFW_KEY_7:
			return "thigh_right";
		case GLFW_KEY_8:
			return "leg_left";
		case GLFW_KEY_9:
			return "leg_right";
		case GLFW_KEY_0:
			return "body";
		}
	}
}

namespace base {
/**
 * @brief handle input key presses from keyboard
 */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	
	// Switch to Recode mode
	else if ( key == GLFW_KEY_R  and action == GLFW_PRESS) {
		mode = RECORD_MODE;
		printf("In Recording Mode...\n");
	}
	// Switch to Playback mode
	else if (key == GLFW_KEY_P and action == GLFW_PRESS) {
		mode = PLAYBACK_MODE;
		printf("In Playback Mode...\n");
		printf("Playing Animation...\n");
		scene->play(window);
		printf("Animation Saved...\n");
		mode = RECORD_MODE;
		printf("In Recording Mode...\n");

	}
	// Switch to Playback mode
	else if (key == GLFW_KEY_V and action == GLFW_PRESS) {
		mode = VIEW_MODE;
		printf("In View Mode...\n");
	}

	//Save Keyframe callback
	else if (key == GLFW_KEY_Q and action == GLFW_PRESS) {
		if (mode == RECORD_MODE) {
			printf("Enter keyframe number: ");
			int num; std::cin >> num;
			scene->save_keyframe(num);
			printf("Keyframe %d saved!\n", num);
		}
	}

	// Third Person View Callbacks	
	else if ( key == GLFW_KEY_UP or key == GLFW_KEY_DOWN or
	          key == GLFW_KEY_LEFT or key == GLFW_KEY_RIGHT or
	          key == GLFW_KEY_PAGE_UP or key == GLFW_KEY_PAGE_DOWN) {
		if (mode == RECORD_MODE or  mode == VIEW_MODE)
			rotation_callback(key, action);
	}
	else if ( key == GLFW_KEY_W or
	          key == GLFW_KEY_S or
	          key == GLFW_KEY_A or
	          key == GLFW_KEY_D or
	          key == GLFW_KEY_Z or
	          key == GLFW_KEY_X) {
		if (mode == RECORD_MODE or  mode == VIEW_MODE)
			translation_callback(key, action);
	}




	//Modelling mode callbacks
	// Toggle spotlight
	else if (key == GLFW_KEY_L and action == GLFW_PRESS) {
		if (mode == RECORD_MODE) {
			if (scene->toggle_light()) {
				printf("Spotlight On.\n");
			} else {
				printf("Spotlight Off.\n");
			}
		}
	}
	//Modelling mode PERRY
	else if (key == GLFW_KEY_N and action == GLFW_PRESS) {
		if (mode == RECORD_MODE) {
			curr_heirarchical_model = scene->find_heirarchical_model_by_id("perry");
			curr_model = curr_heirarchical_model->find_by_id("body");
			printf("Modelling PERRY now!\n");
		}
	}
	//Modelling mode PHINEAS
	else if (key == GLFW_KEY_H and action == GLFW_PRESS) {
		if (mode == RECORD_MODE) {
			curr_heirarchical_model = scene->find_heirarchical_model_by_id("phineas");
			curr_model = curr_heirarchical_model->find_by_id("body");
			printf("Modelling PHINEAS now!\n");
		}
	}
	//Model individual parts
	else if (action == GLFW_PRESS and
	         (key == GLFW_KEY_0 or
	          key == GLFW_KEY_1 or
	          key == GLFW_KEY_2 or
	          key == GLFW_KEY_3 or
	          key == GLFW_KEY_4 or
	          key == GLFW_KEY_5 or
	          key == GLFW_KEY_6 or
	          key == GLFW_KEY_7 or
	          key == GLFW_KEY_8 or
	          key == GLFW_KEY_9)
	        ) {
		if (mode == RECORD_MODE and curr_heirarchical_model != NULL) {
			std::string id = handle_modelling_callback(curr_heirarchical_model->get_id(), key);
			curr_model = curr_heirarchical_model->find_by_id(id);
			if (curr_model != NULL) {
				printf("Modelling %s now!\n", id.c_str());
			} else {
				printf("Part selection failed! Retry again...\n");
			}
		}
	}
}

};
