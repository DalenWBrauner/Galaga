#ifndef SpriteNode_h
#define SpriteNode_h
#include "SceneNode.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class SpriteNode;

class SpriteNode : public SceneNode {
public:
	explicit		SpriteNode(const sf::Texture& texture);
	SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);

private:
	virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Sprite		mSprite;
};

#endif