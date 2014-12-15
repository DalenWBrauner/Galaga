#include "TextNode.h"
#include "Utility.h"

TextNode::TextNode(const FontHolder& fonts, const std::string& text) {
	mText.setFont(fonts.get(Resource::Font::Galaga));
	mText.setCharacterSize(10);
	setString(text);
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mText, states);
}

void TextNode::setString(const std::string& text) {
	mText.setString(text);
	centerOrigin(mText);
}