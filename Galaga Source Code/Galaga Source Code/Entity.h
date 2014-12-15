#ifndef Entity_h
#define Entity_h
#include "SceneNode.h"

class CommandQueue;

class Entity : public SceneNode {
public:
	//explicit		Entity(int startingHitpoints);
	explicit		Entity();
	//void			repair(int points);
	//void			damage(int points);
	void			destroy();
	bool			isDestroyed() const;

	void			setVelocity(sf::Vector2f velocity);
	void			setVelocity(float vx, float vy);
	sf::Vector2f	getVelocity() const;
	void			accelerate(sf::Vector2f velocity);
	void			accelerate(float vx, float vy);

private:
	//int				maxHitpoints;
	//int				hitpoints;
	bool			destroyed;
	sf::Vector2f	mVelocity;

protected:
	virtual void	updateCurrent(sf::Time dt, CommandQueue& commands);
};

#endif