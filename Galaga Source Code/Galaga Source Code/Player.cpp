#include "Player.h"

void Player::handleRealTimeInput(CommandQueue& commands) {
	// For commands that depend on the current state
	// "You're pressing [keystroke]!"

	const float PlayerSpeed = 75.f;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		std::cout << "You're pressing up!" << std::endl;

		Command moveLeft;
		moveLeft.category = Category::PlayerAircraft;
		moveLeft.action = derivedAction<Entity>(EntityMover(-PlayerSpeed, 0.f));
		commands.push(moveLeft);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		std::cout << "You're pressing down!" << std::endl;

		Command moveRight;
		moveRight.category = Category::PlayerAircraft;
		moveRight.action = derivedAction<Entity>(EntityMover(PlayerSpeed, 0.f));
		commands.push(moveRight);
	}
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands) {
	// For commands that depend on when the state changes
	// "You pressed [keystroke]!"

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
		std::cout << "You pressed P!" << std::endl;

		Command output;
		output.category = Category::PlayerAircraft;
		output.action = [](SceneNode& s, sf::Time dt) {
			std::cout << s.getPosition().x << "," << s.getPosition().y << std::endl;
		};
		commands.push(output);
	}
}