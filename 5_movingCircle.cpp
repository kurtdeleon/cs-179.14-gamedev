#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <SFML/System/Vector2.hpp>

#define FPS 144
#define CSIZE 40.0f
#define WINDOW_H 720
#define WINDOW_W 1280
#define SPEED 20
#define MASS 0.01

using namespace std;

sf::RenderWindow window;
sf::CircleShape circle;
sf::Vector2f vel, accel;
float cx, cy, friction;
bool frictionOn;

void checkBounce(){
	cx = circle.getPosition().x;
	cy = circle.getPosition().y;

	if (cy + (CSIZE*2) > WINDOW_H || cy < 0){
		vel.y *= -1;
	}
	if (cx + (CSIZE*2) > WINDOW_W || cx < 0) {
		vel.x *= -1;
	}
}

void moveCircle(){
	circle.move(vel);
}

void updateSpeed(){
	vel.x += accel.x;
	vel.y += accel.y;
	
	if (frictionOn){
		vel.x = vel.x - (friction*vel.x)*MASS;
		vel.y = vel.y - (friction*vel.y)*MASS;
	}
}

void renderingThread(sf::RenderWindow* window){
	while (window->isOpen())
	{
		updateSpeed();
		moveCircle();
		checkBounce();
		window->clear(sf::Color::Black);
		window->draw(circle);
		window->display();
	}
}

int main( void ){
	//initialize window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(sf::VideoMode(WINDOW_W, WINDOW_H), "Moving Circle", sf::Style::Default, settings);
	window.setFramerateLimit(FPS);
	window.setKeyRepeatEnabled(false);
	window.setActive(false); //deactivate main's openGL

	//variables
	friction = 0.2;
	frictionOn = false;

	//circle
	circle.setRadius(CSIZE);
	circle.setFillColor(sf::Color::Red);
	circle.setPosition(WINDOW_W/2, WINDOW_H/2);
	
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
					accel.y = -0.1;
					break;

					case sf::Keyboard::A:
					accel.x = -0.1;
					break;

					case sf::Keyboard::S:
					accel.y = 0.1;
					break;

					case sf::Keyboard::D:
					accel.x = 0.1;
					break;

					case sf::Keyboard::F:
					frictionOn = !frictionOn;
					if (frictionOn){
						circle.setFillColor(sf::Color::White);
					}
					else {
						circle.setFillColor(sf::Color::Red);
					}
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
					accel.y = 0;
					break;

					case sf::Keyboard::A:
					accel.x = 0;
					break;

					case sf::Keyboard::S:
					accel.y = 0;
					break;
					
					case sf::Keyboard::D:
					accel.x = 0;
					break;
				}
				break;
			}
		}
	}
	return 0;
}





