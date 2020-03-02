#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>

#include <game.hpp>

using namespace std;
using namespace sf;

#define FRAMERATE 60

int main()
{
	RenderWindow window(VideoMode(610, 700), "Single Rotation - Cellular Automata with C++/SFML", Style::Titlebar | Style::Close);
	//window.setFramerateLimit(FRAMERATE);
	Clock mainClock;
    Color background(50, 50, 60, 255);

    game::load(&window);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyReleased) {
				switch (event.key.code) {
					case  9: game::setPlay(-1); break;	// code  9 for J
					case 10: game::setPlay(0); break;	// code 10 for K
					case 11: game::setPlay(1); break;	// code 11 for L
					case 36: window.close(); break;		// code 36 for Escape
				}
				// cout << event.key.code << endl;
			}
			
			// catch the resize events
			if (event.type == Event::Resized)
			{
				// update the view to the new size of the window
				FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(View(visibleArea));
			}
		}
		window.clear(background);
        game::update((double)(mainClock.restart().asMicroseconds()*1e-6));
        game::draw(&window);
		window.display();
	}

	return 0;
}