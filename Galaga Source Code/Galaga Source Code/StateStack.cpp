#include "StateStack.h"

StateStack::StateStack(State::Context context)
	: mStack()
	, mPendingList()
	, mContext(context)
	, mFactories()
{}

void StateStack::update(sf::Time dt) {
	// Calls update() for every state, starting from the top
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
		if (!(*itr)->update(dt)) {
			// Quit early if a state returns false
			return;
		}
	}
	// Only make changes to the stack after handling events
	applyPendingChanges();
}

void StateStack::draw() {
	// Draws each state, starting from the bottom
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
		(*itr)->draw();
	}
}

template <typename T>
void StateStack::registerState(States::ID stateID) {
	// Stores a factory for the respective state in mFactories
	mFactories[stateID] = [this]() {
		return State::Ptr(new T(*this, mContext));
	}
}

State::Ptr StateStack::createState(States::ID stateID) {
	// Uses the appropriate mFactory to create a new state
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());

	return found->second();
}

void StateStack::handleEvent(const sf::Event& event) {
	// Calls handleEvent() for every state, starting from the top
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
		if (!(*itr)->handleEvent(event)) {
			// Quit early if a state returns false
			return;
		}
	}
	// Only make changes to the stack after handling events
	applyPendingChanges();
}

void StateStack::applyPendingChanges() {
	for (PendingChange change : mPendingList) {
		switch (change.action) {
		case Push:
			mStack.push_back(createState(change.stateID));
			break;
		case Pop:
			mStack.pop_back();
			break;
		case Clear:
			mStack.clear();
			break;
		}
	}
	mPendingList.clear();
}

void StateStack::pushState(States::ID stateID) {
	mPendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::popState() {
	mPendingList.push_back(PendingChange(Pop));
}

void StateStack::clearStates() {
	mPendingList.push_back(PendingChange(Clear));
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
	: action(action)
	, stateID(stateID)
{}