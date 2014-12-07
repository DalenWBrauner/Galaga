#ifndef StarryState_h
#define StarryState_h
#include "State.h"
#include "SFML/Graphics/Sprite.hpp"
#include <vector>

class StarryState : public State {
public:
	StarryState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);

private:
	std::vector<sf::Sprite>			mStars;

	void				insertStarsRandomly();
};

#endif