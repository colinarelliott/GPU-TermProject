#pragma once

//class for cinemagraph scene
class cinemagraph {
	public:
		float offset = 0.0f;
		cinemagraph::cinemagraph() {
			//empty constructor, all logic happens in drawCinemagraph
		}
		void drawCinemagraph();
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		void processInput(GLFWwindow* window);
		GLuint loadTexture(const char* path);
		void SetupVertexPointers();
};