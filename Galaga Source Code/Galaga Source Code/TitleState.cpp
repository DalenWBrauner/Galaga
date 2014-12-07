#include "TitleState.h"
#include "ResourceHolder.h"
#include "Utility.h"
#include "SFML/Graphics/RenderWindow.hpp"

TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
	, mText()
	, mShowText(true)
	, mTextEffectTime(sf::Time::Zero)
{
	mTitleSprite.setTexture(context.textures->get(Resource::Texture::Title));

	mText.setFont(context.fonts->get(Resource::Font::Galaga));
	mText.setString("PRESS ANY KEY");
	centerOrigin(mText);
	mText.setPosition(context.window->getView().getSize() / 2.f);
}

void TitleState::draw() {
	sf::RenderWindow& window = *getContext().window;
	window.draw(mTitleSprite);

	if (mShowText) { window.draw(mText); }
}

bool TitleState::update(sf::Time dt) {
	mTextEffectTime += dt;

	// Achieves the rapid-blinking effect for mText
	if (mTextEffectTime >= sf::seconds(0.2f)) {
		mShowText = !mShowText;
		mTextEffectTime = sf::Time::Zero;
	}

	return true;
}

bool TitleState::handleEvent(const sf::Event& event) {
	// Check for Any keypress
	if (event.type == sf::Event::KeyPressed) {
		requestStackPop();
		requestStackPush(States::Menu);
	}
	return true;
}