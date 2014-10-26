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
#include "Player.h"
#include <sstream>

class Galaga;

class Galaga {

private:
	Player mPlayer;
	World mWorld;
	sf::RenderWindow mWindow;
	static const sf::Time TimePerFrame;
	static const float PlayerSpeed;

	// Text (Will be moved)
	sf::Font font;
	sf::Text SFXText;
	sf::Text scoreDisplay;

	// Audio (Will be moved)
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

	// Score (Will be moved)
	int yourScore;
	int highScore;

	void loadAssets();
	void processInput();
	void handleGameInput();
	void update(sf::Time);
	void render();

public:
	Galaga();
	void run();
};

#endif