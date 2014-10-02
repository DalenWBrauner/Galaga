#include "Entity.h"

void Entity::setVelocity(sf::Vector2f velocity) {
	//std::cout << "Entity.setVelocity( {" << velocity.x << ", " << velocity.y << "} )" << std::endl;
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy) {
	//std::cout << "Entity.setVelocity(" << vx << ", " << vy << ")" << std::endl;
	mVelocity.x = vx;
	mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const {
	//std::cout << "Entity.getVelocity()" << std::endl;
	return mVelocity;
}

void Entity::updateCurrent(sf::Time dt) {
	//std::cout << "Entity.updateCurrent(" << dt.asSeconds() << ")" << std::endl;
	move(mVelocity * dt.asSeconds());
}