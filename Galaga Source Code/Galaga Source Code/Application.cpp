#include "Application.h"
#include "State.h"
#include "StateIDs.h"
#include "TitleState.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"
#include "StarryState.h"
#include "ScoreState.h"

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
	: mWindow(sf::VideoMode(512, 480), "GALAGA")
	, mTextures()
	, mFonts()
	, mPlayer()
	, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
{
	mWindow.setKeyRepeatEnabled(false);

	mFonts.load(Resource::Font::Galaga, "../../Media/Galaga.ttf");
	mTextures.load(Resource::Texture::Title, "../../Media/Title.png");

	mStatisticsText.setFont(mFonts.get(Resource::Font::Galaga));
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10u);

	registerStates();
	mStateStack.pushState(States::Starry);	// Start the aesthetic
	mStateStack.pushState(States::Title);	// Let's get started!
}

void Application::run() {
	// Launches the game
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen()) {
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;

		// While there are still time-steps that ought to have passed
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
			timeStep();
		}
		updateStatistics(dt);
		render();
	}
}

void Application::timeStep() {
	processInput();
	update(TimePerFrame);

	if (mStateStack.isEmpty()) {
		mWindow.close();
	}
}

void Application::registerStates() {
	mStateStack.registerState<StarryState>(States::Starry);
	mStateStack.registerState<TitleState>(States::Title);
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<GameState>(States::Game);
	mStateStack.registerState<PauseState>(States::Pause);
	mStateStack.registerState<ScoreState>(States::Scoreboard);
}

void Application::update(sf::Time dt) { mStateStack.update(dt); }

void Application::processInput() {
	sf::Event event;
	while (mWindow.pollEvent(event)) {
		mStateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::render() {
	mWindow.clear();
	mStateStack.draw();
	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mStatisticsText);	// Draw statistics absolutely last
	mWindow.display();
}

// Mimic'd exactly from the Source Code
void Application::updateStatistics(sf::Time dt) {
	mStatisticsUpdateTime += dt;
	mStatisticsNumFrames += 1;
	if (mStatisticsUpdateTime >= sf::seconds(1.0f)) {
		mStatisticsText.setString("FPS: " + std::to_string(mStatisticsNumFrames));

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}