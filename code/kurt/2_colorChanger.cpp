#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib> //header for srand() & rand()
#include <ctime> //header for time()
#include <math.h>

#define FPS 60
#define CSIZE 5

using namespace std;

int main( void )
{
	sf::RenderWindow window( sf::VideoMode( 200, 200 ), "SFML works!" );
	sf::CircleShape shape( 100.f );
	sf::Color color[CSIZE];
	color[0] = sf::Color::Green;
	color[1] = sf::Color::Blue;
	color[2] = sf::Color::Red;
	color[3] = sf::Color::Yellow;
	color[4] = sf::Color::Cyan;
	int curr = 0;
	int tempCurr = 0;
	shape.setFillColor( color[curr] );
	sf::Clock clock;
	window.setFramerateLimit( FPS );
	srand(time(NULL));
	int counter = 0;
	sf::Time totalElapsed = sf::seconds(0);
	sf::Time tempElapsed = sf::seconds(0);
	//sf::font font;

	sf::Text text;

	
	text.setCharacterSize(24);
	//text.setColor(sf::Color::Black);

	while( window.isOpen() )
	{

		sf::Event event;
		sf::Time elapsed = clock.restart();
		tempElapsed = operator+ (tempElapsed, elapsed);
		totalElapsed = operator+ (totalElapsed, elapsed);
		counter++;

		if (operator>= (tempElapsed, sf::seconds(3.0f))){
			tempCurr = curr;
			curr = rand() % CSIZE;
			while(tempCurr == curr){ //f o r c e f u l c o l o r c h a n g e
				curr = rand() % CSIZE;
			}
			shape.setFillColor( color[curr] );
			tempElapsed = sf::seconds(0);
		}

		while( window.pollEvent( event ) )
		{
			switch( event.type ){
				case sf::Event::Closed:
				window.close();
				break;

				case sf::Event::KeyPressed:
				if( event.key.code == sf::Keyboard::Escape )
				{
					window.close();
				}
				break;
			}
		}
		
		window.clear();
		text.setString("hello");
		
		window.draw(shape);
		window.draw(text);
		window.display();

		cout << ">>> Iteration: " << counter << endl;
		cout << "Time since last iteration: " << floor(elapsed.asSeconds()) << " seconds and " << (elapsed.asMilliseconds() % 1000) << " milliseconds" << endl;
		cout << "Total time elapsed: " << floor(totalElapsed.asSeconds()) << " seconds and " << (totalElapsed.asMilliseconds() % 1000) << " milliseconds" << endl;
	}
	return 0;
}


