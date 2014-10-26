#ifndef SceneNode_h
#define SceneNode_h
#include "Inclusion.h"
#include "Category.h"
#include "Command.h"
#include <vector>
#include <memory>

class SceneNode;

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
public:
	typedef std::unique_ptr<SceneNode> Ptr;

	SceneNode();
	void					update(sf::Time dt);

	virtual unsigned int	getCategory() const;
	void					onCommand(const Command& command, sf::Time dt);

	void					attachChild(Ptr child);
	Ptr						detachChild(const SceneNode& node);

	sf::Transform			getWorldTransform() const;
	sf::Vector2f			getWorldPosition() const;

private:
	virtual void			updateCurrent(sf::Time dt);
	void					updateChildren(sf::Time dt);

	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void					drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<Ptr>		mChildren;
	SceneNode*				mParent;

protected:
	Category::Type			mCategory;

};

#endif