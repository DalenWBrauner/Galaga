#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC

#ifndef Galaga_h
#define Galaga_h
#include "World.h"
//#include "Player.h"
#include <sstream>

class Galaga;

class Galaga {

private:
	// Player
	Player mPlayer;

	// World
	World mWorld;

	// Mechanics
	sf::RenderWindow mWindow;
	sf::Time TimePerFrame;

	// Text
	sf::Font font;
	sf::Text SFXText;
	sf::Text scoreDisplay;

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

	// Other
	int yourScore;
	int highScore;

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

#endif