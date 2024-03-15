#pragma once

class lighthouse {
	public:
		//variables
		// timing
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;

		//constructor
		lighthouse();

		//functions
		void drawLighthouse();
		void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		void processInput(GLFWwindow* window);
		GLuint loadTexture(const char* path);
		void setupVertexPointers();
		void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};