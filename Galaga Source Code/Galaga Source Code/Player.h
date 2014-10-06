#ifndef Player_h
#define Player_h
//#include "Galaga.h"
#include "Aircraft.h"

class Player;

class Player {
public:
	void			handleEvent(const sf::Event& event, CommandQueue& commands);
	void			handleRealTimeInput(CommandQueue& commands);
};

#endif Player_h