#pragma once

class cinemagraph {
	public:
		cinemagraph();
		void drawCinemagraph();
		void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		void processInput(GLFWwindow* window);
		GLuint loadTexture(const char* path);
};