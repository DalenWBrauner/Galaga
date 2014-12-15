#ifndef Utility_h
#define Utility_h

namespace sf {
	class Sprite;
	class Text;
}

// You have to wonder why these aren't built-in
void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

// I don't know if I'll actually use this
int randomInt(int exclusiveMax);

// Vector operations
float length(sf::Vector2f vector);
sf::Vector2f unitVector(sf::Vector2f vector);

// Degree/radian conversion
float toDegree(float radian);
float toRadian(float degree);

#endif