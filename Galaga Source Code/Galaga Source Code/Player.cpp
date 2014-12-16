#include "Player.h"
#include "Aircraft.h"

// Templating allows derivedAction(Function) on any given Function for any GameObjectType
template <typename GameObjectType, typename Function>
std::function<void(SceneNode& node, sf::Time dt)> derivedAction(Function fn) {

	// We return "[=]". [=] translates to: a "captured" copy of Function's return value
	return[=](SceneNode& node, sf::Time dt) {

		// Checks if we can cast our node as <GameObjectType>
		assert(dynamic_cast<GameObjectType*>(&node) != nullptr);

		// If we can, then we invoke our Function no problem!
		fn(static_cast<GameObjectType&>(node), dt);
	};
}

void Player::handleRealTimeInput(CommandQueue& commands) {
	// For commands that depend on the current state
	// "You're pressing [keystroke]!"
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands) {
	// For commands that depend on when the state changes
	// "You pressed [keystroke]!" and "You released [keystroke]!"

	if (event.key.code == sf::Keyboard::P) {
		if (event.type == sf::Event::KeyPressed) {
			std::cout << "You pressed P!\t";
		}
		else if (event.type == sf::Event::KeyReleased) {
			std::cout << "You released P!\t";
		}
		Command output;
		output.category = Category::PlayerAircraft;
		output.action = [](SceneNode& s, sf::Time dt) {
			std::cout << s.getPosition().x << "," << s.getPosition().y << std::endl;
		};
		commands.push(output);
	}

	if (event.key.code == sf::Keyboard::Space && event.type == sf::Event::KeyPressed) {
		std::cout << "You pressed Space; Fire!" << std::endl;
		Command output;
		output.category = Category::PlayerAircraft;
		output.action = [](SceneNode& s, sf::Time dt) {
			derivedAction<Aircraft>([](Aircraft& a, sf::Time){ a.fire(); });
		};
		commands.push(output);
	}
	
	// Attempt 4
	if (event.key.code == sf::Keyboard::Left) {
		if (event.type == sf::Event::KeyPressed) {
			std::cout << "Pressing left..." << std::endl;
			pressingLeft = true;
		}
		else if (event.type == sf::Event::KeyReleased) {
			std::cout << "Left released." << std::endl;
			pressingLeft = false;
		}
	}

	if (event.key.code == sf::Keyboard::Right) {
		if (event.type == sf::Event::KeyPressed) {
			std::cout << "Pressing right..." << std::endl;
			pressingRight = true;
		}
		else if (event.type == sf::Event::KeyReleased) {
			std::cout << "Right released." << std::endl;
			pressingRight = false;
		}
	}
	float x_velocity = 0.f;
	if (pressingLeft) { x_velocity -= PlayerSpeed; }
	if (pressingRight){ x_velocity += PlayerSpeed; }

	Command dragPlayer;
	dragPlayer.category = Category::PlayerAircraft;
	dragPlayer.action = derivedAction<Entity>(EntityDragger(x_velocity, 0.f));
	commands.push(dragPlayer);

	// Attempt 3
	/*
	// Reset the velocity each tick
	float x_velocity = 0.f;
	if (event.key.code == sf::Keyboard::Left && event.type == sf::Event::KeyPressed) {
		x_velocity -= PlayerSpeed;
	}

	if (event.key.code == sf::Keyboard::Right && event.type == sf::Event::KeyPressed) {
		x_velocity += PlayerSpeed;
	}
	Command dragPlayer;
	dragPlayer.category = Category::PlayerAircraft;
	dragPlayer.action = derivedAction<Entity>(EntityDragger(x_velocity, 0.f));
	commands.push(dragPlayer);
	*/
	// Attempt 2
	/*
	if (event.key.code == sf::Keyboard::Left) {
		// Accelerate to the right when you press the Left key
		if (event.type == sf::Event::KeyPressed) {
			Command moveLeft;
			moveLeft.category = Category::PlayerAircraft;
			moveLeft.action = derivedAction<Entity>(EntityMover(-PlayerSpeed, 0.f));
			commands.push(moveLeft);
		}
		// Counteract that acceleration when you release the Left key
		else if (event.type == sf::Event::KeyReleased) {
			Command moveRight;
			moveRight.category = Category::PlayerAircraft;
			moveRight.action = derivedAction<Entity>(EntityMover(PlayerSpeed, 0.f));
			commands.push(moveRight);
		}
	}
	
	if (event.key.code == sf::Keyboard::Right) {
		// Accelerate to the right when you press the Right key
		if (event.type == sf::Event::KeyPressed) {
			Command moveRight;
			moveRight.category = Category::PlayerAircraft;
			moveRight.action = derivedAction<Entity>(EntityMover(PlayerSpeed, 0.f));
			commands.push(moveRight);
		}
		// Counteract that acceleration when you release the Right key
		else if (event.type == sf::Event::KeyReleased) {
			Command moveLeft;
			moveLeft.category = Category::PlayerAircraft;
			moveLeft.action = derivedAction<Entity>(EntityMover(-PlayerSpeed, 0.f));
			commands.push(moveLeft);
		}
	}
	*/
	// Attempt 1
	/*
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
		Command moveLeft;
		moveLeft.category = Category::PlayerAircraft;
		moveLeft.action = derivedAction<Entity>(EntityMover(-PlayerSpeed, 0.f));
		commands.push(moveLeft);
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
		Command moveRight;
		moveRight.category = Category::PlayerAircraft;
		moveRight.action = derivedAction<Entity>(EntityMover(PlayerSpeed, 0.f));
		commands.push(moveRight);
	}
	*/
}