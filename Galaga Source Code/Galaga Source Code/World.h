#ifndef World_h
#define World_h
#include "Aircraft.h"
#include "SpriteNode.h"
#include "CommandQueue.h"
#include "Player.h"
#include "ResourceHolder.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>

class World : private sf::NonCopyable {
public:
	explicit			World(sf::RenderWindow& window);
	void				update(sf::Time dt);
	void				draw();
	void				movePlayer(sf::Vector2f movement);
	CommandQueue&		getCommandQueue();

private:
	void				loadTextures();
	void				prepareSpriteMap();
	void				buildScene();
	void				invisibleWall();

	enum Layer {
		Background,
		Air,
		LayerCount,
	};
	sf::RenderWindow&					mWindow;
	sf::View							mWorldView;
	SceneNode							mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;
	sf::FloatRect						mWorldBounds;
	sf::Vector2f						mSpawnPosition;
	Aircraft*							mPlayerAircraft;
	float								mBoundsOffset;
	CommandQueue						mCommandQueue;

	// Textures
	sf::Texture mTexture;
	std::shared_ptr<sf::Texture> mTexturePtr;
	// Sprite Map
	std::map<Aircraft::ShipType, int>	spriteMap;
	std::shared_ptr<std::map<Aircraft::ShipType, int>> spriteMapPtr;
};

#endif