#ifndef StateStack_h
#define StateStack_h
#include "State.h"
#include "StateIDs.h"
#include "ResourceIDs.h"
#include "SFML\System\NonCopyable.hpp"
#include <vector>
#include <utility>
#include <functional>
#include <map>

class StateStack : private sf::NonCopyable {
public:
	enum Action {
		Push,
		Pop,
		Clear
	};

	explicit			StateStack(State::Context context);

	template <typename someState>
	void				registerState(States::ID stateID);

	void				update(sf::Time dt);
	void				draw();
	void				handleEvent(const sf::Event& event);

	void				pushState(States::ID stateID);
	void				popState();
	void				clearStates();

	bool				isEmpty() const;

private:
	State::Ptr			createState(States::ID stateID);
	void				applyPendingChanges();

	struct PendingChange {
		explicit		PendingChange(Action action, States::ID stateID = States::None);
		Action			action;
		States::ID		stateID;
	};

	std::vector<State::Ptr>				mStack;
	std::vector<PendingChange>			mPendingList;
	State::Context						mContext;
	std::map < States::ID,
		std::function < State::Ptr() >> mFactories;
};

// I need to research why this is necessary
template <typename someState>
void StateStack::registerState(States::ID stateID) {
	// Stores a factory for the respective state in mFactories
	mFactories[stateID] = [this]() {
		return State::Ptr(new someState(*this, mContext));
	};
}

#endif