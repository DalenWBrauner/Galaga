#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <sstream>

class Galaga {

private:
	// Mechanics
	sf::RenderWindow mWindow;
	sf::Time TimePerFrame;

	// Text
	sf::Font font;
	sf::Text SFXText;
	sf::Text scoreDisplay;

	// Images
	sf::Texture mTexture;
	sf::Sprite mPlayer;

	// Audio
	sf::SoundBuffer sbfCoin;
	sf::SoundBuffer sbfCaptured;
	sf::SoundBuffer sbfFiring;
	sf::SoundBuffer sbfIncoming;
	sf::SoundBuffer sbfDestroyed;
	sf::SoundBuffer sbfStart;
	sf::SoundBuffer sbfIntro;
	sf::Sound sfxCoin;
	sf::Sound sfxCaptured;
	sf::Sound sfxFiring;
	sf::Sound sfxIncoming;
	sf::Sound sfxDestroyed;
	sf::Sound sfxStart;
	sf::Sound sfxIntro;

	// Motion
	float PlayerSpeed;
	bool mIsMovingLeft;
	bool mIsMovingRight;

	// Other
	int yourscore;
	int highscore;

	// Class Methods
	void handlePlayerInput(sf::Keyboard::Key, bool);
	void processEvents();
	void update(sf::Time);
	void render();
	void loadAssets();

public:
	// Constructors
	Galaga();

	// Usage Methods
	void run();

};