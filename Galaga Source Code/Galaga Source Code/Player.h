#ifndef Player_h
#define Player_h
#include "CommandQueue.h"
#include "EntityMover.h"
#include <SFML\Window\Event.hpp>

class Player {
public:
	void			handleEvent(const sf::Event& event, CommandQueue& commands);
	void			handleRealTimeInput(CommandQueue& commands);
	// It's really strange this number is so high
	const float		PlayerSpeed = 200.0f;
private:
	bool			pressingLeft = false;
	bool			pressingRight = false;
};

#endif Player_h