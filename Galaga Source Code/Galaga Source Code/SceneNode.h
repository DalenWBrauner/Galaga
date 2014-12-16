#ifndef SceneNode_h
#define SceneNode_h
#include "Category.h"
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <vector>
#include <set>
#include <memory>
#include <utility>
#include <algorithm>
#include <assert.h>
#include <functional>
#include <queue>

struct Command;
class CommandQueue;

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
public:
	typedef std::unique_ptr<SceneNode> Ptr;
	typedef std::pair<SceneNode*, SceneNode*> Pair;

	explicit				SceneNode(Category::Type category = Category::None);
	void					update(sf::Time dt, CommandQueue& commands);

	unsigned int			getCategory() const;
	void					onCommand(const Command& command, sf::Time dt);

	void					attachChild(Ptr child);
	Ptr						detachChild(const SceneNode& node);

	sf::Transform			getWorldTransform() const;
	sf::Vector2f			getWorldPosition() const;

	virtual sf::FloatRect	getBoundingRect() const;
	virtual bool			isMarkedForRemoval() const;
	virtual bool			isDestroyed() const;

private:
	virtual void		updateCurrent(sf::Time dt, CommandQueue& commands);
	void				updateChildren(sf::Time dt, CommandQueue& commands);

	virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void				drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
	void				drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<Ptr>	mChildren;
	SceneNode*			mParent;
protected:
	Category::Type		mDefaultCategory;

};

#endif