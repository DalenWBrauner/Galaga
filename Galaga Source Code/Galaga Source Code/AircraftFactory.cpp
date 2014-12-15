#include "AircraftFactory.h"

AircraftFactory::AircraftFactory(TextureHolder *textureHolder)
	: mTextures(textureHolder)
	, mProjectileFactory(textureHolder)
{
	initSpriteMap();
}

void AircraftFactory::initSpriteMap(){
	mSpriteMap = std::map<Aircraft::ShipType, int>();

	// Pure Sprite-Types
	mSpriteMap[Aircraft::WhiteShip]	  = 1;
	mSpriteMap[Aircraft::RedShip]	  = 18;
	mSpriteMap[Aircraft::DawnOwl]	  = 35;
	mSpriteMap[Aircraft::DuskOwl]	  = 52;
	mSpriteMap[Aircraft::Butterfly]   = 69;
	mSpriteMap[Aircraft::Wasp]		  = 86;
	mSpriteMap[Aircraft::Pudding]	  = 103;
	mSpriteMap[Aircraft::Scorpion]	  = 120;
	mSpriteMap[Aircraft::Greenie]	  = 137;
	mSpriteMap[Aircraft::Dragonfly]   = 154;
	mSpriteMap[Aircraft::Enterprise]  = 171;
	mSpriteMap[Aircraft::Petalcopter] = 188;
	// Additional Types
	mSpriteMap[Aircraft::PlayerShip] = mSpriteMap[Aircraft::WhiteShip];
}

std::unique_ptr<Aircraft> AircraftFactory::newAircraft(Aircraft::ShipType shipType) {
	/* Instantiates and returns a unique pointer to a new Aircraft object */

	// Determines the sprite based on the shiptype
	sf::Sprite sprite;
	sprite.setTexture(mTextures->get(Resource::Texture::Ships));
	sprite.setTextureRect(sf::IntRect(
		103,						// Column 7
		mSpriteMap[shipType],		// Row [shipType]
		16,							// Sprite Width of 16px
		16							// Sprite Height of 16px
		));
	sprite.setScale(sf::Vector2f(2.f, 2.f));
	sprite.setOrigin(8, 8);

	return std::unique_ptr<Aircraft>(new Aircraft(shipType, sprite, mProjectileFactory));
}