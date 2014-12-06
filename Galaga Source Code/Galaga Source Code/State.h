#ifndef State_h
#define State_h
#include "StateIDs.h"
#include "ResourceIDs.h"
#include <memory>
#include "SFML\System\Time.hpp"
#include "SFML\Window\Event.hpp"

// Forward Declarations
namespace sf {
	class RenderWindow;
}
class StateStack;
class Player;

// Class
class State {
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context {
		Context(
			sf::RenderWindow&	window,
			TextureHolder&		textures,
			FontHolder&			fonts,
			Player&				player
			);

		sf::RenderWindow*	window;
		TextureHolder*		textures;
		FontHolder*			fonts;
		Player*				player;
	};

	State(StateStack& stack, Context context);
	virtual			~State();

	virtual void	draw() = 0;
	virtual bool	update(sf::Time dt) = 0;
	virtual bool	handleEvent(const sf::Event& event) = 0;

protected:
	void			requestStackPush(States::ID stateID);
	void			requestStackPop();
	void			requestStackClear();

	Context			getContext() const;

private:
	StateStack*		mStack;
	Context			mContext;
};

#endif