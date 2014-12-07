#ifndef EntityMover_h
#define EntityMover_h
#include "Entity.h"

class EntityMover {
private:
	sf::Vector2f velocity;
public:
	EntityMover(float vx, float vy) : velocity(vx, vy) {}
	void operator() (Entity& entity, sf::Time dt) const {
		entity.accelerate(velocity);
	}
};

// The forceful brother to EntityMover
class EntityDragger {
private:
	sf::Vector2f velocity;
public:
	EntityDragger(float vx, float vy) : velocity(vx, vy) {}
	void operator() (Entity& entity, sf::Time dt) const {
		entity.setVelocity(velocity);
	}
};

/* Syntax for EntityMover:
Command moveLeft;
moveLeft.category = Category::PlayerAircraft;
moveLeft.action = derivedAction<Entity>(
EntityMover(-playerSpeed, 0.f) );

Looks like those fancy enemy ship maneuvers won't be so difficult after all!
*/

#endif