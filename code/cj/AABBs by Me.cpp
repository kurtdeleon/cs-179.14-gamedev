#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <stdlib.h>

#define FPS 144
#define TIMESTEP 1.0f / FPS
#define WIDTH 800
#define HEIGHT 600
#define DEGREE 45

using namespace std;
using namespace sf;

RenderWindow window;
RectangleShape rectArray[5];
RectangleShape aabb[5];
float degrees[5];


//set the random degree of rotation
void degreeSet()
{
	srand (time (NULL));

	for (int i = 0; i < 5; i++)
	{
		degrees[i] = ((rand() % DEGREE) + 1);
	}
}

void rotateAABB (int i)
{
	float x = rectArray[i].getPosition().x;
	float y = rectArray[i].getPosition().y;

	float rotateX = x * cos (rectArray[i].getRotation()) - y * sin (rectArray[i].getRotation());
	float rotateY = x * sin (rectArray[i].getRotation()) + y * cos (rectArray[i].getRotation());

	aabb[i].setSize (Vector2f (rotateX, rotateY));
	aabb[i].setOrigin (aabb[i].getSize() * 0.5f);
}

int main()
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create (VideoMode (WIDTH,HEIGHT), "AABBs", Style::Default, settings);
	window.setFramerateLimit (FPS);
	window.setKeyRepeatEnabled (false);

	//hardcoded rectangles
	rectArray[0].setSize (Vector2f (150.0f, 242.0f));
	rectArray[0].setPosition (150.f, 130.f);

	rectArray[1].setSize (Vector2f (42.0f, 440.0f));
	rectArray[1].setPosition (420.f, 150.f);

	rectArray[2].setSize (Vector2f (242.0f, 42.0f));
	rectArray[2].setPosition (500.f, 420.f);

	rectArray[3].setSize (Vector2f (110.0f, 20.0f));
	rectArray[3].setPosition (330.f, 80.f);

	rectArray[4].setSize (Vector2f (150.0f, 150.0f));
	rectArray[4].setPosition (150.f, 400.f);

	for (int i = 0; i < 5; i++)
	{
		//set initial aabb size
		aabb[i].setSize (rectArray[i].getSize());
		aabb[i].setPosition (rectArray[i].getPosition() - rectArray[i].getSize() * 0.5f);

		//center the origin
		rectArray[i].setOrigin (rectArray[i].getSize() * 0.5f);

		//initial color instantiation
		rectArray[i].setFillColor (Color::Green);
		aabb[i].setFillColor (Color::Transparent);
		aabb[i].setOutlineColor (Color::Magenta);
		aabb[i].setOutlineThickness (1.0f);
	}

	degreeSet();

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

		//rotation
		for (int i = 0; i < 5; i++)
		{
			rectArray[i].rotate (degrees[i] * TIMESTEP);

			rotateAABB (i);

			window.draw (rectArray[i]);
			window.draw (aabb[i]);
		}

		window.display();
	}
}