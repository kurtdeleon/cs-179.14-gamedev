#include <SFML/Graphics.hpp>
#include <iostream>

#define FPS 144
#define CSIZE 6
#define CIRCLES 60
#define RECTANGLES 40
#define WINDOW_H 480
#define WINDOW_W 320
#define SPEED 20

using namespace std;

sf::Color color[CSIZE];
sf::CircleShape cArray[CIRCLES];
sf::RectangleShape rArray[RECTANGLES];
int curr = 0;

void moveAll(){
	for (int i = 0; i < CIRCLES; i++){
		cArray[i].move(0,0.13889); //speed is frames wanted / FPS
	}
	for (int i = 0; i < RECTANGLES; i++){
		rArray[i].move(0.13889,0);
	}
}

void renderingThread(sf::RenderWindow* window){
	while (window->isOpen())
	{
		window->clear(sf::Color::Black);
		for (int i = 0; i < CIRCLES; i++){
			window->draw(cArray[i]);
		}
		for (int i = 0; i < RECTANGLES; i++){
			window->draw(rArray[i]);
		}
		window->display();
		moveAll();
	}
}

int main( void ){
	//initialize window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;
	sf::RenderWindow window(sf::VideoMode(WINDOW_H, WINDOW_W), "Vectors & Circles", sf::Style::Default, settings);
	window.setFramerateLimit(FPS);
	window.setActive(false); //deactivate main's openGL
	srand(time(NULL));
	
	//colors
	color[0] = sf::Color::Red;
	color[1] = sf::Color::Green;
	color[2] = sf::Color::Blue;
	color[3] = sf::Color::Yellow;
	color[4] = sf::Color::Cyan;
	color[5] = sf::Color::White;

	//shapes
	for (int i = 0; i < CIRCLES; i++){
		cArray[i].setPosition(rand() % (WINDOW_H-1), rand() % (WINDOW_W-1));
		cArray[i].setRadius(30.0f);
		cArray[i].setFillColor(color[curr]);
		curr++;
		if (curr > CSIZE-1){
			curr = 0;
		}
	}
	for (int i = 0; i < RECTANGLES; i++){
		rArray[i].setPosition(rand() % (WINDOW_H-1), rand() % (WINDOW_W-1));
		rArray[i].setSize(sf::Vector2f(50.0f, 50.0f));
		rArray[i].setFillColor(color[curr]);
		curr++;
		if (curr > CSIZE-1){
			curr = 0;
		}
	}
	
	//thread
	sf::Thread thread(&renderingThread, &window);
	thread.launch();
	//events
	while( window.isOpen() )
	{
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed){
				window.close();
			}
		}
	}
	return 0;
}

