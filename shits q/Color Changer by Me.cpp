#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>

using namespace std;

#define FPS 60
#define COLORS 5

int main (void)
{
	sf::RenderWindow window (sf::VideoMode (200, 200), "Circle");
	window.setFramerateLimit (FPS);

	sf::CircleShape shape (100.f);
	sf::Color color[COLORS];
	color [0] = sf::Color::Green;
	color [1] = sf::Color::Cyan;
	color [2] = sf::Color::Yellow;
	color [3] = sf::Color::Red;
	color [4] = sf::Color::Blue;

	sf::Clock clock;
	sf::Time totalElapsed = sf::seconds (0);
	sf::Time threeTimer = sf::seconds (0);
	srand (time (NULL));

	int curr = 0;
	int counter = 0;
	
	shape.setFillColor(color [curr]);

	while (window.isOpen())
	{
		sf::Event event;

		sf::Time elapsed = clock.restart();
		totalElapsed = operator+ (totalElapsed, elapsed);
		threeTimer = operator+ (threeTimer, elapsed);

		if (operator>= (threeTimer, sf::seconds (3.0f)))
		{
			counter++;
			int tempCurr = curr;
			curr = rand() % COLORS;

			if (tempCurr == curr)
			{
				curr = rand() % COLORS;
			}

			shape.setFillColor (color [curr]);
			threeTimer = sf::seconds (0);
		}

		while (window.pollEvent (event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if  (event.type == sf::Event::KeyPressed) 
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
			}
		}

		window.clear();
		window.draw (shape);
		window.display();

		cout << ">>> Iteration: " << counter << endl;
		cout << "Time since last iteration: " << floor (threeTimer.asSeconds()) << " seconds and " << floor (threeTimer.asMilliseconds() % 1000) << " milliseconds" << endl;
		cout << "Total time elapsed; " << floor (totalElapsed.asSeconds()) << "seconds and " << floor (totalElapsed.asMilliseconds() % 1000) << " milliseconds" << endl;
	}
}