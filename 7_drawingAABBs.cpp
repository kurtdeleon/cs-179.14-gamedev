#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

#define FPS 60
#define TIMESTEP 1.0f / FPS
#define WINDOW_W 1600
#define WINDOW_H 900

using namespace std;
using namespace sf;

RenderWindow window;
int OBJECTS;
vector<RectangleShape> rectangles, AABB;
vector<Vector2f> ptOne, ptTwo, minAABB;

/*********************
  ptOne
    A-------------+
    |             |
    |             |
    |             |
    B-------------+
  ptTwo

*********************/

//normal check collision
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

//check specific rectangle's collision versus other rectangles
bool isColliding(int a) {
	Vector2f diff, min1, min2;
	min1.x = rectangles[a].getPosition().x - (rectangles[a].getSize().x / 2);
	min1.y = rectangles[a].getPosition().y - (rectangles[a].getSize().y / 2);

	//check if rect[a] is colliding with other rects!
	//if colliding, method returns 'true' and this gets called again by initialCheckCollion
	//else, it returns 'false' and stops the loop
	for (int i = 0; i < OBJECTS; i++){
		if (a != i){
			min2.x = rectangles[i].getPosition().x - (rectangles[i].getSize().x / 2);
			min2.y = rectangles[i].getPosition().y - (rectangles[i].getSize().y / 2);
			diff = min1 - min2;
			if (diff.x > rectangles[i].getSize().x || diff.y > rectangles[i].getSize().y || -diff.x > rectangles[a].getSize().x || -diff.y > rectangles[a].getSize().y){
				continue;
			}
			else {
				return true;
			}
		}
	}
	return false;
}

//initial checking of collision
void initialCheckCollision(){
	int counter = 0;
	//checks collision for all objects
	//if isColliding() returns 'true' (meaning it does collide), the position gets reset
	for (int i = 0; i < OBJECTS; i++){
		while (isColliding(i)){
			rectangles[i].setPosition(rand() % (WINDOW_W - 200) + 100, rand() % (WINDOW_H - 200) + 100);			
		}
	}
}

void initializeObjects(int a){
	//resize the vectors
	rectangles.resize(a);
	AABB.resize(a);
	ptOne.resize(a);
	ptTwo.resize(a);
	minAABB.resize(a);

	//create Rectangles
	Vector2f max;
	for (int i = 0; i < OBJECTS; i++){
		//create Rectangles while checking for collisions
		//if (i == 0) rectangles[i].setSize(Vector2f(10, 550));
		/*if (i % 2 == 0) rectangles[i].setSize(Vector2f(80, 150 - (i * 7)));
		else rectangles[i].setSize(Vector2f(150 - (i * 7), 80));*/

		rectangles[i].setSize(
			Vector2f(
			(rand() % 180) + 50,
			(rand() % 180) + 50)
			);



		//set color, origin, and rotation
		rectangles[i].setFillColor(Color::White);
		rectangles[i].setOrigin(rectangles[i].getSize().x / 2, rectangles[i].getSize().y / 2);
		rectangles[i].setRotation(0);

		//set the position
		rectangles[i].setPosition(rand() % (WINDOW_W - 200) + 100, rand() % (WINDOW_H - 200) + 100);
	}

	//check initial overlapping
	initialCheckCollision();

	//set position (center point)
	AABB = rectangles;
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
		rectangles[i].rotate(6 * (i+1) * TIMESTEP);
	}
}

void drawAABB(){
	Vector2f rotOne, rotTwo, size;
	for (int i = 0; i < OBJECTS; i++) {
		//calculate sin/cos * rotation of object
		float sinAngle = abs(sin(rectangles[i].getRotation() * M_PI/180));
		float cosAngle = abs(cos(rectangles[i].getRotation() * M_PI/180));

		//calculate for new rotated position values
		//https://gamedev.stackexchange.com/a/86784
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

		//get the new minimum values of AABB
		minAABB[i].x = AABB[i].getPosition().x - (AABB[i].getSize().x / 2);
		minAABB[i].y = AABB[i].getPosition().y - (AABB[i].getSize().y / 2);

		//before checking for collisions, reset the colors first!
		rectangles[i].setFillColor(Color::White);
	}
}

int main(int argc, char** argv){
	//window stuff
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(VideoMode(WINDOW_W, WINDOW_H), "Drawing AABBs", Style::Default, settings);
	window.setFramerateLimit(FPS);
	window.setKeyRepeatEnabled(false);
	window.setActive(false);
	srand(time(NULL));

	//create the rectangles and AABBs
	OBJECTS = atoi(argv[1]);
	if (OBJECTS > 15 || OBJECTS < 1){
		cout << "Only numbers between 1 and 15 are allowed." << endl;
		window.close();
	}
	else {
		initializeObjects(OBJECTS);
	}

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