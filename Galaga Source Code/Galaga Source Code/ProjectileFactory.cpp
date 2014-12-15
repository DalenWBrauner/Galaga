#include "ProjectileFactory.h"

ProjectileFactory::ProjectileFactory(TextureHolder *textureHolder) {
	mTextures = textureHolder;
	initSpriteMap();
}

void ProjectileFactory::initSpriteMap(){
	mSpriteMap = std::map<Projectile::Type, int>();

	// Pure Sprite-Types
	mSpriteMap[Projectile::AlliedBullet] = 7;
	mSpriteMap[Projectile::EnemyBullet] = 16;
}

std::unique_ptr<Projectile> ProjectileFactory::newProjectile(Projectile::Type type) {
	/* Instantiates and returns a unique pointer to a new Projectile object */

	// Determines the sprite based on the type
	sf::Sprite sprite;
	sprite.setTexture(mTextures->get(Resource::Texture::Effects));
	sprite.setTextureRect(sf::IntRect(mSpriteMap[type], 1, 8, 8));
	sprite.setScale(sf::Vector2f(2.f, 2.f));
	sprite.setOrigin(8, 8);

	return std::unique_ptr<Projectile>(new Projectile(type, sprite));
}