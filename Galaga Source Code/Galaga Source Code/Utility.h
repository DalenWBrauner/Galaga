#ifndef Utility_h
#define Utility_h

namespace sf {
	class Sprite;
	class Text;
}

// You have to wonder why these aren't built-in
void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

#endif