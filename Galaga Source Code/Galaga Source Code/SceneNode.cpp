#include "SceneNode.h"
#include "Command.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

// SceneNode Definitions
SceneNode::SceneNode(Category::Type category)
	: mChildren()
	, mParent(nullptr)
	, mDefaultCategory(category)
{}

void SceneNode::update(sf::Time dt, CommandQueue& commands) {
	updateCurrent(dt, commands);
	updateChildren(dt, commands);
}

void SceneNode::updateCurrent(sf::Time dt, CommandQueue& commands) {
	// Nothing by default
}

void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands) {
	for (const Ptr& child : mChildren) {
		child->update(dt, commands);
	}
}

unsigned int SceneNode::getCategory() const {
	return mDefaultCategory;
}

void SceneNode::onCommand(const Command& command, sf::Time dt) {
	if (command.category & getCategory()) {
		command.action(*this, dt);
	}

	for (const Ptr& child : mChildren) {
		child->onCommand(command, dt);
	}
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	states.transform *= getTransform();
	drawCurrent(target, states);
	drawChildren(target, states);

	// DEBUG: Draw bounding rectangle
	//drawBoundingRect(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	// Do nothing
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const Ptr& child : mChildren) {
		child->draw(target, states);
	}
}

void SceneNode::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const {
	sf::FloatRect rect = getBoundingRect();

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.f);

	target.draw(shape);
}

void SceneNode::attachChild(Ptr child) {
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node) {

	// Find the node
	auto found = std::find_if(mChildren.begin(), mChildren.end(),
		[&](Ptr& p) -> bool { return p.get() == &node; });

	// Assert we found something
	assert(found != mChildren.end());

	// Detach and return
	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

sf::Transform SceneNode::getWorldTransform() const {
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->mParent) {
		transform *= node->getTransform();
	}
	return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const {
	return getWorldTransform() * sf::Vector2f();
}

sf::FloatRect SceneNode::getBoundingRect() const {
	return sf::FloatRect();
}

bool SceneNode::isMarkedForRemoval() const {
	return isDestroyed();
}

bool SceneNode::isDestroyed() const {
	return false;
}