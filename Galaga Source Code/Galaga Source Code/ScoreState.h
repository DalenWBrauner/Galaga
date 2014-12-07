#ifndef ScoreState_h
#define ScoreState_h
#include "State.h"
#include "SFML/Graphics/Text.hpp"

class ScoreState : public State {
public:
	ScoreState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);

private:
	sf::Text				mExitText;
	std::vector<sf::Text>	mScores;

	void				loadScores();
};

#endif