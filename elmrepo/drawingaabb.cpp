#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <stdlib.h>

#define FPS 60
#define WIDTH 800
#define HEIGHT 600
#define TIMESTEP 1.0f / 60.0f
#define LIMIT 100
#define CONSTANT_TEST 65.0f

using namespace std;
using namespace sf;

RenderWindow window;
RectangleShape rArray[LIMIT];
RectangleShape AABB[LIMIT];
Vector2f minXMinY[LIMIT];
Vector2f minXMaxY[LIMIT];
Vector2f maxXMinY[LIMIT];
Vector2f maxXMaxY[LIMIT];
Vector2f colAABB[LIMIT];

int main(int argc, char *argv[]){
	float x = atoi(argv[1]);
	if(x <= 0 || x > 100){
		cout << "Cannot draw no rectangles or more than 100 rectangles!";
		return 0;
	}
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(VideoMode(WIDTH, HEIGHT), "Bounding Boxes", Style::Default, settings);
	window.setFramerateLimit(FPS);
/*	rArray[0].setSize(Vector2f(50.0f, 150.0f));	
	rArray[1].setSize(Vector2f(250.0f, 100.0f));
	rArray[2].setSize(Vector2f(120.0f, 300.0f));
	rArray[3].setSize(Vector2f(150.0f, 100.0f));
	rArray[4].setSize(Vector2f(100.0f, 100.0f));*/
	for(int i = 0; i < x; i++){
		rArray[i].setSize(Vector2f(CONSTANT_TEST, CONSTANT_TEST));
	}
	srand(time(NULL));
	for(int i = 0; i < x; i++){
		rArray[i].setOrigin(rArray[i].getSize().x / 2, rArray[i].getSize().y / 2);
	}
/*	rArray[0].setPosition(100, 200);
	rArray[1].setPosition(550, 300);
	rArray[2].setPosition(300, 325);
	rArray[3].setPosition(600, 100);
	rArray[4].setPosition(700, 450);*/
	for(int i = 0; i < x; i++){
		bool stillOverlapping;
		float randomXPos = (rand() % (WIDTH - 200)) + 100;
		float randomYPos = (rand() % (HEIGHT - 267)) + 100;
		rArray[i].setPosition(randomXPos, randomYPos);
		Vector2f minPointA = Vector2f((rArray[i].getPosition().x - (rArray[i].getSize().x / 2)), (rArray[i].getPosition().y - (rArray[i].getPosition().y / 2)));
		Vector2f diff;
		for(int j = i-1; j > -1; j--){
			//assuming that a rectangle is already made
			Vector2f minPointB = Vector2f((rArray[j].getPosition().x - (rArray[j].getSize().x / 2)), (rArray[j].getPosition().y - (rArray[j].getPosition().y / 2)));
			diff = minPointA - minPointB;
			if(diff.x > CONSTANT_TEST || -diff.x > CONSTANT_TEST || diff.y > CONSTANT_TEST || -diff.y > CONSTANT_TEST){
				stillOverlapping = false;
			}else{
				stillOverlapping = true;
				while(stillOverlapping){
					float newRandomXPos = (rand() % (WIDTH/2)) + 100;
					float newRandomYPos = (rand() % (HEIGHT/2)) + 100;	
					rArray[i].setPosition(newRandomXPos, newRandomYPos);
					Vector2f newMinPointA =  Vector2f((rArray[i].getPosition().x - (rArray[i].getSize().x / 2)), (rArray[i].getPosition().y - (rArray[i].getPosition().y / 2)));
					Vector2f diff2 = newMinPointA - minPointB;
					if(diff2.x > CONSTANT_TEST || -diff2.x > CONSTANT_TEST || diff2.y > CONSTANT_TEST || -diff2.y > CONSTANT_TEST){
						stillOverlapping = false;
					}else{
						cout << "Meron pa rin" << endl;
						continue;
					}
				}
			}
		}
	}
	for(int i = 0; i < x; i++){ //getting the original positions of the points of the objects and setting up AABBs
		//setting up AABBs
		AABB[i].setFillColor(Color::Transparent);
		AABB[i].setOutlineColor(Color::Magenta);
		AABB[i].setOutlineThickness(1.5f);
		//getting original positions of points for AABB drawing
		minXMinY[i] = Vector2f((rArray[i].getPosition().x - (rArray[i].getSize().x / 2)), (rArray[i].getPosition().y - (rArray[i].getSize().y / 2)));
		minXMaxY[i] = Vector2f((rArray[i].getPosition().x - (rArray[i].getSize().x / 2)), (rArray[i].getPosition().y + (rArray[i].getSize().y / 2)));
		maxXMinY[i] = Vector2f((rArray[i].getPosition().x + (rArray[i].getSize().x / 2)), (rArray[i].getPosition().y - (rArray[i].getSize().y / 2)));
		maxXMaxY[i] = Vector2f((rArray[i].getPosition().x + (rArray[i].getSize().x / 2)), (rArray[i].getPosition().y + (rArray[i].getSize().y / 2)));
	}
	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			switch(event.type){
				case Event::Closed:
				window.close();
				break;
				case Event::KeyPressed:
				switch(event.key.code){
					case Keyboard::Escape:
					window.close();
					break;
				}
				break;
			}
		}
