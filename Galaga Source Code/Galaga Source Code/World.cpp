#include "World.h"

World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(sf::Vector2f(0, 0), sf::Vector2f(512.f, 480.f))
	, mSceneGraph()
	, mSceneLayers()
	, mWorldBounds(0.f, 0.f, 512.f, 480.f)
	, mSpawnPosition(mWorldBounds.width/2, 400.f)
	, mPlayerAircraft(nullptr)
	, mFonts()
	, mTextures()
	, mSounds()
	, mAircraftFactory(&mTextures)
{
	mBoundsOffset = 32;
	mWorldView.setCenter(256, 240);

	loadResources();
	buildScene();
}

void World::loadResources() {
	loadFonts();
	loadTextures();
	loadSounds();
}

void World::loadFonts() {
	mFonts.load(Resource::Font::Galaga,				"../../Media/Galaga.ttf");
}

void World::loadTextures() {
	mTextures.load(Resource::Texture::Ships,		"../../Media/Ships.png");
	mTextures.load(Resource::Texture::Effects,		"../../Media/Effects.png");
}

void World::loadSounds() {
	mSounds.load(Resource::Sound::Coin,				"../../Media/Coin.wav");
	mSounds.load(Resource::Sound::Captured,			"../../Media/Fighter_Captured.wav");
	mSounds.load(Resource::Sound::Firing,			"../../Media/Firing.wav");
	mSounds.load(Resource::Sound::Incoming,			"../../Media/Flying_Enemy.wav");
	mSounds.load(Resource::Sound::Destroyed,		"../../Media/Kill_Enemy.wav");
	mSounds.load(Resource::Sound::Start,			"../../Media/Level_Start.wav");
	mSounds.load(Resource::Sound::Intro,			"../../Media/Theme_Song.wav");
}

void World::buildScene() {
	for (std::size_t i = 0; i < LayerCount; ++i) {
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}
	
	std::unique_ptr<Aircraft> leader(
		mAircraftFactory.newAircraft(Aircraft::PlayerShip));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setVelocity(0.f, 0.f);
	mSceneLayers[Air]->attachChild(std::move(leader));

	/* Let's add some escorts!
	std::unique_ptr<Aircraft> leftEscort(
		mAircraftFactory.newAircraft(Aircraft::Wasp));
	leftEscort->setPosition(-80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(leftEscort));

	std::unique_ptr<Aircraft> rightEscort(
		mAircraftFactory.newAircraft(Aircraft::Enterprise));
	rightEscort->setPosition(80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(rightEscort));
	*/
}

CommandQueue& World::getCommandQueue() {
	return mCommandQueue;
}

void World::movePlayer(sf::Vector2f movement){
	mPlayerAircraft->setVelocity(movement);
}

void World::update(sf::Time dt) {
	
	// Forward commands to the scene graph
	while (!mCommandQueue.isEmpty()) {
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);
	}

	invisibleWall();
	mSceneGraph.update(dt);
}

void World::invisibleWall() {
	// This acts as an "invisible wall" to keep the player on the screen
	sf::Vector2f position = mPlayerAircraft->getPosition();
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	// If the player is too far Left, prevent Left movement
	if ( (position.x <= mWorldBounds.left + mBoundsOffset)
		&& (velocity.x < 0)) { velocity.x = 0; }

	// If the player is too far Right, prevent Right movement
	else if ((position.x >= mWorldBounds.width - mBoundsOffset)
		&& (velocity.x > 0)) { velocity.x = 0; }

	// Set their modified velocity
	mPlayerAircraft->setVelocity(velocity);
}

void World::draw() {
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}