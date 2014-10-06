#ifndef Entity_h
#define Entity_h
#include "SceneNode.h"

class Entity;
struct EntityMover;

class Entity : public SceneNode {
public:
	void			setVelocity(sf::Vector2f velocity);
	void			setVelocity(float vx, float vy);
	sf::Vector2f	getVelocity() const;
	void			accelerate(sf::Vector2f velocity);
	void			accelerate(float vx, float vy);

private:
	sf::Vector2f	mVelocity;
	virtual void	updateCurrent(sf::Time dt);
};

struct EntityMover {
	EntityMover(float vx, float vy) : velocity(vx, vy) {}
	sf::Vector2f velocity;
	void operator() (Entity& entity, sf::Time) const {
		entity.accelerate(velocity);
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