#ifndef Aircraft_h
#define Aircraft_h
#include "Entity.h"
#include "ResourceHolder.h"
#include <memory>
#include <map>

class Aircraft : public Entity {
public:
	enum			ShipType {
//		EnemyName	 // Line # on Sprite Sheet
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
	};
	explicit		Aircraft(
		ShipType shipType,
		TextureHolder *mTextures,
		std::shared_ptr<std::map<ShipType, int>> spriteMap,
		bool isPlayer=false
		);
	virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	ShipType			mShipType;
	sf::Sprite			mSprite;
};

#endif