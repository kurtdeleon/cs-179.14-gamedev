#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

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
bool bUp, bDown, bLeft, bRight, bMouse;

void move()
{
	if (bUp)
	{	
		c[0].move (0, -200.f * TIMESTEP);
	}

	if (bLeft)
	{
		c[0].move (-200.f * TIMESTEP, 0);
	}

	if  (bDown)
	{
		c[0].move (0, 200.f * TIMESTEP);
	}

	if (bRight)
	{
		c[0].move (200.f * TIMESTEP, 0);
	}

	if (bMouse)
	{
		double x = Mouse::getPosition (window).x - r[0].getPosition().x;
		double y = Mouse::getPosition (window).y - r[0].getPosition().y;
		double dist = 1 / (sqrt ((x * x) + (y * y)));

		r[0].move ((x * dist) * (200.0f * TIMESTEP), (y * dist) * (200.0f * TIMESTEP));
	}

	for (int i = 1; i < CIRCLES; i++)
	{
		c[i].move(0, 20.0f * TIMESTEP);
	}

	for (int i = 1; i < RECTS; i++)
	{
		r[i].move(20.0f * TIMESTEP, 0);
	}
}

void renderingThread (RenderWindow* window)
{
	while (window->isOpen())
	{
		move();

		window->clear (sf::Color::Black);

		for (int i = 0; i < CIRCLES; i++){
			window->draw (c[i]);
		}
		for (int i = 0; i < RECTS; i++){
			window->draw (r[i]);
		}
		window->display();
	}
}

int main (void)
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create (VideoMode (WIDTH,HEIGHT), "Drawing Shapes 2", Style::Default, settings);
	window.setFramerateLimit (FPS);
	window.setKeyRepeatEnabled (false);
	window.setActive (false);

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

	Thread thread(&renderingThread, &window);
	thread.launch();

	while (window.isOpen())
	{
		Event event;
		while(window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
					case Event::Closed:
					window.close();
					break;

					case sf::Event::KeyPressed:
					switch(event.key.code){
						case sf::Keyboard::W:
						bUp = true;
						break;
						case sf::Keyboard::A:
						bLeft = true;
						break;
						case sf::Keyboard::S:
						bDown = true;
						break;
						case sf::Keyboard::D:
						bRight = true;
						break;
						case sf::Keyboard::X:
						window.close();
						break;
					}
					break;

					case sf::Event::KeyReleased:
					switch(event.key.code){
						case sf::Keyboard::W:
						bUp = false;
						break;
						case sf::Keyboard::A:
						bLeft = false;
						break;
						case sf::Keyboard::S:
						bDown = false;
						break;
						case sf::Keyboard::D:
						bRight = false;
						break;
					}
					break;

					case sf::Event::MouseButtonPressed:
					switch(event.mouseButton.button)
					{
						case sf::Mouse::Left:
						bMouse = true;
						break;
					}
					break;

					case sf::Event::MouseButtonReleased:
					switch(event.mouseButton.button)
					{
						case sf::Mouse::Left:
						bMouse = false;
						break;
					}
					break;
				}
			}
		}
	}
}