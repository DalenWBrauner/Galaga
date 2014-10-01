#include "Inclusion.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <assert.h>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
public:
	typedef std::unique_ptr<SceneNode> Ptr;

	SceneNode();
	void				attachChild(Ptr child);
	Ptr					detachChild(const SceneNode& node);

	void				update(sf::Time dt);

	sf::Transform		getWorldTransform() const;
	sf::Vector2f		getWorldPosition() const;

private:
	// These should be made final
	virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void		updateCurrent(sf::Time dt);
	void				updateChildren(sf::Time dt);

	std::vector<Ptr>	mChildren;
	SceneNode*			mParent;
};

class SpriteNode : public SceneNode {
public:
	explicit		SpriteNode(const sf::Texture& texture);
	SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);

private:
	virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Sprite		mSprite;
};