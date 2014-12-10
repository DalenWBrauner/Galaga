#include "GameState.h"
#include <iostream>

GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(*context.window)
	, mPlayer(*context.player)
{
	// These really belong in the world, not here
	yourScore = 0;
	highScore = 1337;	//Temporary

	scoreText.setFont(context.fonts->get(Resource::Font::Galaga));
	scoreText.setCharacterSize(15);
	scoreText.setColor(sf::Color::Red);
	scoreText.setPosition(400, 50);
	scoreText.setString("High\n Score\n\n\n\n1UP\n");

	scoreDisplay.setFont(context.fonts->get(Resource::Font::Galaga));
	scoreDisplay.setCharacterSize(15);
	scoreDisplay.setColor(sf::Color::White);
	scoreDisplay.setPosition(scoreText.getPosition());
	scoreDisplay.setString("\n\n" + std::to_string(highScore) + "\n\n\n\n" + std::to_string(yourScore));
}

void GameState::draw() {
	//std::cout << "draw() GameState" << std::endl;
	sf::RenderWindow& window = *getContext().window;

	mWorld.draw();
	window.draw(scoreText);
	window.draw(scoreDisplay);
}

bool GameState::update(sf::Time dt) {
	//std::cout << "update() GameState" << std::endl;
	mWorld.update(dt);

	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleRealTimeInput(commands);

	// Keeping Score
	scoreDisplay.setString("\n\n" + std::to_string(highScore) + "\n\n\n\n" + std::to_string(yourScore));

	return true;
}

bool GameState::handleEvent(const sf::Event& event) {
	//std::cout << "handleEvent() GameState" << std::endl;
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleEvent(event, commands);

	// Pause Functionality
	if (event.type == sf::Event::LostFocus) {
		requestStackPush(States::Pause);
	}
	else if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape) {
			requestStackPush(States::Pause);
		}
		if (event.key.code == sf::Keyboard::Up) {
			yourScore += 200;
			if (yourScore > highScore)
				highScore = yourScore;
		}
		if (event.key.code == sf::Keyboard::Down) {
			yourScore -= 200;
		}
	}
	return true;
}