#include "Aircraft.h"

Aircraft::Aircraft(EnemyType enemyType,
	std::shared_ptr<sf::Texture> mTexture,
	std::shared_ptr<std::map<EnemyType, int>> spriteMap
	) {

	mSprite.setTexture(*mTexture);
	mSprite.setTextureRect(sf::IntRect( (*spriteMap)[enemyType], 1, 16, 16));
	mSprite.setScale(sf::Vector2f(2.f, 2.f));
	mSprite.setOrigin(8, 8);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);
}