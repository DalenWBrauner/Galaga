/*#include "StateStack.h"

template <typename T>
void StateStack::registerState(States::ID stateID) {
	mFactories[stateID] = [this](){
		return State::Ptr(new T(*this, mContext));
	}
}

State::Ptr StateStack::createState(States::ID stateID) {
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());

	return found->second();
}

void StateStack::handleEvent(const sf::Event& event) {
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
		if (!(*itr)->handleEvent(event)) {
			return;
		}
	}
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
*/