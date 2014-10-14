#include "Aircraft.h"

Aircraft::Aircraft(ShipType shipType,
	std::shared_ptr<sf::Texture> mTexture,
	std::shared_ptr<std::map<ShipType, int>> spriteMap,
	bool isPlayer
	) {
	mShipType = shipType;
	mSprite.setTexture(*mTexture);
	mSprite.setTextureRect(sf::IntRect(120, (*spriteMap)[mShipType], 16, 16));
	mSprite.setScale(sf::Vector2f(2.f, 2.f));
	mSprite.setOrigin(8, 8);
	if (!isPlayer) {
		mCategory = Category::Type::EnemyAircraft;
	}
	else {
		mCategory = Category::Type::PlayerAircraft;
	}
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	//std::cout << "Aircraft.drawCurrent()\tX: " << this->getPosition().x << "\tY: " << this->getPosition().y << std::endl;
	target.draw(mSprite, states);
}