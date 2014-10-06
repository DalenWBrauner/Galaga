#include "Player.h"

// Templating allows derivedAction(Function) on any given Function for any GameObjectType
template <typename GameObjectType, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn) {

	// Okay, don't know what [=] means.
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
		Command moveLeft;
		moveLeft.category = Category::PlayerAircraft;
		moveLeft.action = derivedAction<Entity>(
			EntityMover(-playerSpeed, 0.f));
		commands.push(moveLeft);
	}
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands) {
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
		Command output;
		output.category = Category::PlayerAircraft;
		output.action = [](SceneNode& s, sf::Time) {
			std::cout << s.getPosition().x << "," << s.getPosition().y << std::endl;
		};
		commands.push(output);
	}
}