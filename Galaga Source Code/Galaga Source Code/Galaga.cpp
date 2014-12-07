#include "Galaga.h"
#include "Application.h"

const float Galaga::PlayerSpeed = 10000.0f; // It's really strange this number is so high

Galaga::Galaga()
	: mWindow(sf::VideoMode(512, 480), "GALAGA")
	, mWorld(mWindow)
	, mPlayer()
	{
	loadAssets();
	TimePerFrame = sf::seconds(1.f / 60.f);
	yourScore = 0;
	highScore = 9900;	//Temporary

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
	SFXText.setString("SFX:\nQ: Intro\nW: Start\nE: Incoming\nR: Firing\nT: Destroyed\nY: Coin\nU: Captured");

	scoreText.setFont(font);
	scoreText.setCharacterSize(15);
	scoreText.setColor(sf::Color::Red);
	scoreText.setPosition(400, 50);
	scoreText.setString("High\n Score\n\n\n\n1UP\n");

	scoreDisplay.setFont(font);
	scoreDisplay.setCharacterSize(15);
	scoreDisplay.setColor(sf::Color::White);
	scoreDisplay.setPosition(scoreText.getPosition());
	scoreDisplay.setString("\n\n" + std::to_string(highScore) + "\n\n\n\n" + std::to_string(yourScore));
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
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
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
		yourScore++;
		if (yourScore > highScore)
			highScore = yourScore;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)) {
		yourScore--;
		if (yourScore > highScore)
			highScore = yourScore;
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
	scoreDisplay.setString("\n\n" + std::to_string(highScore) + "\n\n\n\n" + std::to_string(yourScore));
}

void Galaga::render() {
	// Draws everything a user will see to the screen.
	mWindow.clear();

	mWorld.draw();
	mWindow.draw(SFXText);
	mWindow.draw(scoreText);
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
		//Galaga the_game;
		Application the_game;
		the_game.run();
	}
	catch (std::exception& e) {
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}