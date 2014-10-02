#include "Galaga.h"

Galaga::Galaga()
	: mWindow(sf::VideoMode(512, 480), "GALAGA")
	, mWorld(mWindow)
	, mTexture()
	, mPlayer()
	{

	loadAssets();

	// Sets the player to the ship sprite
	mPlayer.setTexture(mTexture);
	mPlayer.setTextureRect(sf::IntRect(120, 1, 16, 16));
	mPlayer.setScale(sf::Vector2f(2.f, 2.f));

	// Constants set at game instantiation
	mPlayer.setPosition(250.f, 400.f);
	mPlayer.setOrigin(8, 8);
	PlayerSpeed = 200.f;
	TimePerFrame = sf::seconds(1.f / 60.f);

	// Variables
	highscore = 0;	//Obviously temporary placement
	yourscore = 0;
	mIsMovingLeft = false;
	mIsMovingRight = false;

	// Setup SFX
	sfxCoin.setBuffer(sbfCoin);
	sfxCaptured.setBuffer(sbfCaptured);
	sfxFiring.setBuffer(sbfFiring);
	sfxIncoming.setBuffer(sbfIncoming);
	sfxDestroyed.setBuffer(sbfDestroyed);
	sfxStart.setBuffer(sbfStart);
	sfxIntro.setBuffer(sbfIntro);

	// Prepare Text
	SFXText.setFont(font);
	SFXText.setCharacterSize(15);
	SFXText.setColor(sf::Color::White);
	SFXText.setPosition(25, 50);
	SFXText.setString("Q: Intro\nW: Start\nE: Incoming\nR: Firing\nT: Destroyed\nY: Coin\nU: Captured");

	scoreDisplay.setFont(font);
	scoreDisplay.setCharacterSize(15);
	scoreDisplay.setColor(sf::Color::Red);
	scoreDisplay.setPosition(400, 50);
	scoreDisplay.setString("High\n Score\n\n\n\n1UP");
}

void Galaga::loadAssets() {
	// Loads the sprite sheet
	if (!font.loadFromFile("../../Media/Galaga.ttf"))
		throw std::runtime_error("Failed to load font.");

	if (!mTexture.loadFromFile("../../Media/Sprite Sheet.png"))
		throw std::runtime_error("Failed to load sprite sheet.");

	if (!sbfCoin.loadFromFile("../../Media/Coin.wav"))
		throw std::runtime_error("Failed to load coin.wav.");
	if (!sbfCaptured.loadFromFile("../../Media/Fighter_Captured.wav"))
		throw std::runtime_error("Failed to load coin.wav.");
	if (!sbfFiring.loadFromFile("../../Media/Firing.wav"))
		throw std::runtime_error("Failed to load coin.wav.");
	if (!sbfIncoming.loadFromFile("../../Media/Flying_Enemy.wav"))
		throw std::runtime_error("Failed to load coin.wav.");
	if (!sbfDestroyed.loadFromFile("../../Media/Kill_Enemy.wav"))
		throw std::runtime_error("Failed to load coin.wav.");
	if (!sbfStart.loadFromFile("../../Media/Level_Start.wav"))
		throw std::runtime_error("Failed to load coin.wav.");
	if (!sbfIntro.loadFromFile("../../Media/Theme_Song.wav"))
		throw std::runtime_error("Failed to load coin.wav.");

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
	case sf::Keyboard::Q:
		sfxIntro.play();
		break;
	case sf::Keyboard::W:
		sfxStart.play();
		break;
	case sf::Keyboard::E:
		sfxIncoming.play();
		break;
	case sf::Keyboard::R:
		sfxFiring.play();
		break;
	case sf::Keyboard::T:
		sfxDestroyed.play();
		break;
	case sf::Keyboard::Y:
		sfxCoin.play();
		break;
	case sf::Keyboard::U:
		sfxCaptured.play();
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

	// Player Movement
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;
	if (mIsMovingRight)
		movement.x += PlayerSpeed;
	mPlayer.move(movement * deltaTime.asSeconds());

	// Camera Movement
	//mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());

	mWorld.update(deltaTime);
	
	// Keeping Score
//	std::stringstream scoreText;
//	scoreText << "High\n Score\n" << highscore << "\nYour\n Score\n" << yourscore;
//	scoreDisplay.setString(scoreText.str());
}

void Galaga::render() {
	// Draws everything a user will see to the screen.
	mWindow.clear();

	mWorld.draw();
	mWindow.setView(mWindow.getDefaultView());

//	mWindow.draw(SFXText);
//	mWindow.draw(scoreDisplay);
//	mWindow.draw(mPlayer);

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
	try {
		std::cout << "Let's make a game!" << std::endl;
		Galaga the_game;
		std::cout << "Alright, time to run..." << std::endl;
		the_game.run();
		std::cout << "Phew, all done!" << std::endl;
	}
	catch (std::exception& e) {
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}