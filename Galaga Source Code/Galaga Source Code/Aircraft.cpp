#include "Aircraft.h"

Aircraft::Aircraft(EnemyType enemyType,
	std::shared_ptr<sf::Texture> mTexture,
	std::shared_ptr<std::map<EnemyType, int>> spriteMap
	) {
	mEnemyType = enemyType;
	mSprite.setTexture(*mTexture);
	mSprite.setTextureRect(sf::IntRect(120, (*spriteMap)[mEnemyType], 16, 16));
	mSprite.setScale(sf::Vector2f(2.f, 2.f));
	mSprite.setOrigin(8, 8);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	//std::cout << "Aircraft.drawCurrent()\tX: " << this->getPosition().x << "\tY: " << this->getPosition().y << std::endl;
	target.draw(mSprite, states);
	
}