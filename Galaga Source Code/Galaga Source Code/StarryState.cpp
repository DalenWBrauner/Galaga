#include "StarryState.h"
#include "ResourceHolder.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include <iostream>

StarryState::StarryState(StateStack& stack, Context context)
	: State(stack, context)
	, mStars()
{}

void StarryState::draw() {
	sf::RenderWindow& window = *getContext().window;
	//window.clear();		// Draw the night sky
	for (sf::Sprite& star : mStars) {
		window.draw(star);
	}
}

bool StarryState::update(sf::Time dt) {
	//std::cout << "Updating StarryState" << std::endl;

	insertStarsRandomly();

	for (sf::Sprite& star : mStars) {
		// Update each star's position
		// If a star leaves the field, delete it
	}

	// StarryState pauses all states below
	return false;
}

// StarryState pauses all states below
bool StarryState::handleEvent(const sf::Event& event) { return false; }

void StarryState::insertStarsRandomly() {
	// Stars spawn above the playing field
	// Stars have a random (visible) x-coordinate
	// Stars have a random color
	// Stars are not spawned every time this funciton is called
	// Stars are all given a velocity (details can be chosen later)
	// Stars are added to mStars()
}