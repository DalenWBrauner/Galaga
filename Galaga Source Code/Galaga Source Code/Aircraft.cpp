#include "Aircraft.h"


Aircraft::Aircraft(ShipType shipType, sf::Sprite sprite) {
	mShipType = shipType;
	mSprite = sprite;
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	//std::cout << "Aircraft.drawCurrent()\tX: " << this->getPosition().x << "\tY: " << this->getPosition().y << std::endl;
	target.draw(mSprite, states);
}