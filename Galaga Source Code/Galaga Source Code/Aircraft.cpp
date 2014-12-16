#include "Aircraft.h"
#include "CommandQueue.h"
#include "DataTables.h"
#include "Utility.h"
#include <iostream>

namespace
{
	const std::vector<AircraftData> Table = initAircraftData();
}

Aircraft::Aircraft(ShipType shipType, sf::Sprite sprite, ProjectileFactory& projectileFactory)
	: Entity()
	, mShipType(shipType)
	, mSprite(sprite)
	, mFireCommand()
	//, mMissileCommand()
	, mFireCountdown(sf::Time::Zero)
	, mIsFiring(false)
	//, mIsLaunchingMissile(false)
	, mIsMarkedForRemoval(false)
	, mFireRateLevel(1)
	//, mSpreadLevel(1)
	//, mMissileAmmo(2)
	//, mDropPickupCommand()
	, mTravelledDistance(0.f)
	, mDirectionIndex(0)
	//, mHealthDisplay(nullptr)
	//, mMissileDisplay(nullptr)
{
	if (mShipType == Aircraft::PlayerShip)	{ mDefaultCategory = Category::PlayerAircraft; }
	else									{ mDefaultCategory = Category::EnemyAircraft; }

	centerOrigin(mSprite);

	mFireCommand.category = Category::Scene;
	mFireCommand.action = [this, &projectileFactory](SceneNode& node, sf::Time){
		//createBullets(node, textures);
		createProjectile(node, projectileFactory);
	};

	// This should simplify the constructor a bit
	/*
	mMissileCommand.category = Category::SceneAirLayer;
	mMissileCommand.action = [this, &textures](SceneNode& node, sf::Time) {
		createProjectile(node, Projectile::Missile, 0.f, 0.5f, textures);
	};
	mDropPickupCommand.category = Category::SceneAirLayer;
	mDropPickupCommand.action = [this, &textures](SceneNode& node, sf::Time) {
		createPickup(node, textures);
	};

	std::unique_ptr<TextNode> healthDisplay(new TextNode(fonts, ""));
	mHealthDisplay = healthDisplay.get();
	attachChild(std::move(healthDisplay));

	if (getCategory() == Category::PlayerAircraft) {
		std::unique_ptr<TextNode> missileDisplay(new TextNode(fonts, ""));
		missileDisplay->setPosition(0, 70);
		mMissileDisplay = missileDisplay.get();
		attachChild(std::move(missileDisplay));
	}
	updateTexts();
	*/
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);
}

void Aircraft::updateCurrent(sf::Time dt, CommandQueue& commands) {
	//std::cout << "updating current aircraft..." << std::endl;

	//Entity has been destroyed; Possibly drop pickup, mark for removal
	if (isDestroyed()) {
		//checkPickupDrop(commands);
		mIsMarkedForRemoval = true;
		return;
	}

	// Check if bullets or missiles are fired
	checkProjectileLaunch(dt, commands);

	// Update enemy movement pattern; apply velocity
	updateMovementPattern(dt);
	Entity::updateCurrent(dt, commands);

	//updateTexts();
}

unsigned int Aircraft::getCategory() const {
	if (isAllied()) {
		return Category::PlayerAircraft;
	}
	else {
		return Category::EnemyAircraft;
	}
}

