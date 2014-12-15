#ifndef Aircraft_h
#define Aircraft_h
#include "Entity.h"
#include "Command.h"
#include "ResourceIDs.h"
#include "ProjectileFactory.h"
#include "TextNode.h"
#include "ResourceHolder.h"
#include "SFML\Graphics\Sprite.hpp"
#include <memory>
#include <map>

class Aircraft : public Entity {
public:
	// ShipType determines behavior.
	enum					ShipType {
		// ShipTypes with unique behaviors.
		PlayerShip,
		// Standard enemy ships; described based upon appearance.
		WhiteShip,	 // Line 1
		RedShip,	 // Line 2
		DawnOwl,	 // Line 3
		DuskOwl,	 // Line 4
		Butterfly,	 // Line 5
		Wasp,		 // Line 6
		Pudding,	 // Line 7
		Scorpion,	 // Line 8
		Greenie,	 // Line 9
		Dragonfly,	 // Line 10
		Enterprise,	 // Line 11
		Petalcopter, // Line 12
		// So we have the length of our enum
		TypeCount,
	};
	explicit				Aircraft(ShipType shipType, sf::Sprite sprite, ProjectileFactory& projectileFactory);
	virtual unsigned int	getCategory() const;
	virtual sf::FloatRect	getBoundingRect() const;
	bool					isAllied() const;
	bool					isMarkedForRemoval() const;
	float					getMaxSpeed() const;

	//void					increaseFireRate();
	//void					increaseSpread();
	//void					collectMissiles(unsigned int count);

	void					fire();
	//void					launchMissile();

private:
	virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void	updateCurrent(sf::Time dt, CommandQueue& commands);
	void			updateMovementPattern(sf::Time dt);
	//void			checkPickupDrop(CommandQueue& commands);
	void			checkProjectileLaunch(sf::Time dt, CommandQueue& commands);

	//void			createBullets(SceneNode& node, const TextureHolder& textures) const;
	void			createProjectile(SceneNode& node, ProjectileFactory& projectileFactory) const;
	//void			createPickup(SceneNode& node, const TextureHolder& textures) const;

	//void			updateTexts();

	ShipType			mShipType;
	sf::Sprite			mSprite;
	Command				mFireCommand;
	//Command				mMissileCommand;
	//sf::Time			mFireCountdown;
	bool				mIsFiring;
	//bool				mIsLaunchingMissile;
	bool				mIsMarkedForRemoval;

	//int					mFireRateLevel;
	//int					mSpreadLevel;
	//int					mMissileAmmo;
	int					mPointValue; // Galaga Addition

	//Command				mDropPickupCommand;
	float				mTravelledDistance;
	std::size_t			mDirectionIndex;
	//TextNode*			mHealthDisplay;
	//TextNode*			mMissileDisplay;

	// NOTE: I need to build-in a Projectile Factory
	// possibly one static for all aircraft?
};

#endif