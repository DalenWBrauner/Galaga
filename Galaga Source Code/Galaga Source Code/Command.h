#ifndef Command_h
#define Command_h
#include "Category.h"
#include <SFML/System/Time.hpp>
#include <functional>
#include <cassert>

struct Command;

struct Command {
	Command();
	std::function<void(SceneNode& s, sf::Time dt)>	action;
	unsigned int									category;
};

// Templating allows derivedAction(Function) on any given Function for any GameObjectType
template <typename GameObjectType, typename Function>
std::function<void(SceneNode& node, sf::Time dt)> derivedAction(Function fn) {

	// We return "[=]". [=] translates to: a "captured" copy of Function's return value
	return[=](SceneNode& node, sf::Time dt) {

		// Checks if we can cast our node as <GameObjectType>
		assert(dynamic_cast<GameObjectType*>(&node) != nullptr);

		// If we can, then we invoke our Function no problem!
		fn(static_cast<GameObjectType&>(node), dt);
	};
}

/* Command Syntax Example
Command commandStop;
commandStop.action = [] (SceneNode& node, sf::Time dt)
{
node.setVelocity(0.f, 0.f);
};
commandStop.category	= Category::AlliedAircraft
| Category::EnemyAircraft;
*/

#endif