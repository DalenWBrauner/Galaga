#include "Galaga.h"
#include <stdexcept>
#include <iostream>

int main() {
	try {
		Galaga the_game;
		the_game.run();
	}
	catch (std::exception& e) {
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}