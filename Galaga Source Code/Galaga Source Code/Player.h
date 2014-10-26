#ifndef Player_h
#define Player_h
#include "Aircraft.h"
#include "Command.h"
#include "CommandQueue.h"
#include <map>
#include <string>
#include <algorithm>

class Player;

class Player {
public:
	void			handleEvent(const sf::Event& event, CommandQueue& commands);
	void			handleRealTimeInput(CommandQueue& commands);
};

#endif Player_h