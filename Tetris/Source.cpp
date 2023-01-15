#include <SFML/Graphics.hpp>
#include <time.h>
#include "Game.cpp"
#include <Windows.h>
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(320, 480), "Game");
	Game game;
	Clock clock;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
				break;
			}
			game.ProcessEvent(event);
		}
		game.Update(clock);
		game.Draw(window);
		if (game.End(window)) {
			window.display(); 
			Sleep(3000);
			window.close();
		}
		else
		window.display();
	}
	return EXIT_SUCCESS;
}
