#include "Application.h"

void Application::reigsterStates() {
	mStateStack.registerState<TitleState>(States::Title);
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<GameState>(States::Game);
	mStateStack.registerState<PauseState>(States::Pause);
}

void Application::update(sf::Time dt) {
	mStateStack.update(dt);
}

/*

while (mWindow.pollEvent(event)) {
	mStateStack.handleEvent(event);
}


mStateStack.draw();


if (mStateStack.isEmpty())
	mWindow.close();


mStateStack.pushState(States::Title);
*/