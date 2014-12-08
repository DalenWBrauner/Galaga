#include "PauseState.h"
#include "ResourceHolder.h"
#include "Utility.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/View.hpp"
#include <iostream>

PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context)
	, mPausedText()
	, mInstructionText()
{
	sf::Font& font = context.fonts->get(Resource::Font::Galaga);
	sf::Vector2f viewSize = (context.window->getView()).getSize();

	mPausedText.setFont(font);
	mPausedText.setString("PAUSED");
	mPausedText.setCharacterSize(32);
	centerOrigin(mPausedText);
	mPausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

	mInstructionText.setFont(font);
	mInstructionText.setString("ESC\t\t\t-> Resume Game\nBackspace\t-> Return to Main Menu");
	mInstructionText.setCharacterSize(12);
	centerOrigin(mInstructionText);
	mInstructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

void PauseState::draw() {
	//std::cout << "draw() PauseState" << std::endl;
	sf::RenderWindow& window = *getContext().window;
	
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 255, 0, 100));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mPausedText);
	window.draw(mInstructionText);
}

bool PauseState::update(sf::Time) {
	//std::cout << "update() PauseState" << std::endl;
	return false;
}

bool PauseState::handleEvent(const sf::Event& event) {
	//std::cout << "handleEvent() PauseState";
	if (event.type != sf::Event::KeyPressed) {
		//std::cout << ":\t Not a keypress" << std::endl;
		return false;
	}

	if (event.key.code == sf::Keyboard::Escape) {
		//std::cout << ":\t Pressed Escape!" << std::endl;;
		requestStackPop();
	}
	if (event.key.code == sf::Keyboard::BackSpace) {
		//std::cout << ":\t Pressed Backspace!" << std::endl;;
		requestStackClear();
		//requestStackPush(States::Starry);
		requestStackPush(States::Menu);
	}
	return false;
}