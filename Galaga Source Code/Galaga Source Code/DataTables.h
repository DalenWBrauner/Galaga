#ifndef DataTables_h
#define DataTables_h
#include "ResourceIDs.h"
#include "SFML\System\Time.hpp"
#include "SFML\Graphics\Color.hpp"
#include <vector>
#include <functional>

class Aircraft;

struct Direction {
	Direction(float angle, float distance)
		: angle(angle), distance(distance) {}

	float angle;
	float distance;
};

struct AircraftData {
	// Not SFML
	int								pointValue;
	// Not Galaga
	//int								hitpoints;
	//Resource::Texture				texture;
	sf::Time						fireInterval;
	float							speed;
	std::vector<Direction>			directions;
	
};

/*
struct ProjectileData {
	int								damage;
	float							speed;
	Resource::Texture				texture;
};

struct PickupData {
	std::function<void(Aircraft&)>	action;
	Resource::Texture				texture;
};
*/

std::vector<AircraftData>		initAircraftData();
//std::vector<ProjectileData>		initProjectileData();
//std::vector<PickupData>			initPickupData();

#endif