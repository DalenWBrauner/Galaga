#ifndef MenuState_h
#define MenuState_h
#include "State.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include <vector>

class MenuState : public State {
public:
	MenuState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);

	void				updateOptionText();

private:
	sf::Sprite			mTitleSprite;
	enum OptionNames {
		SinglePlayer,
		ScoreBoard,
//		LocalMultiplayer,
//		OnlineMultiplayer,
		Quit,
	};
	std::vector<sf::Text>	mOptions;
	std::size_t				mOptionIndex;
};

#endif