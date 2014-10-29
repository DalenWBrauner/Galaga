#ifndef Player_h
#define Player_h
#include "Aircraft.h"
#include "CommandQueue.h"
#include "EntityMover.h"

class Player {
public:
	void			handleEvent(const sf::Event& event, CommandQueue& commands);
	void			handleRealTimeInput(CommandQueue& commands);
};

#endif Player_h