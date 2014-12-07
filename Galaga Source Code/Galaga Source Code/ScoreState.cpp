#include "ScoreState.h"
#include "ResourceHolder.h"
#include "SFML/Graphics/RenderWindow.hpp"

ScoreState::ScoreState(StateStack& stack, Context context)
	: State(stack, context)
	, mExitText()
	, mScores()
{
	mExitText.setFont(context.fonts->get(Resource::Font::Galaga));
	mExitText.setString("(Press any key to return to the Main Menu)");
	//centerOrigin(mExitText);
	mExitText.setPosition(context.window->getView().getSize() / 2.f);

	loadScores();
}

void ScoreState::draw() {
	sf::RenderWindow& window = *getContext().window;

	for (const sf::Text& text : mScores) {
		window.draw(text);
	}

	window.draw(mExitText);
}

bool ScoreState::update(sf::Time dt) {
	return true;
}

bool ScoreState::handleEvent(const sf::Event& event) {
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