#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "main.h"

// Choose between scenes
int main() {
	
	//create scenes
	lighthouse lighthouse;
	cinemagraph cinemagraph;

	//menu toggle and choice
	bool menu = true;
	int choice;

	//main menu
	while (menu) {
		system("CLS");
		std::cout << "Welcome to the Colin's GPU Programming Term Project!" << std::endl;
		std::cout << "Please select a scene to render:" << std::endl;
		std::cout << "1. Lighthouse (3D Scene)" << std::endl;
		std::cout << "2. Cinemagraph (2D Scene)" << std::endl;
		std::cout << "3. Exit" << std::endl;
		std::cin >> choice;

		switch (choice) {
			case 1:
				lighthouse.drawLighthouse();
				break;
			case 2:
				cinemagraph.drawCinemagraph();
				break;
			case 3:
				menu = false;
				break;
			default:
				break;
		}
	}
	return 0;
}