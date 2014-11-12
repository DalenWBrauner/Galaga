#ifndef ResourceIDs_h
#define ResourceIDs_h

// Forward Declaration
template <typename ResourceType, typename Identifier>
class ResourceHolder;

namespace sf {
	class Font;
	class Texture;
	class SoundBuffer;
}

// Identifiers
namespace Resource {
	enum Font {
		Galaga,
	};
	enum Texture {
		SpriteSheet,
	};
	enum Sound {
		Coin,
		Captured,
		Firing,
		Incoming,
		Destroyed,
		Start,
		Intro,
	};
};

// Typedefs
typedef ResourceHolder< sf::Font, Resource::Font>			FontHolder;
typedef ResourceHolder< sf::Texture, Resource::Texture>		TextureHolder;
typedef ResourceHolder< sf::SoundBuffer, Resource::Sound>	SoundHolder;

#endif