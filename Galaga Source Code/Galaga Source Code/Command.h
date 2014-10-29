#ifndef Command_h
#define Command_h
#include <SFML/System.hpp>
#include <iostream>
#include <functional>

namespace Category {
	enum Type {
		None = 0,
		Scene = 1 << 0,
		PlayerAircraft = 1 << 1,
		EnemyAircraft = 1 << 2,
		Collectable = 1 << 3,
	};
}

class SceneNode;

struct Command {
	Command();
	std::function<void(SceneNode& s, sf::Time dt)>	action;
	unsigned int									category;
};

/* Command Syntax Example

Command commandStop;
commandStop.action = [] (SceneNode& node, sf::Time dt) {
	node.setVelocity(0.f, 0.f);
};
commandStop.category	= Category::AlliedAircraft | Category::EnemyAircraft;

*/

#endif