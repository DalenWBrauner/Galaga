#include "StateStack.h"
#include <iostream>

StateStack::StateStack(State::Context context)
	: mStack()
	, mPendingList()
	, mContext(context)
	, mFactories()
{}

State::Ptr StateStack::createState(States::ID stateID) {
	// Uses the appropriate mFactory to create a new state
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());

	return found->second();
}

void StateStack::draw() {
	//std::cout << "-- draw() StateStack" << std::endl;

	// Draws each state, starting from the bottom
	for (unsigned i = 0; i < mStack.size(); i++) {
		(mStack)[i]->draw();
	}
}

void StateStack::update(sf::Time dt) {
	//std::cout << "-- update() StateStack" << std::endl;

	// Calls update() for every state, starting from the top
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
		if (!(*itr)->update(dt)) {
			// Quit early if a state returns false
			break;
		}
	}
	// Only make changes to the stack after handling events
	applyPendingChanges();
}

void StateStack::handleEvent(const sf::Event& event) {
	//std::cout << "-- handleEvent() StateStack" << std::endl;

	// Calls handleEvent() for every state, starting from the top
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
		if (!(*itr)->handleEvent(event)) {
			// Quit early if a state returns false
			break;
		}
	}
	// Only make changes to the stack after handling events
	applyPendingChanges();
}

void StateStack::applyPendingChanges() {
	for (PendingChange change : mPendingList) {
		switch (change.action) {
		case Push:
			//std::cout << "applyPendingChange(): push_back...";
			mStack.push_back(createState(change.stateID));
			//std::cout << "done!" << std::endl;
			break;
		case Pop:
			//std::cout << "applyPendingChange(): pop_back...";
			mStack.pop_back();
			//std::cout << "done!" << std::endl;
			break;
		case Clear:
			//std::cout << "applyPendingChange(): clear...";
			mStack.clear();
			//std::cout << "done!" << std::endl;
			break;
		}
	}
	mPendingList.clear();
}

void StateStack::pushState(States::ID stateID) {
	//std::cout << "PUSHING STATE!" << std::endl;
	mPendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::popState() {
	//std::cout << "POPPING STATE!" << std::endl;
	mPendingList.push_back(PendingChange(Pop));
}

void StateStack::clearStates() {
	//std::cout << "CLEARING STATE!" << std::endl;
	mPendingList.push_back(PendingChange(Clear));
}

bool StateStack::isEmpty() const {
	return mStack.empty();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
	: action(action)
	, stateID(stateID)
{}