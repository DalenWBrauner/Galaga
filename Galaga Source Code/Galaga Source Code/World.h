#include "Aircraft.h"
#include <array>

class World : private sf::NonCopyable {
public:
	explicit			World(sf::RenderWindow& window);
	void				update(sf::Time dt);
	void				draw();
	void				movePlayer(sf::Vector2f movement);

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

	// Textures
	sf::Texture mTexture;
	std::shared_ptr<sf::Texture> mTexturePtr;
	// Sprite Map
	std::map<Aircraft::EnemyType, int>	spriteMap;
	std::shared_ptr<std::map<Aircraft::EnemyType, int>> spriteMapPtr;
	
};