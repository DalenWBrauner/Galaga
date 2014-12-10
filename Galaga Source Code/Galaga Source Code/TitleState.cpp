#include "TitleState.h"
#include "ResourceHolder.h"
#include "Utility.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include <iostream>

TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
	, mText()
	, mShowText(true)
	, mTextEffectTime(sf::Time::Zero)
{
	sf::Vector2f viewSize = context.window->getView().getSize();

	mTitleSprite.setTexture(context.textures->get(Resource::Texture::Title));
	centerOrigin(mTitleSprite);
	mTitleSprite.setPosition(sf::Vector2f(
		viewSize.x/2.f,
		viewSize.y/2.f - 15.f - viewSize.y*.2f
		));

	mText.setFont(context.fonts->get(Resource::Font::Galaga));
	mText.setString("PRESS ANY KEY");
	centerOrigin(mText);
	mText.setPosition(sf::Vector2f(
		viewSize.x / 2.f,
		viewSize.y / 2.f + 1.f + viewSize.y*.25f
		));
}

void TitleState::draw() {
	//std::cout << "draw() TitleState" << std::endl;
	sf::RenderWindow& window = *getContext().window;
	window.draw(mTitleSprite);

	if (mShowText) { window.draw(mText); }
}

bool TitleState::update(sf::Time dt) {
	//std::cout << "update() TitleState" << std::endl;

	mTextEffectTime += dt;

	// Achieves the rapid-blinking effect for mText
	if (mTextEffectTime >= sf::seconds(0.9f)) {
		mShowText = !mShowText;
		mTextEffectTime = sf::Time::Zero;
	}

	return true;
}

bool TitleState::handleEvent(const sf::Event& event) {
	//std::cout << "handleEvent() TitleState" << std::endl;
	// Check for Any keypress
	if (event.type == sf::Event::KeyPressed) {
		requestStackPop();
		requestStackPush(States::Menu);
	}
	return true;
}