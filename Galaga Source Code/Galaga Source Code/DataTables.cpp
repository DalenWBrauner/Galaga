
#include "DataTables.h"
#include "Aircraft.h"
#include "Projectile.h"
//#include "Pickup.h"

using namespace std::placeholders;

std::vector<AircraftData> initAircraftData() {
	std::vector<AircraftData> data(Aircraft::TypeCount);

	data[Aircraft::WhiteShip].fireInterval = sf::seconds(1);
	data[Aircraft::WhiteShip].speed = 250.f;
	data[Aircraft::WhiteShip].directions.push_back(Direction(0.f, 10.f));
	data[Aircraft::WhiteShip].directions.push_back(Direction(30.f, 10.f));
	data[Aircraft::WhiteShip].directions.push_back(Direction(60.f, 10.f));
	data[Aircraft::WhiteShip].directions.push_back(Direction(90.f, 10.f));
	data[Aircraft::WhiteShip].directions.push_back(Direction(120.f, 10.f));
	data[Aircraft::WhiteShip].directions.push_back(Direction(150.f, 10.f));
	data[Aircraft::WhiteShip].directions.push_back(Direction(180.f, 10.f));
	data[Aircraft::WhiteShip].directions.push_back(Direction(210.f, 10.f));
	data[Aircraft::WhiteShip].directions.push_back(Direction(240.f, 10.f));
	data[Aircraft::WhiteShip].directions.push_back(Direction(270.f, 10.f));
	data[Aircraft::WhiteShip].directions.push_back(Direction(300.f, 10.f));
	data[Aircraft::WhiteShip].directions.push_back(Direction(330.f, 10.f));

	data[Aircraft::WhiteShip].fireInterval = sf::seconds(1);
	data[Aircraft::RedShip].speed = 25.f;
	data[Aircraft::RedShip].directions.push_back(Direction(+45.f, 25.f));
	data[Aircraft::RedShip].directions.push_back(Direction(-45.f, 50.f));
	data[Aircraft::RedShip].directions.push_back(Direction(+45.f, 50.f));
	data[Aircraft::RedShip].directions.push_back(Direction(-45.f, 50.f));
	data[Aircraft::RedShip].directions.push_back(Direction(+45.f, 25.f));

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