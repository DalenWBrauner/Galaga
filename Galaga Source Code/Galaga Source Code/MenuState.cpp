#include "MenuState.h"
#include "ResourceHolder.h"
#include "Utility.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/View.hpp"
#include <iostream>

MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context)
	, mOptions()
	, mOptionIndex(0)
{
	//sf::Font& font = context.fonts->get(Resource::Font::Galaga);
	sf::Vector2f viewSize = context.window->getView().getSize();

	mTitleSprite.setTexture(context.textures->get(Resource::Texture::Title));
	centerOrigin(mTitleSprite);
	mTitleSprite.setPosition(sf::Vector2f(
		viewSize.x / 2.f,
		viewSize.y / 2.f - 15.f - viewSize.y*.2f
		));

	float menuItems = 0.f;
	addToMenu(viewSize, "Single Player", menuItems++);
	addToMenu(viewSize, "High Scores", menuItems++);
	addToMenu(viewSize, "Local Multiplayer", menuItems++);
	addToMenu(viewSize, "Online Multiplayer", menuItems++);
	addToMenu(viewSize, "Quit", menuItems++);
	updateOptionText();
}

void MenuState::addToMenu(sf::Vector2f viewSize, std::string text, float row) {
	sf::Text option;
	option.setFont(getContext().fonts->get(Resource::Font::Galaga));
	option.setString(text);
	option.setCharacterSize(20);
	centerOrigin(option);
	option.setPosition(sf::Vector2f(
		viewSize.x / 2.f,
		viewSize.y / 2.f + 5.f + viewSize.y*(row/10.f)
		));
	mOptions.push_back(option);
}

void MenuState::draw() {
	//std::cout << "draw() MenuState" << std::endl;
	sf::RenderWindow& window = *getContext().window;
	window.draw(mTitleSprite);

	for (const sf::Text& text : mOptions) {
		window.draw(text);
	}
}

bool MenuState::update(sf::Time dt) {
	//std::cout << "update() MenuState" << std::endl;
	updateOptionText();
	return true;
}

bool MenuState::handleEvent(const sf::Event& event) {
	std::cout << "handleEvent() MenuState" << std::endl;

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
			//requestStackPush(States::Starry);
			requestStackPush(States::Scoreboard);
		}
		else if (mOptionIndex == LocalMultiplayer) {}
		else if (mOptionIndex == OnlineMultiplayer) {}
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