#include <SFML\Graphics.hpp>
#include "Aircraft.h"
#include <array>

class World : private sf::NonCopyable {
public:
	explicit			World(sf::RenderWindow& window);
	void				update(sf::Time dt);
	void				draw();

private:
	void				loadTextures();
	void				prepareSpriteMap();
	void				buildScene();

	enum Layer {
		Background,
		Air,
		LayerCount,
	};
	sf::RenderWindow&					mWindow;
	sf::View							mWorldView;
//	TextureHolder						mTextures;
	SceneNode							mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;
	sf::FloatRect						mWorldBounds;
	sf::Vector2f						mSpawnPosition;
//	float								mScrollSpeed;
	Aircraft*							mPlayerAircraft;

	// Textures
	sf::Texture mTexture;
	std::shared_ptr<sf::Texture> mTexturePtr;
	// Sprite Map
	std::map<Aircraft::EnemyType, int>	spriteMap;
	std::shared_ptr<std::map<Aircraft::EnemyType, int>> spriteMapPtr;
	
};