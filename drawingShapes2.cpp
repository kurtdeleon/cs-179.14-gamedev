#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#define FPS 144
#define CSIZE 6
#define CIRCLES 60
#define RECTANGLES 40
#define WINDOW_H 720
#define WINDOW_W 1280
#define SPEED 20

using namespace std;

sf::Color color[CSIZE];
sf::CircleShape cArray[CIRCLES];
sf::RectangleShape rArray[RECTANGLES];
bool boolUp, boolDown, boolLeft, boolRight, boolMouseL;
sf::RenderWindow window;

void moveAll(){
	if (boolUp){
		cArray[0].move(0,-1.38889);
	}
	if (boolDown){
		cArray[0].move(0,1.38889);
	}
	if (boolRight){
		cArray[0].move(1.38889,0);
	}
	if (boolLeft){
		cArray[0].move(-1.38889,0);
	}
	if (boolMouseL){
		double x2 = sf::Mouse::getPosition(window).x - rArray[0].getPosition().x;
		double y2 = sf::Mouse::getPosition(window).y - rArray[0].getPosition().y;
		double dist = sqrt((x2*x2) + (y2*y2));
		rArray[0].move(x2/dist * 1.38889, y2/dist * 1.38889);
	}
	for (int i = 1; i < CIRCLES; i++){
		cArray[i].move(0,0.13889); //speed is frames wanted / FPS
	}
	for (int i = 1; i < RECTANGLES; i++){
		rArray[i].move(0.13889,0);
	}
}

void renderingThread(sf::RenderWindow* window){
	while (window->isOpen())
	{
		moveAll();
		window->clear(sf::Color::Black);
		for (int i = 0; i < CIRCLES; i++){
			window->draw(cArray[i]);
		}
		for (int i = 0; i < RECTANGLES; i++){
			window->draw(rArray[i]);
		}
		window->display();
	}
}

int main( void ){
	//initialize window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(sf::VideoMode(WINDOW_W, WINDOW_H), "Vectors & Circles", sf::Style::Default, settings);
	window.setFramerateLimit(FPS);
	window.setKeyRepeatEnabled(false);
	window.setActive(false); //deactivate main's openGL
	srand(time(NULL));
	int curr = 0;
	
	//colors
	color[0] = sf::Color::Red;
	color[1] = sf::Color::Green;
	color[2] = sf::Color::Blue;
	color[3] = sf::Color::Yellow;
	color[4] = sf::Color::Cyan;
	color[5] = sf::Color::White;

	//shapes
	for (int i = 0; i < CIRCLES; i++){
		cArray[i].setPosition(rand() % (WINDOW_W-1), rand() % (WINDOW_H-1));
		cArray[i].setRadius(30.0f);
		cArray[i].setFillColor(color[curr]);
		curr++;
		if (curr > CSIZE-1){
			curr = 0;
		}
	}
	for (int i = 0; i < RECTANGLES; i++){
		rArray[i].setPosition(rand() % (WINDOW_W-1), rand() % (WINDOW_H-1));
		rArray[i].setSize(sf::Vector2f(50.0f, 50.0f));
		rArray[i].setFillColor(color[curr]);
		curr++;
		if (curr > CSIZE-1){
			curr = 0;
		}
	}

	cArray[0].setOutlineThickness(10);
	cArray[0].setOutlineColor(sf::Color::Magenta);
	rArray[0].setOutlineThickness(10);
	rArray[0].setOutlineColor(sf::Color::Magenta);
	
	//thread
	sf::Thread thread(&renderingThread, &window);
	thread.launch();

	//events
	while( window.isOpen() )
	{
		sf::Event event;
		while (window.pollEvent(event)){
			switch(event.type){
				//closing window
				case sf::Event::Closed:
				window.close();
				break;

				//when keyboard is pressed
				case sf::Event::KeyPressed:
				switch(event.key.code){
					case sf::Keyboard::W:
					boolUp = true;
					break;
					case sf::Keyboard::A:
					boolLeft = true;
					break;
					case sf::Keyboard::S:
					boolDown = true;
					break;
					case sf::Keyboard::D:
					boolRight = true;
					break;
					case sf::Keyboard::Escape:
					window.close();
					break;
				}
				break;

				//when keyboard is released
				case sf::Event::KeyReleased:
				switch(event.key.code){
					case sf::Keyboard::W:
					boolUp = false;
					break;
					case sf::Keyboard::A:
					boolLeft = false;
					break;
					case sf::Keyboard::S:
					boolDown = false;
					break;
					case sf::Keyboard::D:
					boolRight = false;
					break;
				}
				break;

				//when mouse button is pressed
				case sf::Event::MouseButtonPressed:
				switch(event.mouseButton.button){
					case sf::Mouse::Left:
					boolMouseL = true;
					break;
				}
				break;

				case sf::Event::MouseButtonReleased:
				switch(event.mouseButton.button){
					case sf::Mouse::Left:
					boolMouseL = false;
					break;
				}
				break;
			}
		}
	}
	return 0;
}





