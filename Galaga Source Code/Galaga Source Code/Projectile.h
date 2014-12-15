#ifndef Projectile_h
#define Projectile_h
#include "Entity.h"
#include "ResourceIDs.h"
#include "SFML\Graphics\Sprite.hpp"

class CommandQueue;

class Projectile : public Entity {
public:
	// There will only be allied and enemy bullets, so I may simplify this
	enum Type {
		AlliedBullet,
		EnemyBullet,
		//Missile,
		TypeCount,
	};

	Projectile(Type type, sf::Sprite sprite);
	//Projectile(Type type, const TextureHolder& textures);
	//void					guideTowards(sf::Vector2f position);
	//bool					isGuided() const;

	virtual unsigned int	getCategory() const;
	virtual sf::FloatRect	getBoundingRect() const;
	float					getMaxSpeed() const;
	//int						getDamage() const;

private:
	virtual void			updateCurrent(sf::Time dt, CommandQueue& commands);
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	Type					mType;
	sf::Sprite				mSprite;
	sf::Vector2f			mTargetDirection;
};

#endif