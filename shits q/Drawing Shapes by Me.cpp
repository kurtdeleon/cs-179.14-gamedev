#include <SFML/Graphics.hpp>
#include <iostream>

#define FPS 144
#define TIMESTEP 1.0f / FPS
#define WIDTH 800
#define HEIGHT 600
#define CIRCLES 60
#define RECTS 40
#define COLORS 6

using namespace std;
using namespace sf;

RenderWindow window;

CircleShape c[CIRCLES];
RectangleShape r[RECTS];
Color col[COLORS];

int main()
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create (VideoMode (WIDTH,HEIGHT), "Drawing Shapes", Style::Default, settings);
	window.setFramerateLimit (FPS);
	window.setKeyRepeatEnabled (false);

	srand (time (NULL));

	col[0] = Color::Red;
	col[1] = Color::Green;
	col[2] = Color::Blue;
	col[3] = Color::Yellow;
	col[4] = Color::Cyan;
	col[5] = Color::White;

	for (int i = 0; i < CIRCLES; i++)
	{
		c[i].setRadius (30.0f);
		c[i].setPosition (Vector2f (rand() % (WIDTH - 1), rand() % (HEIGHT - 1)));
		c[i].setFillColor (col[rand() % 6]);
	}

	for (int i = 0; i < RECTS; i++)
	{
		r[i].setSize (Vector2f (50.0f, 50.0f));
		r[i].setPosition (Vector2f (rand() % (WIDTH - 1), rand() % (HEIGHT - 1)));
		r[i].setFillColor (col[rand() % 6]);
	}


	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent (event))
		{
			if (event.key.code == Keyboard::X)
			{
				cout << "Exit!" << endl;
				window.close();
			}
		}

		window.clear (Color::Black);

		for (int i = 0; i < CIRCLES; i++)
		{
			c[i].move(0, 20.0f * TIMESTEP);
			window.draw (c[i]);
		}

		for (int i = 0; i < RECTS; i++)
		{
			r[i].move(20.0f * TIMESTEP, 0);
			window.draw (r[i]);
		}


		window.display();
	}
}