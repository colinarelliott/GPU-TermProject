#pragma once

class lighthouse {
	public:
		lighthouse();
		void drawLighthouse();
		void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		void processInput(GLFWwindow* window);
		GLuint loadTexture(const char* path);
		void setupVertexPointers();
};