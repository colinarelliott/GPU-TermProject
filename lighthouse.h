#pragma once

class lighthouse {
	/// Holds all state information relevant to a character as loaded using FreeType
	struct Character {
		unsigned int TextureID; // ID handle of the glyph texture
		glm::ivec2   Size;      // Size of glyph
		glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
		unsigned int Advance;   // Horizontal offset to advance to next glyph
	};

	std::map<GLchar, Character> Characters;
	unsigned int VAO, VBO;

	public:
		//variables
		// timing
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;

		//constructor
		lighthouse();

		//functions
		void drawLighthouse();
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		void processInput(GLFWwindow* window);
		GLuint loadTexture(const char* path);
		void setupVertexPointers();
		void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color);
		void FreeTypeSetup();
};