#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC


#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 640), "GALAGA");
	sf::CircleShape circle_1;
	circle_1.setRadius(6.f);
	circle_1.setPosition(320.f, 320.f);
	circle_1.setFillColor(sf::Color::Green);

	sf::CircleShape circle_2;
	circle_2.setRadius(64.f);
	circle_2.setPosition(100.f, 100.f);
	circle_2.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(circle_1);
		window.draw(circle_2);
		window.display();
	}

	//return 0;
}