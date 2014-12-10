#include "Application.h"

int main() {
	try {
		Application the_game;
		the_game.run();
	}
	catch (std::exception& e) {
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}