#include "World.h"

World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mTexture()
	, mSceneGraph()
	, mSceneLayers()
	, mWorldBounds(
		0.f,					// left X position
		0.f,					// top Y position
		512.f,					// width
		480.f					// height
	)
	, mSpawnPosition(250.f, 400.f)	// This will become variable once I better understand boundaries
	, mPlayerAircraft(nullptr)
{
	//std::cout << mWorldView.getSize().x << std::endl;
	//std::cout << mWorldView.getSize().y << std::endl;

	loadTextures();
	prepareSpriteMap();
	buildScene();

	//	Wrong argument: our mWorldView's center will never change.
	//	mWorldView.setCenter(mSpawnPosition);
	//	Equally wrong: our mWorldView's center should actually be the
	//	center of the playing field, not the screen.
	mWorldView.setCenter(256, 240);

	std::cout << "AND THUS THE WORLD WAS BORN" << std::endl;
}

void World::update(sf::Time dt) {
	//std::cout << "AND THUS THE WORLD WAS UPDATED" << std::endl;
	//mWorldView.move(0.f, mScrollSpreed * dt.asSeconds());
	sf::Vector2f position = mPlayerAircraft->getPosition();
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	if (position.x <= mWorldBounds.left || position.x >= mWorldBounds.width) {
		velocity.x = -velocity.x;
		mPlayerAircraft->setVelocity(velocity);
	}
	mSceneGraph.update(dt);
}

void World::draw() {
	std::cout << "AND THUS THE WORLD WAS DRAWN" << std::endl;
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

void World::loadTextures() {
	//std::cout << "AND THUS THE WORLD'S TEXTURES WERE LOADED" << std::endl;
	if (!mTexture.loadFromFile("../../Media/Sprite Sheet.png"))
		throw std::runtime_error("Failed to load sprite sheet.");

	mTexturePtr = std::make_shared<sf::Texture>(mTexture);
	// Clearly this isn't Galaga sprites/textures.
	// That being said, I do want to recreate it using the correct sprites/textures,
	// But I need to see the bigger picture first.
	//mTextures.load(Textures::Eagle,	"Media/Textures/Eagle.png");
	//mTextures.load(Textures::Raptor,	"Media/Textures/Raptor.png");
	//mTextures.load(Textures::Desert,	"Media/Textures/Desert.png");
}

void World::prepareSpriteMap() {
	// I'm pretty sure this is roughly where I want this to be
	std::cout << "AND THUS THE WORLD'S SPRITEMAP WAS PREPARED" << std::endl;

	spriteMap[Aircraft::RedShip] = 1;
	spriteMap[Aircraft::WhiteShip] = 18;
	spriteMap[Aircraft::DawnOwl] = 35;
	spriteMap[Aircraft::DuskOwl] = 52;
	spriteMap[Aircraft::Butterfly] = 69;
	spriteMap[Aircraft::Wasp] = 86;
	spriteMap[Aircraft::Pudding] = 103;
	spriteMap[Aircraft::Scorpion] = 120;
	spriteMap[Aircraft::Greenie] = 137;
	spriteMap[Aircraft::Dragonfly] = 154;
	spriteMap[Aircraft::Enterprise] = 171;
	spriteMap[Aircraft::Petalcopter] = 188;

	spriteMapPtr = std::make_shared<std::map<Aircraft::EnemyType, int>>(spriteMap);
}

void World::buildScene() {
	std::cout << "AND THUS THE WORLD'S SCENE WAS BUILT" << std::endl;
	for (std::size_t i = 0; i < LayerCount; ++i) {
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	// For the background desert texture not in Galaga
//	sf::Texture& texture = mTextures.get(Textures::Desert);
//	sf::IntRect textureRect(mWorldBounds);
//	texture.setRepeated(true);
//
//	std::unique_ptr<SpriteNode> backgroundSprite(
//		new SpriteNode(texture, textureRect));
//	backgroundSprite->setPosition(
//		mWorldBounds.left,
//		mWorldBounds.top);
//	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	std::unique_ptr<Aircraft> leader(
		new Aircraft(Aircraft::WhiteShip, mTexturePtr, spriteMapPtr));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setVelocity(1.f, 0.f);
	mSceneLayers[Air]->attachChild(std::move(leader));

	// Let's add some escorts!
	std::unique_ptr<Aircraft> leftEscort(
		new Aircraft(Aircraft::RedShip, mTexturePtr, spriteMapPtr));
	leftEscort->setPosition(-80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(leftEscort));

	std::unique_ptr<Aircraft> rightEscort(
		new Aircraft(Aircraft::RedShip, mTexturePtr, spriteMapPtr));
	rightEscort->setPosition(80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(rightEscort));
}