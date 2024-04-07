#pragma once
#include "main.h"

cinemagraph::cinemagraph() {
	//constructor
}

void cinemagraph::drawCinemagraph() {
	//initialize, set window hints
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create the window
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Cinemagraph", NULL, NULL);

	//if window not valid, terminate
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	//add window to current context
	glfwMakeContextCurrent(window);
	//set callback for resize
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//check if GLAD loader loaded, if not, terminate
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	//enable opengl depth test, blend, alpha params
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//build and compile shaders
	Shader shader("shaders/blendShader.vs", "shaders/blendShader.fs");
	Shader textShader("shaders/textShader.vs", "shaders/textShader.fs");

	
	//Setup Text Projection
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(1280), 0.0f, static_cast<float>(720));
	textShader.use();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	FreeTypeSetup();
	
	//setup vertex data and buffers and configure vertex attributes

	unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
	};

	float foregroundVertices[] =  {
		// positions          // colors           // texture coords
		 1.0f,  1.0f, 0.1f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 1.0f, -1.0f, 0.1f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-1.0f, -1.0f, 0.1f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-1.0f,  1.0f, 0.1f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};

	float sunVertices[] = {
		// positions		   // colors           //texture coords
		 -1.36f,  0.2f + 0.5f, 0.2f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 -1.36f, -0.2f + 0.5f,0.2f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-1.48f, -0.2f + 0.5f, 0.2f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-1.48f,  0.2f + 0.5f, 0.2f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left s
	};

	float moonVertices[] = {
		// positions          // colors           //texture coords
		-1.36f,  0.2f, -0.2f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 -1.36f, -0.2f, -0.2f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-1.48f, -0.2f, -0.2f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-1.48f,  0.2f, -0.2f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left s
	};

	float lighthouseVertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.6f, -0.1f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.4f, -0.1f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		 0.1f, -0.4f, -0.1f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		 0.1f,  0.6f, -0.1f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};

	float lighthouseBeamVertices[] = {
		// positions          // colors           // texture coords
		 0.3f,  0.55f, -0.4f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.3f, 0.25f, -0.4f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		 -1.2f, 0.25f, -0.4f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		 -1.2f,  0.55f, -0.4f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};

	
	// configure VAO/VBO for text
	glGenVertexArrays(1, &textVAO);
	glGenBuffers(1, &textVBO);
	glBindVertexArray(textVAO);
	glBindBuffer(GL_ARRAY_BUFFER, textVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	

	//configure VAO/VBO for cinemagraph foreground
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO); 

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(foregroundVertices), foregroundVertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//VAO, VBO, EBO for sun and moon
	unsigned int sunVBO, sunVAO, sunEBO;
	glGenVertexArrays(1, &sunVAO);
	glGenBuffers(1, &sunVBO);
	glGenBuffers(1, &sunEBO);
	glBindVertexArray(sunVAO);
	glBindBuffer(GL_ARRAY_BUFFER, sunVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sunVertices), sunVertices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sunEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//VAO, VBO, EBO for moon
	unsigned int moonVBO, moonVAO, moonEBO;
	glGenVertexArrays(1, &moonVAO);
	glGenBuffers(1, &moonVBO);
	glGenBuffers(1, &moonEBO);
	glBindVertexArray(moonVAO);
	glBindBuffer(GL_ARRAY_BUFFER, moonVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(moonVertices), moonVertices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, moonEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//VAO, VBO, EBO for lighthouse
	unsigned int lighthouseVBO, lighthouseVAO, lighthouseEBO;
	glGenVertexArrays(1, &lighthouseVAO);
	glGenBuffers(1, &lighthouseVBO);
	glGenBuffers(1, &lighthouseEBO);
	glBindVertexArray(lighthouseVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lighthouseVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lighthouseVertices), lighthouseVertices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lighthouseEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//VAO, VBO, EBO for lighthouseBeam
	unsigned int lighthouseBeamVAO, lighthouseBeamVBO, lighthouseBeamEBO;
	glGenVertexArrays(1, &lighthouseBeamVAO);
	glGenBuffers(1, &lighthouseBeamVBO);
	glGenBuffers(1, &lighthouseBeamEBO);
	glBindVertexArray(lighthouseBeamVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lighthouseBeamVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lighthouseBeamVertices), lighthouseBeamVertices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lighthouseBeamEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//load texture into shader
	shader.use();
	glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0);

	//flip image on load
	stbi_set_flip_vertically_on_load(true);
	//load foreground image
	//https://cat.pexels.com/photo/a-lighthouse-on-a-cape-6263774/
	GLuint foregroundTexture = loadTexture("resources/img/foreground.png");
	//load sun image
	//https://www.timeanddate.com/astronomy/sun/about
	GLuint sunTexture = loadTexture("resources/img/sun.png");
	//load moon image
	//https://www.pexels.com/photo/photo-of-full-moon-975012/
	GLuint moonTexture = loadTexture("resources/img/moon.png");
	//load lighthouse image
	//https://www.istockphoto.com/photo/peggys-cove-lighthouse-gm160353394-22770308?searchscope=image%2Cfilm
	GLuint lighthouseTexture = loadTexture("resources/img/lighthouse.png");
	//load lighthouse beam image
	//Homemade in Photoshop
	GLuint lighthouseBeamTexture = loadTexture("resources/img/lighthouseBeam.png");
	
	//clear
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	while (!glfwWindowShouldClose(window)) {
		//MAIN LOOP
		//get input

		// per-frame time logic
		// --------------------
		currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		offset = sin(glfwGetTime());
		float sunOffset = offset * -1;

		processInput(window);

		//rendering commands here =============

		//clear colour set & clear
		glClearColor(0.0f, 0.6f*sunOffset, 0.9f*sunOffset, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		textShader.use();
		//Show text
		RenderText(textShader, "Lighthouse Cinemagraph", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
		RenderText(textShader, "Colin Elliott", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));

		shader.use();

		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, foregroundTexture);
		//set uniform for texture
		glUniform1i(glGetUniformLocation(shader.ID, "myTexture"), 0);
		//draw foreground
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//sun
		//bind sun texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sunTexture);
		//set uniform for texture
		glUniform1i(glGetUniformLocation(shader.ID, "myTexture"), 0);
		//update sun position based on offset (sin func)
		float sunVertices[] = {
			// positions                             // colors           //texture coords
			-0.28f,  0.2f + sunOffset * .8, -0.2f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
			 -0.28f, -0.2f + sunOffset * .8, -0.2f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
			-0.04f, -0.2f + sunOffset * .8, -0.2f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
			-0.04f,  0.2f + sunOffset * .8, -0.2f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left s
		};
		//update sun VBO
		glBindBuffer(GL_ARRAY_BUFFER, sunVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(sunVertices), sunVertices, GL_DYNAMIC_DRAW);
		//draw sun
		glBindVertexArray(sunVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		//moon
		//bind moon texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, moonTexture);
		//set uniform for texture
		glUniform1i(glGetUniformLocation(shader.ID, "myTexture"), 0);
		//update moon position based on offset
		float moonVertices[] = {
			// positions                      // colors           //texture coords
			-0.52f,  0.2f + offset * .8, -0.1f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
			 -0.52f, -0.2f + offset * .8, -0.1f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
			-0.28f, -0.2f + offset * .8, -0.1f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
			-0.28f,  0.2f + offset * .8, -0.1f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left s
		};
		//update moon VBO
		glBindBuffer(GL_ARRAY_BUFFER, moonVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(moonVertices), moonVertices, GL_DYNAMIC_DRAW);
		//draw moon
		glBindVertexArray(moonVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//lighthouse
		//bind lighthouse texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, lighthouseTexture);
		//set uniform for texture
		glUniform1i(glGetUniformLocation(shader.ID, "myTexture"), 0);
		//draw lighthouse
		glBindVertexArray(lighthouseVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//lighthouse beam
		//bind lighthouse beam texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, lighthouseBeamTexture);
		//set uniform for texture
		glUniform1i(glGetUniformLocation(shader.ID, "myTexture"), 0);
		//draw lighthouse beam
		glBindVertexArray(lighthouseBeamVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, foregroundTexture);
		//set uniform for texture
		glUniform1i(glGetUniformLocation(shader.ID, "myTexture"), 0);
		float foregroundVertices[] = {
			// positions          // colors           // texture coords
			 1.0f,  1.0f, 0.1f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
			 1.0f, -1.0f, 0.1f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
			-1.0f, -1.0f, 0.1f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
			-1.0f,  1.0f, 0.1f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
		};
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(foregroundVertices), foregroundVertices, GL_DYNAMIC_DRAW);
		//draw foreground
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//====================================

		//check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//delete all resources
	glDeleteVertexArrays(1, &textVAO);
	glDeleteBuffers(1, &textVBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &sunVAO);
	glDeleteBuffers(1, &sunVBO);
	glDeleteBuffers(1, &sunEBO);
	glDeleteVertexArrays(1, &moonVAO);
	glDeleteBuffers(1, &moonVBO);
	glDeleteBuffers(1, &moonEBO);
	glDeleteVertexArrays(1, &lighthouseVAO);
	glDeleteBuffers(1, &lighthouseVBO);
	glDeleteBuffers(1, &lighthouseEBO);

	glfwTerminate();
}

void cinemagraph::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void cinemagraph::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//load texture from path function
GLuint cinemagraph::loadTexture(const char* path) {
	GLuint textureID;
	glGenTextures(1, &textureID);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data) {
		GLenum format;
		if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;
		else
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else {
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

void cinemagraph::RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color)
{
	// activate corresponding render state	
	shader.use();
	glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(textVAO);

	// iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		float xpos = x + ch.Bearing.x * scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;
		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, textVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void cinemagraph::FreeTypeSetup() {
	// FreeType
	// --------
	FT_Library ft;
	// All functions return a value different than 0 whenever an error occurred
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	}

	// find path to font
	std::string font_name = "resources/fonts/Antonio-Regular.ttf";
	if (font_name.empty())
	{
		std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
	}

	// load font as face
	FT_Face face;
	if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	}
	else {
		// set size to load glyphs as
		FT_Set_Pixel_Sizes(face, 0, 48);

		// disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// load first 128 characters of ASCII set
		for (unsigned char c = 0; c < 128; c++)
		{
			// Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// generate texture
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			// set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// now store character for later use
			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				static_cast<unsigned int>(face->glyph->advance.x)
			};
			Characters.insert(std::pair<char, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	// destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}