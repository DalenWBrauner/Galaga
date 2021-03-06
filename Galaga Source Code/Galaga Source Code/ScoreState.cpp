#include "ScoreState.h"
#include "ResourceHolder.h"
#include "Utility.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include <iostream>

ScoreState::ScoreState(StateStack& stack, Context context)
	: State(stack, context)
	, mExitText()
	, mScores()
{
	sf::Vector2f viewSize = context.window->getView().getSize();
	mExitText.setFont(context.fonts->get(Resource::Font::Galaga));
	mExitText.setString("(Press any key\nto return to the Main Menu)");
	mExitText.setCharacterSize(15);
	centerOrigin(mExitText);
	mExitText.setPosition(sf::Vector2f(
		viewSize.x / 2.f,
		viewSize.y / 2.f + viewSize.y*.4f
		));
	mExitText.setColor(sf::Color::Red);

	loadScores();
}

void ScoreState::draw() {
	//std::cout << "draw() ScoreState" << std::endl;
	sf::RenderWindow& window = *getContext().window;

	for (const sf::Text& text : mScores) {
		window.draw(text);
	}

	window.draw(mExitText);
}

bool ScoreState::update(sf::Time dt) {
	//std::cout << "update() ScoreState" << std::endl;
	return true;
}

bool ScoreState::handleEvent(const sf::Event& event) {
	//std::cout << "handleEvent() ScoreState" << std::endl;

	// Check for any keypress
	if (event.type == sf::Event::KeyPressed) {
		requestStackPop();
		requestStackPop();	// Need to pop StarryState
	}
	return true;
}

void ScoreState::loadScores() {
	sf::Font& font = getContext().fonts->get(Resource::Font::Galaga);
	// Load scores
}