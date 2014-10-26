#include "SceneNode.h"

// SceneNode Definitions
SceneNode::SceneNode() {
	mCategory = Category::Type::Scene;
}

void SceneNode::update(sf::Time dt) {
	//std::cout << "SceneNode.update("<< dt.asSeconds << ")" << std::endl;
	updateCurrent(dt);
	updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time dt) {
	//std::cout << "SceneNode.updateCurrent(" << dt.asSeconds << ")" << std::endl;
}

void SceneNode::updateChildren(sf::Time dt) {
	//std::cout << "SceneNode.updateChildren(" << dt.asSeconds << ")" << std::endl;
	for (const Ptr& child : mChildren) {
		child->update(dt);
	}
}

unsigned int SceneNode::getCategory() const {
	return mCategory;
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
	//std::cout << "SceneNode.draw()" << std::endl;

	// "Apply transform of current node"
	states.transform *= getTransform();

	// Draw self & children
	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	//std::cout << "SceneNode.draw()" << std::endl;
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const Ptr& child : mChildren) {
		child->draw(target, states);
	}
}

void SceneNode::attachChild(Ptr child) {
	// Attaches the provided child
	//std::cout << "SceneNode.attachChild()" << std::endl;
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node) {
	// Detaches the provided child
	//std::cout << "start: SceneNode.detachChild()" << std::endl;

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
	//std::cout << "start: SceneNode.getWorldTransform()" << std::endl;
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->mParent) {
		transform *= node->getTransform();
	}
	return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const {
	//std::cout << "start: SceneNode.getWorldPosition()" << std::endl;
	return getWorldTransform() * sf::Vector2f();
}
