
#include "DataTables.h"
#include "Aircraft.h"
#include "Projectile.h"
//#include "Pickup.h"

using namespace std::placeholders;

std::vector<AircraftData> initAircraftData() {
	std::vector<AircraftData> data(Aircraft::TypeCount);

	data[Aircraft::WhiteShip].speed = 200.f;
	data[Aircraft::RedShip].speed = 300.f;
	data[Aircraft::RedShip].directions.push_back(Direction(+45.f, 10.f));
	data[Aircraft::RedShip].directions.push_back(Direction(-45.f, 20.f));
	data[Aircraft::RedShip].directions.push_back(Direction(+45.f, 20.f));
	data[Aircraft::RedShip].directions.push_back(Direction(-45.f, 20.f));
	data[Aircraft::RedShip].directions.push_back(Direction(+45.f, 10.f));

	data[Aircraft::DawnOwl] =	data[Aircraft::WhiteShip];
	data[Aircraft::DuskOwl] =	data[Aircraft::RedShip];
	data[Aircraft::Butterfly] = data[Aircraft::WhiteShip];
	data[Aircraft::Dragonfly] = data[Aircraft::RedShip];
	data[Aircraft::Pudding] =	data[Aircraft::WhiteShip];
	data[Aircraft::Greenie] =	data[Aircraft::RedShip];
	data[Aircraft::Scorpion] =	data[Aircraft::WhiteShip];
	data[Aircraft::Wasp] =		data[Aircraft::RedShip];
	data[Aircraft::Petalcopter]=data[Aircraft::WhiteShip];
	data[Aircraft::Enterprise] =data[Aircraft::RedShip];

	return data;
}