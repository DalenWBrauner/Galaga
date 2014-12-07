#ifndef Application_h
#define Application_h
#include "ResourceHolder.h"
#include "ResourceIDs.h"
#include "Player.h"
#include "StateStack.h"
#include "SFML/System/Time.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"

class Application {
public:
	Application();
	void			run();

private:
	void			timeStep();
	void			processInput();
	void			update(sf::Time dt);
	void			render();

	void			updateStatistics(sf::Time dt);
	void			registerStates();

	static const sf::Time	TimePerFrame;

	sf::RenderWindow		mWindow;
	sf::View				mCorrectView;
	TextureHolder			mTextures;
	FontHolder				mFonts;
	Player					mPlayer;

	StateStack				mStateStack;

	// For displaying FPS
	sf::Text				mStatisticsText;
	sf::Time				mStatisticsUpdateTime;
	std::size_t				mStatisticsNumFrames;
};

#endif