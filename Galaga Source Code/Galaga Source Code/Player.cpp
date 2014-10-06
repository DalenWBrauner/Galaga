#include "Player.h"

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
	const float playerSpeed = 30.f;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		std::cout << "You pressed up!" << std::endl;
		std::cout << "I'm going to instantiate a command!" << std::endl;
		Command moveLeft;
		std::cout << "Now I'm going to set its category!" << std::endl;
		moveLeft.category = Category::PlayerAircraft;
		std::cout << "Now I'm going to set its action!" << std::endl;
		moveLeft.action = derivedAction<Entity>(EntityMover(-playerSpeed, 0.f));
		std::cout << "Now I'm going to insert it into the CommandQueue!" << std::endl;
		commands.push(moveLeft);
	}
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands) {
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
		std::cout << "You pressed P!" << std::endl;
		std::cout << "I'm going to instantiate a command!" << std::endl;
		Command output;
		std::cout << "Now I'm going to set its category!" << std::endl;
		output.category = Category::PlayerAircraft;
		std::cout << "Now I'm going to set its action!" << std::endl;
		output.action = [](SceneNode& s, sf::Time dt) {
			std::cout << s.getPosition().x << "," << s.getPosition().y << std::endl;
		};
		std::cout << "Now I'm going to insert it into the CommandQueue!" << std::endl;
		commands.push(output);
	}
}