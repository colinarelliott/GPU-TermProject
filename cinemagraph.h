#pragma once

class cinemagraph {
	/// Holds all state information relevant to a character as loaded using FreeType
	struct Character {
		unsigned int TextureID; // ID handle of the glyph texture
		glm::ivec2   Size;      // Size of glyph
		glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
		unsigned int Advance;   // Horizontal offset to advance to next glyph
	};

	std::map<GLchar, Character> Characters;
	unsigned int textVAO, textVBO;

	public:
		//variables
		// timing
		float currentFrame = 0.0f;
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
		float offset = 0.0f;

		cinemagraph();
		void drawCinemagraph();
		void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		void processInput(GLFWwindow* window);
		GLuint loadTexture(const char* path);
		void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color);
		void FreeTypeSetup();
};