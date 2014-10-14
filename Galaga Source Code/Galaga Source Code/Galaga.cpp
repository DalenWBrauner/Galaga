#include "Galaga.h"

Galaga::Galaga()
	: mWindow(sf::VideoMode(512, 480), "GALAGA")
	, mWorld(mWindow)
	, mPlayer()
	{
	loadAssets();
	PlayerSpeed = 7500.f;
	TimePerFrame = sf::seconds(1.f / 60.f);
	yourScore = 0;
	highScore = 0;	//Temporary

	// Prepare SFX
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

void Galaga::handleGameInput() {
	// For handling input unrelated to the player object.
	if		(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		sfxIntro.play();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		sfxStart.play();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		sfxIncoming.play();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		sfxFiring.play();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
		sfxDestroyed.play();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
		sfxCoin.play();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
		sfxCaptured.play();
	}
}

void Galaga::processEvents() {
	//	Accepts user input.

	CommandQueue& commands = mWorld.getCommandQueue();

	sf::Event event;
	while (mWindow.pollEvent(event)) {
		// While there are still events on the event stack:
		if (event.type == sf::Event::Closed) {
			mWindow.close();
		}
		else if (event.type == sf::Event::LostFocus) {
			//pause the game
		}
		else {
			// for handling events sequentially
			mPlayer.handleEvent(event, commands);
		}
	}
	// for checking current events
	mPlayer.handleRealTimeInput(commands);
	handleGameInput();
}

void Galaga::update(sf::Time deltaTime) {
	// Manipulates the game logic at each 'tick'

	// Player Movement
	sf::Vector2f movement(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		movement.x -= PlayerSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		movement.x += PlayerSpeed;
	mWorld.movePlayer(movement * deltaTime.asSeconds());

	mWorld.update(deltaTime);
	
	// Keeping Score
//	std::stringstream scoreText;
//	scoreText << "High\n Score\n" << highscore << "\nYour\n Score\n" << yourscore;
//	scoreDisplay.setString(scoreText.str());
}

void Galaga::render() {
	// Draws everything a user will see to the screen.
	mWindow.clear();
	//mWindow.setView( sf::View(sf::Vector2f(256.f, 240.f), sf::Vector2f(512.f, 480.f)));

	mWorld.draw();
	mWindow.draw(SFXText);
	mWindow.draw(scoreDisplay);

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
		//std::cout << "Let's make a game!" << std::endl;
		Galaga the_game;
		//std::cout << "Alright, time to run..." << std::endl;
		the_game.run();
		//std::cout << "Phew, all done!" << std::endl;
	}
	catch (std::exception& e) {
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}