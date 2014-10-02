#include "Aircraft.h"

Aircraft::Aircraft(EnemyType enemyType,
	std::shared_ptr<sf::Texture> mTexture,
	std::shared_ptr<std::map<EnemyType, int>> spriteMap
	) {

	mEnemyType = enemyType;

	mSprite.setTexture(*mTexture);
	mSprite.setTextureRect(sf::IntRect( (*spriteMap)[mEnemyType], 1, 16, 16));
	mSprite.setScale(sf::Vector2f(2.f, 2.f));
	mSprite.setOrigin(8, 8);
//	std::cout << "I AM " << mEnemyType << std::endl;
//	std::cout << "MY PIXEL ROW IS AT " << (*spriteMap)[mEnemyType] << std::endl;
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	std::cout << "Aircraft.drawCurrent()\tX: " << this->getPosition().x << "\tY: " << this->getPosition().y << std::endl;
	target.draw(mSprite, states);
	
}
