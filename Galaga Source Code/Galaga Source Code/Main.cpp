#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC


#include <SFML/Graphics.hpp>

class Galaga {

private:
	// Class Vars
	sf::RenderWindow mWindow;
	sf::CircleShape mPlayer;
	// Class Methods
	void processEvents();
	void update();
	void render();

public:
	// Constructors
	Galaga();
	// Usage Methods
	void run();

};

Galaga::Galaga(): mWindow(sf::VideoMode(640, 640), "GALAGA"), mPlayer() {
	mPlayer.setRadius(6.f);
	mPlayer.setPosition(320.f, 320.f);
	mPlayer.setFillColor(sf::Color::Green);
}

void Galaga::run() {
//	Causes the game to start!
	while (mWindow.isOpen()) {
		processEvents();
		update();
		render();
	}
}

void Galaga::processEvents() {
//	Handles user input.
	sf::Event event;
	while (mWindow.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			mWindow.close();
		}
	}
}

void Galaga::update() {
//	"Updates the game logic, that is, everything that happens in the game."
}

void Galaga::render() {
//	Draws everything a user will see to the screen.
	mWindow.clear();
	mWindow.draw(mPlayer);
	mWindow.display();
}

int main() {
	Galaga the_game;
	the_game.run();
	return 0;
}