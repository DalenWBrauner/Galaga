#include "PauseState.h"
#include "ResourceHolder.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/View.hpp"

PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context)
	, mPausedText()
	, mInstructionText()
{
	sf::Font& font = context.fonts->get(Resource::Font::Galaga);
	sf::Vector2f viewSize = (context.window->getView()).getSize();

	mPausedText.setFont(font);
	mPausedText.setString("PAUSED");
	mPausedText.setCharacterSize(64);
	//centerOrigin(mPausedText);
	mPausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

	mInstructionText.setFont(font);
	mInstructionText.setString("Press Backspace to return to Main Menu");
	//centerOrigin(mInstructionText);
	mInstructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

void PauseState::draw() {
	sf::RenderWindow& window = *getContext().window;
	
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 255, 0, 100));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mPausedText);
	window.draw(mInstructionText);
}

bool PauseState::update(sf::Time) { return false; }

bool PauseState::handleEvent(const sf::Event& event) {
	if (event.key.code == sf::Keyboard::Escape) {
		requestStackPop();
	}
	else if (event.key.code == sf::Keyboard::BackSpace) {
		requestStackClear();
		requestStackPush(States::Starry);
		requestStackPush(States::Menu);
	}
	return false;
}