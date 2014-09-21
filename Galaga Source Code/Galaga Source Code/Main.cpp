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
	bool mIsMovingLeft;
	bool mIsMovingRight;

	// Class Methods
	void handlePlayerInput(sf::Keyboard::Key, bool);
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
	mIsMovingLeft = false;
	mIsMovingRight = false;
}

void Galaga::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
	// Controls the game based on user input.
	switch (key) {
	case sf::Keyboard::Left:
		mIsMovingLeft = isPressed;
		break;
	case sf::Keyboard::Right:
		mIsMovingRight = isPressed;
		break;
	}
}

void Galaga::processEvents() {
	//	Accepts user input.
	sf::Event event;
	while (mWindow.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Galaga::update() {
	// Manipulates the game logic at each 'tick'
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingLeft)
		movement.x -= 1.f;
	if (mIsMovingRight)
		movement.x += 1.f;

	mPlayer.move(movement);
}

void Galaga::render() {
	// Draws everything a user will see to the screen.
	mWindow.clear();
	mWindow.draw(mPlayer);
	mWindow.display();
}

void Galaga::run() {
	// Causes the game to start!
	while (mWindow.isOpen()) {
		processEvents();
		update();
		render();
	}
}

int main() {
	Galaga the_game;
	the_game.run();
	return 0;
}