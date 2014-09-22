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
	// Mechanics
	sf::RenderWindow mWindow;
	sf::Time TimePerFrame;

	// Images
	sf::Texture mTexture;
	sf::Sprite mPlayer;

	// Motion
	float PlayerSpeed;
	bool mIsMovingLeft;
	bool mIsMovingRight;

	// Class Methods
	void handlePlayerInput(sf::Keyboard::Key, bool);
	void processEvents();
	void update(sf::Time);
	void render();
	void loadAssets();

public:
	// Constructors
	Galaga();

	// Usage Methods
	void run();

};

Galaga::Galaga()
	: mWindow(sf::VideoMode(600, 800), "GALAGA")
	, mTexture()
	, mPlayer()
	{

	loadAssets();

	// Sets the player to the ship sprite
	mPlayer.setTexture(mTexture);
	mPlayer.setTextureRect(sf::IntRect(120, 1, 16, 16));
	mPlayer.setScale(sf::Vector2f(2.f, 2.f));

	// Constants set at game instantiation
	mPlayer.setPosition(300.f, 666.f);
	PlayerSpeed = 200.f;
	TimePerFrame = sf::seconds(1.f / 60.f);

	// Variables
	mIsMovingLeft = false;
	mIsMovingRight = false;
}

void Galaga::loadAssets() {
	// Loads the sprite sheet
	if (!mTexture.loadFromFile(			"../../Media/Sprite Sheet.png"))		{
		throw std::runtime_error("Failed to load sprite sheet.");
	}
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

void Galaga::update(sf::Time deltaTime) {
	// Manipulates the game logic at each 'tick'
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;
	if (mIsMovingRight)
		movement.x += PlayerSpeed;

	mPlayer.move(movement * deltaTime.asSeconds());
}

void Galaga::render() {
	// Draws everything a user will see to the screen.
	mWindow.clear();
	mWindow.draw(mPlayer);
	mWindow.display();
}

void Galaga::run() {
	// Causes the game to start!

	// Synchronizes our time-step clocks
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// While our game is running...
	while (mWindow.isOpen()) {
		processEvents();

		// Grab how much time has passed since our last time-step
		timeSinceLastUpdate += clock.restart();
		// Run the appropriate number of time-steps that ought to have passed
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;

			// update() and processEvents() within each individual time step
			processEvents();
			update(TimePerFrame);
		}

		// Render only after we've caught up
		render();
	}
}

int main() {
	Galaga the_game;
	the_game.run();
}