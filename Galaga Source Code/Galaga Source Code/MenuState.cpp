#include "MenuState.h"
#include "ResourceHolder.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/View.hpp"

MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context)
	, mOptions()
	, mOptionIndex(0)
{
	mTitleSprite.setTexture(context.textures->get(Resource::Texture::Title));

	sf::Font& font = context.fonts->get(Resource::Font::Galaga);

	// Crude Menu Implementation
	sf::Text optSinglePlayer;
	optSinglePlayer.setFont(font);
	optSinglePlayer.setString("Single Player");
	optSinglePlayer.setPosition(context.window->getView().getSize() / 2.f);
	mOptions.push_back(optSinglePlayer);

	sf::Text optScore;
	optScore.setFont(font);
	optScore.setString("High Scores");
	optSinglePlayer.setPosition(optSinglePlayer.getPosition() + sf::Vector2f(0.f, 30.f));
	mOptions.push_back(optScore);

	sf::Text optQuit;
	optQuit.setFont(font);
	optQuit.setString("Quit");
	optSinglePlayer.setPosition(optScore.getPosition() + sf::Vector2f(0.f, 30.f));
	mOptions.push_back(optQuit);

	updateOptionText();
}

void MenuState::draw() {
	sf::RenderWindow& window = *getContext().window;
	window.draw(mTitleSprite);

	for (const sf::Text& text : mOptions) {
		window.draw(text);
	}
}

bool MenuState::update(sf::Time dt) {
	return true;
}

bool MenuState::handleEvent(const sf::Event& event) {

	if (event.type != sf::Event::KeyPressed) {
		return false;
	}

	if (event.key.code == sf::Keyboard::Return) {
		if (mOptionIndex == Quit) {
			requestStackPop();		// Closes the game by emptying the stack
			//requestStackPop();	// Need to clear out the Starry state
		}
		else if (mOptionIndex == SinglePlayer) {
			requestStackPop();
			requestStackPush(States::Game);
		}
		else if (mOptionIndex == ScoreBoard) {
			requestStackPush(States::Starry);
			requestStackPush(States::Scoreboard);
		}
		/*
		else if (mOptionIndex == LocalMultiplayer) {}
		else if (mOptionIndex == OnlineMultiplayer) {}
		*/
	}
	else if (event.key.code == sf::Keyboard::Up) {
		// Decrement
		if (mOptionIndex > 0)					
			mOptionIndex--;
		// Wrap-around
		else
			mOptionIndex = mOptions.size() - 1;
	}
	else if (event.key.code == sf::Keyboard::Down) {
		// Increment
		if (mOptionIndex < mOptions.size() - 1)
			mOptionIndex++;
		// Wrap-Around
		else
			mOptionIndex = 0;
	}
	return true;
}

void MenuState::updateOptionText() {
	if (mOptions.empty()) {
		return;
	}

	// Set the text colors to white
	for (sf::Text& text : mOptions) {
		text.setColor(sf::Color::White);
	}

	// Set the selected color to red
	mOptions[mOptionIndex].setColor(sf::Color::Red);
}