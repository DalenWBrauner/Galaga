#ifndef GameState_h
#define GameState_h

#include "State.h"
#include "World.h"
#include "Player.h"

class GameState : public State {
public:
	GameState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);

private:
	World				mWorld;
	Player&				mPlayer;
	int yourScore;
	int highScore;
	sf::Text SFXText;
	sf::Text scoreText;
	sf::Text scoreDisplay;
};

#endif