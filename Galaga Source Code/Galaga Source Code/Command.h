#ifndef Command_h
#define Command_h
#include "Category.h"
#include <SFML/System.hpp>
#include <iostream>
#include <functional>

class SceneNode;

struct Command {
	Command();
	std::function<void(SceneNode& s, sf::Time dt)>	action;
	unsigned int									category;
};
// Command Syntax Example
/* 
Command commandStop;
commandStop.action = [] (SceneNode& node, sf::Time dt) {
	node.setVelocity(0.f, 0.f);
};
commandStop.category	= Category::AlliedAircraft | Category::EnemyAircraft;
*/
#endif