/*		for(int i = 0; i < x; i++){ //rotating objects
			rArray[i].rotate(10 * TIMESTEP * (i + rand() % 5));
		} */
		for(int i = 0; i < x; i++){//drawing AABBs and setting up for collision
			//getting the angle functions
			float cFunc = abs(cos(rArray[i].getRotation() * M_PI/180));
			float sFunc = abs(sin(rArray[i].getRotation() * M_PI/180));
			//getting AABB corners using the angle functions and original position of the points of the objects
			Vector2f upperLeft = Vector2f((((minXMinY[i].x - rArray[i].getPosition().x) * cFunc) - ((minXMinY[i].y - rArray[i].getPosition().y) * sFunc)) + rArray[i].getPosition().x, 
				(((minXMinY[i].x - rArray[i].getPosition().x) * sFunc) + ((minXMinY[i].y - rArray[i].getPosition().y) * cFunc)) + rArray[i].getPosition().y);
			Vector2f upperRight = Vector2f((((maxXMinY[i].x - rArray[i].getPosition().x) * cFunc) - ((maxXMinY[i].y - rArray[i].getPosition().y) * sFunc)) + rArray[i].getPosition().x, 
				(((maxXMinY[i].x - rArray[i].getPosition().x) * sFunc) + ((maxXMinY[i].y - rArray[i].getPosition().y) * cFunc)) + rArray[i].getPosition().y);
			Vector2f lowerLeft = Vector2f((((minXMaxY[i].x - rArray[i].getPosition().x) * cFunc) - ((minXMaxY[i].y - rArray[i].getPosition().y) * sFunc)) + rArray[i].getPosition().x, 
				(((minXMaxY[i].x - rArray[i].getPosition().x) * sFunc) + ((minXMaxY[i].y - rArray[i].getPosition().y) * cFunc)) + rArray[i].getPosition().y);
			Vector2f lowerRight = Vector2f((((maxXMaxY[i].x - rArray[i].getPosition().x) * cFunc) - ((maxXMaxY[i].y - rArray[i].getPosition().y) * sFunc)) + rArray[i].getPosition().x, 
				(((maxXMaxY[i].x - rArray[i].getPosition().x) * sFunc) + ((maxXMaxY[i].y - rArray[i].getPosition().y) * cFunc)) + rArray[i].getPosition().y);
			//determining the minimum and maximum x and y points of the AABB
			float aabbMinX = min(min(abs(upperLeft.x), abs(upperRight.x)), min(abs(lowerLeft.x), abs(lowerRight.x)));
			float aabbMinY = min(min(abs(upperLeft.y), abs(upperRight.y)), min(abs(lowerLeft.y), abs(lowerRight.y)));
			float aabbMaxX = max(max(abs(upperLeft.x), abs(upperRight.x)), max(abs(lowerLeft.x), abs(lowerRight.x)));
			float aabbMaxY = max(max(abs(upperLeft.y), abs(upperRight.y)), max(abs(lowerLeft.y), abs(lowerRight.y)));
			//setting the size of AABB, setting origin to center based on size, and setting position based on the position of the rectangle object
			float getWidth = aabbMaxX - aabbMinX;
			float getHeight = aabbMaxY - aabbMinY;
			AABB[i].setSize(Vector2f(getWidth, getHeight));
			AABB[i].setOrigin(AABB[i].getSize().x / 2, AABB[i].getSize().y / 2);
			AABB[i].setPosition(rArray[i].getPosition());
			//setting up for AABB collision using min-width method
			colAABB[i] = Vector2f(aabbMinX, aabbMinY);
			rArray[i].setFillColor(Color::Blue);
		}
		for(int i = 0; i < x; i++){//collision detection
			Vector2f difference;
			for(int j = 0; j < x; j++){
				if(i != j){
					difference = colAABB[i] - colAABB[j];
					if(difference.x > AABB[j].getSize().x || -difference.x > AABB[i].getSize().x || difference.y > AABB[j].getSize().y || -difference.y > AABB[i].getSize().y){
						continue;
					}else{
						rArray[i].setFillColor(Color::Yellow);
						rArray[j].setFillColor(Color::Yellow);
					}
				}
			}
		}
		window.clear(Color::Black);
		for(int i = 0; i < x; i++){
			window.draw(rArray[i]);
		}
		for(int i = 0; i < x; i++){
			window.draw(AABB[i]);
		}
		window.display();
	}
}
