#include "State.h"
#include "StateStack.h"	// I need this because forward declaration

State::Context::Context(
	sf::RenderWindow& window,
	TextureHolder& textures,
	FontHolder& fonts,
	Player& player)
	: window(&window)
	, textures(&textures)
	, fonts(&fonts)
	, player(&player)
{}

State::State(StateStack& stack, Context context)
	: mStack(&stack)
	, mContext(context)
{}

State::~State() {}

void State::requestStackPush(States::ID stateID) {
	//std::cout << "REQUESTING STACK PUSH" << std::endl;
	mStack->pushState(stateID);
}

void State::requestStackPop() {
	//std::cout << "REQUESTING STACK POP" << std::endl;
	mStack->popState();
}

void State::requestStackClear() {
	//std::cout << "REQUESTING STACK CLEAR" << std::endl;
	mStack->clearStates();
}

State::Context State::getContext() const{
	return mContext;
}