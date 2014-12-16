#ifndef TextNode_h
#define TextNode_h
#include "ResourceHolder.h"
#include "ResourceIDs.h"
#include "SceneNode.h"
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\RenderTarget.hpp>

class TextNode : public SceneNode {
public:
	explicit		TextNode(const FontHolder& fonts, const std::string& text);
	void			setString(const std::string& text);

private:
	virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Text		mText;
};
#endif