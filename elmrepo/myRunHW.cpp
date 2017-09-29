#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#define SLEEPMILLI 1000.0f / 144.0f //sort of FPS
#define TIMESTEP SLEEPMILLI / 1000.0f //based on slides
#define FORCE 5000.0f * TIMESTEP //slides have 10000.0f
#define MASS 100.0f //can be changed
#define WIDTH 1366 //can be changed
#define HEIGHT 768 //can be changed
#define RADIUS 30.0f //can be changed

using namespace std;
using namespace sf;

RenderWindow window;
CircleShape circle;
Vector2f velocity, acceleration;
float friction = 0.2f, getTime = TIMESTEP; //getting time of the frame
bool withFriction = false;

void bounceCheck(){
	if(circle.getPosition().y + (RADIUS * 2) > HEIGHT - 1 || circle.getPosition().y < 0) velocity.y = -1.0f * velocity.y;
	if(circle.getPosition().x + (RADIUS * 2) > WIDTH - 1 || circle.getPosition().x < 0) velocity.x = -1.0f * velocity.x;
}

void updateVelocity(){
	velocity = velocity + (acceleration * getTime); // v = v0 + (a*t)
	if(withFriction) velocity = velocity - ((friction * velocity) / MASS); // v = v0 - ((f*v0) / m)
}

void moveCircle(){circle.move(velocity);}

void renderThread(RenderWindow* window){
	while(window->isOpen()){
		bounceCheck();
		updateVelocity();
		moveCircle();
		window->clear(Color::Black);
		window->draw(circle);
		window->display();
	}
}

int main(){
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(VideoMode(WIDTH, HEIGHT), "Circle Physics", Style::Default, settings);
	window.setKeyRepeatEnabled(false);
	window.setActive(false);
	circle.setRadius(RADIUS);
	circle.setFillColor(Color::Magenta);
	circle.setPosition(WIDTH/2, HEIGHT/2);
	Thread thread(&renderThread, &window);
	thread.launch();
	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			switch(event.type){
				case Event::Closed:
				window.close();
				break;
				case Event::KeyPressed:
				switch(event.key.code){
					case Keyboard::W:
					acceleration.y = -FORCE/MASS;
					break;
					case Keyboard::A:
					acceleration.x = -FORCE/MASS;
					break;
					case Keyboard::S:
					acceleration.y = FORCE/MASS;
					break;
					case Keyboard::D:
					acceleration.x = FORCE/MASS;
					break;
					case Keyboard::F:
					withFriction = !withFriction;
					if(withFriction) circle.setFillColor(Color::Blue);
					else circle.setFillColor(Color::Magenta);
					break;
					case Keyboard::Escape:
					window.close();
					break;
				}
				break;
				case Event::KeyReleased:
				switch(event.key.code){
					case Keyboard::W:
					acceleration.y = 0;
					break;
					case Keyboard::A:
					acceleration.x = 0;
					break;
					case Keyboard::S:
					acceleration.y = 0;
					break;
					case Keyboard::D:
					acceleration.x = 0;
					break;
				}
				break;
			}
		}
	}
}
