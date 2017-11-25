#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include "./global.hpp"
#include "./model.hpp"
#include "./openglParams.hpp"
#include "./heirarchical_model.hpp"
#include "./camera.hpp"
/**
 * @brief      Class for storing the entire scene data.
 */
class Scene {
private:
	const int FPS = 3;
	// Translation  and Rotation Parameters
	const glm::vec4 X_UNIT = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	const glm::vec4 Y_UNIT = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	const glm::vec4 Z_UNIT = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	const float TRANS_DELTA = 0.2;
	float xpos = 0.0, ypos = 0.0, zpos = 0.0;
	const float ROT_DELTA = 0.03;
	float xrot = 0.0, yrot = 0.0, zrot = 0.0;
	
	//Scene rotation and translation matrices
	glm::mat4 translation_matrix = glm::mat4(1.0f);
	glm::mat4 rotation_matrix = glm::mat4(1.0f);
	
	// Folder path where the all scene models are present
	const std::string MODEL_FILE_NAME = "./models/";
	const std::string KEY_FRAME_FILE_NAME = "./animation/keyframes.txt";
	const std::string IMAGES_FILE_NAME = "./animation/frames/";
	
	Camera* cam;
	OpenglParams* params;
	
	int current_frame_num = 0, next_frame_num;
	int light_flag = 1;
	std::vector<HeirarchicalModel*> model_list;

	void save_animation_frame(int frame_num, int windowWidth, int windowHeight);

public:
	Scene();
	~Scene();
	void load_new_model(std::string filename, std::string id, glm::vec3 scale_vec, glm::vec3 translation_vec);
	void draw(double interpolation_factor); 
	HeirarchicalModel* find_heirarchical_model_by_id(std::string id);
	void rotate(std::vector<bool> key_state_rotation);
	void translate(std::vector<bool> key_state_translation, bool key_state_recenter);
	bool toggle_light();

	void save_keyframe(int num);
	void play(GLFWwindow* window);
};

#endif