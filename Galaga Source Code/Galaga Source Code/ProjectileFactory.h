#ifndef ProjectileFactory_h
#define ProjectileFactory_h
#include "Projectile.h"
#include "ResourceHolder.h"

class ProjectileFactory {
public:
	explicit						ProjectileFactory(TextureHolder *textureHolder);
	std::unique_ptr<Projectile>		newProjectile(Projectile::Type type);

private:
	void							initSpriteMap();

	TextureHolder*					mTextures;
	std::map<Projectile::Type, int>	mSpriteMap;
};

#endif