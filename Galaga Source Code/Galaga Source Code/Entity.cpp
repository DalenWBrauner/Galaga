#include "Entity.h"

Entity::Entity() {
	destroyed = false;
}

/*
Entity::Entity(int startingHitpoints) {
	maxHitpoints = startingHitpoints;
	hitpoints = startingHitpoints; // Not Galaga
	destroyed = false;
}

void Entity::repair(int points) {
	hitpoints += points;
	if (hitpoints > maxHitpoints) { hitpoints = maxHitpoints; }
}

void Entity::damage(int points) {
	hitpoints -= points;
	if (hitpoints < 0) { destroy(); }
}
*/
bool Entity::isDestroyed() const {
	return destroyed;
}

void Entity::destroy() {
	//hitpoints = 0;
	destroyed = true;
}

void Entity::setVelocity(sf::Vector2f velocity) {
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy) {
	mVelocity.x = vx;
	mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const {
	return mVelocity;
}

void Entity::updateCurrent(sf::Time dt, CommandQueue& commands) {
	move(mVelocity * dt.asSeconds());
}

void Entity::accelerate(sf::Vector2f velocity) {
	setVelocity(getVelocity() + velocity);
}

void Entity::accelerate(float vx, float vy) {
	setVelocity(mVelocity.x + vx, mVelocity.y + vy);
}