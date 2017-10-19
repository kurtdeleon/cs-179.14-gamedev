#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>

#define FPS 60
#define TIMESTEP 1.0f / FPS
#define WIDTH 800
#define HEIGHT 600
#define OBJECTS 5

using namespace std;
using namespace sf;

RenderWindow window;
RectangleShape rectangles[OBJECTS];
RectangleShape AABB[OBJECTS];
Vector2f ptOne[OBJECTS];
Vector2f ptTwo[OBJECTS];
Vector2f minAABB[OBJECTS];

/*********************
  ptOne
    A-------------+
    |             |
    |             |
    |             |
    B-------------+
  ptTwo

*********************/

void checkCollision(){
	for (int i = 0; i < OBJECTS; i++){
		Vector2f diff;
		for (int j = 0; j < OBJECTS; j++){
			if (i != j){
				diff.x = minAABB[i].x - minAABB[j].x;
				diff.y = minAABB[i].y - minAABB[j].y;
				if (diff.x > AABB[j].getSize().x || diff.y > AABB[j].getSize().y ||
					-diff.x > AABB[i].getSize().x || -diff.y > AABB[i].getSize().y){
					continue;
				}
				else {
					rectangles[i].setFillColor(Color::Red);
					rectangles[j].setFillColor(Color::Red);
				}
			}
		}
	}
}

void initializeObjects(){
	//create Rectangles
	rectangles[0].setSize(Vector2f(70, 100));
	rectangles[1].setSize(Vector2f(90, 300));
	rectangles[2].setSize(Vector2f(10, 550));
	rectangles[3].setSize(Vector2f(260, 140));
	rectangles[4].setSize(Vector2f(100, 240));

	for (int i = 0; i < OBJECTS; i++){
		//set color, origin, and rotation
		rectangles[i].setFillColor(Color::White);
		rectangles[i].setOrigin(rectangles[i].getSize().x / 2, 
			rectangles[i].getSize().y / 2);
		rectangles[i].setRotation(0);
	}
	//set position (center point)
	rectangles[0].setPosition(105, 105);
	rectangles[1].setPosition(285, 260);
	rectangles[2].setPosition(400, 300);
	rectangles[3].setPosition(600, 165);
	rectangles[4].setPosition(570, 390);
	
	copy(begin(rectangles), end(rectangles), begin(AABB));
	for (int i = 0; i < OBJECTS; i++){
		//fill in AABB array
		AABB[i].setFillColor(Color::Transparent);
		AABB[i].setOutlineColor(Color::Magenta);
		AABB[i].setOutlineThickness(1.5);

		//fill in top/bot arrays
		ptOne[i].x = rectangles[i].getPosition().x - (rectangles[i].getSize().x / 2);
		ptOne[i].y = rectangles[i].getPosition().y - (rectangles[i].getSize().y / 2);
		ptTwo[i].x = rectangles[i].getPosition().x - (rectangles[i].getSize().x / 2);
		ptTwo[i].y = rectangles[i].getPosition().y + (rectangles[i].getSize().y / 2);
	}
}

void rotateObjects(){
	//rotate objects
	for (int i = 0; i < OBJECTS; i++) {
		rectangles[i].rotate(9 * (i+1) * TIMESTEP);
	}
}

void drawAABB(){
	Vector2f rotOne, rotTwo, size;
	for (int i = 0; i < OBJECTS; i++) {
		//calculate sin/cos * rotation of object
		float sinAngle = abs(sin(rectangles[i].getRotation() * M_PI/180));
		float cosAngle = abs(cos(rectangles[i].getRotation() * M_PI/180));

		//calculate for new rotated position values
		rotOne.x = ((ptOne[i].x - rectangles[i].getPosition().x) * cosAngle) 
		- ((ptOne[i].y - rectangles[i].getPosition().y) * sinAngle) + rectangles[i].getPosition().x;
		rotOne.y = ((ptOne[i].x - rectangles[i].getPosition().x) * sinAngle) 
		+ ((ptOne[i].y - rectangles[i].getPosition().y) * cosAngle) + rectangles[i].getPosition().y;
		rotTwo.x = ((ptTwo[i].x - rectangles[i].getPosition().x) * cosAngle) 
		- ((ptTwo[i].y - rectangles[i].getPosition().y) * sinAngle) + rectangles[i].getPosition().x;
		rotTwo.y = ((ptTwo[i].x - rectangles[i].getPosition().x) * sinAngle) 
		+ ((ptTwo[i].y - rectangles[i].getPosition().y) * cosAngle) + rectangles[i].getPosition().y;
		
		//determine the size of the AABB
		size.x = (AABB[i].getPosition().x - min(abs(rotOne.x), abs(rotTwo.x))) * 2;
		size.y = (AABB[i].getPosition().y - min(abs(rotOne.y), abs(rotTwo.y))) * 2;

		//set the size, set origin based on size, then setposition to center
		AABB[i].setSize(size);
		AABB[i].setOrigin(AABB[i].getSize().x / 2, 
			AABB[i].getSize().y / 2);
		AABB[i].setPosition(rectangles[i].getPosition());

		minAABB[i].x = AABB[i].getPosition().x - (AABB[i].getSize().x / 2);
		minAABB[i].y = AABB[i].getPosition().y - (AABB[i].getSize().y / 2);

		//before checking for collisions, reset the colors first!
		rectangles[i].setFillColor(Color::White);
	}
}

int main(){
	//window stuff
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(VideoMode(WIDTH, HEIGHT), "Drawing AABBs", Style::Default, settings);
	window.setFramerateLimit(FPS);
	window.setKeyRepeatEnabled(false);
	window.setActive(false);

	//create the rectangles and AABBs
	initializeObjects();

	while(window.isOpen()){
		//close if user wants to
		Event event;
		while(window.pollEvent(event)){
			if (event.type == sf::Event::Closed) window.close();
			if ((event.type == sf::Event::KeyPressed) && 
				(event.key.code == sf::Keyboard::Escape))
				window.close();
		}

		rotateObjects();
		drawAABB();
		checkCollision();

		window.clear(Color::Black);
		for(const auto& rect : rectangles) { window.draw(rect); }
		for(const auto& aabb : AABB) { window.draw(aabb); }
		window.display();
	}
}