sf::FloatRect Aircraft::getBoundingRect() const {
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

bool Aircraft::isAllied() const {
	return mShipType == PlayerShip;
}

bool Aircraft::isMarkedForRemoval() const{
	return mIsMarkedForRemoval;
}

float Aircraft::getMaxSpeed() const {
	return Table[mShipType].speed;
}

/*
void Aircraft::increaseFireRate() {
	if (mFireRateLevel < 10) {
		++mFireRateLevel;
	}
}

void Aircraft::increaseSpread() {
	if (mSpreadLevel < 3) {
		++mSpreadLevel;
	}
}

void Aircraft::collectMissiles(unsigned int count) {
	mMissileAmmo += count;
}
*/

void Aircraft::fire() {
	// Only ships with fire interval != 0 are able to fire
	if (Table[mShipType].fireInterval != sf::Time::Zero) {
		mIsFiring = true;
	}
}

/*
void Aircraft::launchMissile() {
	if (mMissileAmmo > 0) {
		mIsLaunchingMissile = true;
		--mMissileAmmo;
	}
}
*/

void Aircraft::updateMovementPattern(sf::Time dt) {
	// This is fine for now, but I'll need an additional function to update movement patterns at runtime

	// Enemy airplane: Movement pattern
	const std::vector<Direction>& directions = Table[mShipType].directions;
	if (!directions.empty()) {
		// Moved long enough in current direction: Change direction
		if (mTravelledDistance > directions[mDirectionIndex].distance) {
			mDirectionIndex = (mDirectionIndex + 1) % directions.size();
			mTravelledDistance = 0.f;
		}

		// Compute velocity from direction
		float radians = toRadian(directions[mDirectionIndex].angle + 90.f);
		float vx = getMaxSpeed() * std::cos(radians);
		float vy = getMaxSpeed() * std::sin(radians);

		setVelocity(vx, vy);
		mTravelledDistance += getMaxSpeed() * dt.asSeconds();
	}
}

/*
void Aircraft::checkPickupDrop(CommandQueue& commands) {
	if (!isAllied() && randomInt(3) == 0) {
		commands.push(mDropPickupCommand);
	}
}
*/

void Aircraft::checkProjectileLaunch(sf::Time dt, CommandQueue& commands) {
	//std::cout << "Checking projectile launch..." << std::endl;

	// This will need to be rewritten completely
	// Enemies will fire when the world orders them to (based on timer + randomness?)
	// Players will fire iff there are less than 2 projectiles already + they are holding down the button

	if (!isAllied()) {
		fire();
	}

	// If they're trying to fire and can:
	if (mIsFiring && mFireCountdown <= sf::Time::Zero) {
		// Interval expired: we can fire a new bullet!
		std::cout << "Guns ready: FIRE!" << std::endl;
		commands.push(mFireCommand);
		mFireCountdown += Table[mShipType].fireInterval / (mFireRateLevel + 1.f);
		mIsFiring = false;
	}
	// If it's not time for them to fire yet:
	else if (mFireCountdown > sf::Time::Zero) {
		// Interval not expired: Decrease it further
		mFireCountdown -= dt;
		mIsFiring = false;
	}
	
	/*
	// Check for missile launch
	if (mIsLaunchingMissile) {
		commands.push(mMissileCommand);
		mIsLaunchingMissile = false;
	}
	*/
}

/*
void Aircraft::createBullets(SceneNode& node, const TextureHolder& textures) const {
	Projectile::Type type = isAllied() ? Projectile::AlliedBullet : Projectile::EnemyBullet;

	switch (mSpreadLevel) {
	case 1:
		createProjectile(node, type, 0.0f, 0.5f, textures);
		break;
	case 2:
		createProjectile(node, type, -0.33f, 0.33f, textures);
		createProjectile(node, type, +0.33f, 0.33f, textures);
		break;
	case 3:
		createProjectile(node, type, -0.5f, 0.33f, textures);
		createProjectile(node, type, 0.0f, 0.5f, textures);
		createProjectile(node, type, +0.5f, 0.33f, textures);
		break;
	}
}
*/

// Now a fusion of createBullet and createProjectile
void Aircraft::createProjectile(SceneNode& node, ProjectileFactory& projectileFactory) const {
	std::cout << "Creating projectile..." << std::endl;
	Projectile::Type type = isAllied() ? Projectile::AlliedBullet : Projectile::EnemyBullet;
	float xOffset = 0.0f;
	float yOffset = 0.5f;

	std::unique_ptr<Projectile> projectile(projectileFactory.newProjectile(type));

	sf::Vector2f offset(xOffset * mSprite.getGlobalBounds().width, yOffset * mSprite.getGlobalBounds().height);
	sf::Vector2f velocity(0, projectile->getMaxSpeed());

	float sign = isAllied() ? -1.f : +1.f;
	projectile->setPosition(getWorldPosition() + offset * sign);
	projectile->setVelocity(velocity * sign);
	node.attachChild(std::move(projectile));
}

/*
void Aircraft::createPickup(SceneNode& node, const TextureHolder& textures) const {
	auto type = static_cast<Pickup::Type>(randomInt(Pickup::TypeCount));

	std::unique_ptr<Pickup> pickup(new Pickup(type, textures));
	pickup->setPosition(getWorldPosition());
	pickup->setVelocity(0.f, 1.f);
	node.attachChild(std::move(pickup));
}

void Aircraft::updateTexts() {
	mHealthDisplay->setString(toString(getHitpoints()) + " HP");
	mHealthDisplay->setPosition(0.f, 50.f);
	mHealthDisplay->setRotation(-getRotation());

	if (mMissileDisplay) {
		if (mMissileAmmo == 0) {
			mMissileDisplay->setString("");
		}
		else {
			mMissileDisplay->setString("M: " + toString(mMissileAmmo));
		}
	}
}
*/
