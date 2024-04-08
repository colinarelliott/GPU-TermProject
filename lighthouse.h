#pragma once

//class for lighthouse scene
class lighthouse {
	public:
		//variables
		// timing
		float currentFrame = 0.0f;
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;

		//empty constructor
		lighthouse::lighthouse() {
			//all logic happens in drawLighthouse
		}

		//functions
		void drawLighthouse();
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		void processInput(GLFWwindow* window);
		GLuint loadTexture(const char* path);
};