#ifndef SceneNode_h
#define SceneNode_h
#include "Inclusion.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <assert.h>
#include <functional>
#include <queue>

class SceneNode;
class SpriteNode;
struct Command;
class CommandQueue;

namespace Category {
	enum Type {
		None = 0,
		Scene =			 1 << 0,
		PlayerAircraft = 1 << 1,
		EnemyAircraft =	 1 << 2,
		Collectable =	 1 << 3,
	};
}

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
public:
	typedef std::unique_ptr<SceneNode> Ptr;

	SceneNode();
	void				update(sf::Time dt);

	unsigned int		getCategory() const;
	void				onCommand(const Command& command, sf::Time dt);

	void				attachChild(Ptr child);
	Ptr					detachChild(const SceneNode& node);

	sf::Transform		getWorldTransform() const;
	sf::Vector2f		getWorldPosition() const;

private:
	virtual void		updateCurrent(sf::Time dt);
	void				updateChildren(sf::Time dt);

	virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<Ptr>	mChildren;
	SceneNode*			mParent;
protected:
	Category::Type		mCategory;

};

class SpriteNode : public SceneNode {
public:
	explicit		SpriteNode(const sf::Texture& texture);
	SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);

private:
	virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Sprite		mSprite;
};

struct Command {
	Command();
	std::function<void(SceneNode& s, sf::Time dt)>	action;
	unsigned int									category;
};

/* Command Syntax Example
Command commandStop;
commandStop.action = [] (SceneNode& node, sf::Time dt)
{
	node.setVelocity(0.f, 0.f);
};
commandStop.category	= Category::AlliedAircraft
						| Category::EnemyAircraft;
*/

class CommandQueue {
public:
	void		push(const Command& command);
	Command		pop();
	bool		isEmpty() const;

private:
	std::queue<Command> mQueue;
};

#endif