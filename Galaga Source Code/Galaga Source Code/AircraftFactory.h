#ifndef AircraftFactory_h
#define AircraftFactory_h
#include "Aircraft.h"
#include "ResourceHolder.h"
#include "ProjectileFactory.h"

class AircraftFactory {
public:
	explicit						AircraftFactory(TextureHolder *textureHolder);
	std::unique_ptr<Aircraft>		newAircraft(Aircraft::ShipType shipType);

private:
	void								initSpriteMap();

	TextureHolder*						mTextures;
	std::map<Aircraft::ShipType, int>	mSpriteMap;
	ProjectileFactory					mProjectileFactory;
};

#endif