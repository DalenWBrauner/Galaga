#ifndef TitleState_h
#define TitleState_h
#include "State.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

class TitleState : public State {
public:
	TitleState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);

private:
	sf::Sprite			mTitleSprite;
	sf::Text			mText;

	bool				mShowText;
	sf::Time			mTextEffectTime;
};

#endif