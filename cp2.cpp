#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

#define FPS 60
#define TIMESTEP 1.0f / FPS
#define WINDOW_W 800
#define WINDOW_H 600
#define SHIP_SIZE 20.0f
#define SPEED 175 * TIMESTEP
#define BRICKS 3000
#define ROW_OF_BRICKS 15
#define BRICKS_IN_ROW BRICKS / ROW_OF_BRICKS
#define BRICKS_SIZE BRICKS / BRICKS_IN_ROW
#define BULLETS 2000
#define BULLETS_SIZE 1.0f

using namespace std;
using namespace sf;

RenderWindow window;
RectangleShape spaceship;
bool u, d, l, r, threeBullets;
list<RectangleShape*> bricks;
list<RectangleShape*> bullets;
//do we make "moving bullets" and put bullets that are moving there?
//and remove them from bullets? tangina

//also, how will the grids work?
//will they just hold a combination of bullets and bricks?
//or will we have another 2 lists inside them haha kill me

void moveAll(){
	//movement
	if (u) spaceship.move(0, -SPEED);
	if (l) spaceship.move(-SPEED, 0);
	if (d) spaceship.move(0, SPEED);
	if (r) spaceship.move(SPEED, 0);

	//move everything in shot bullets
}

void moveBullets(float rotateLevel){

}

void shoot(){
	if (threeBullets){
		//get front -> pop three times
		//each will get teleported to infront of the space ship
		//1st is rotated -30degrees, one is not rotated, one is 30deg
	}
	else {
		//get front 
	}
}

bool isInsideGrid(RectangleShape r){
	//this is the function to know if we will draw or not
}

void checkCollision(){
	//per grid, then pairwise na lang
	//do u guys
}

void initializeObjects(){
	spaceship.setSize(sf::Vector2f(SHIP_SIZE, SHIP_SIZE));
	spaceship.setFillColor(Color::Magenta);
	spaceship.setOutlineThickness(1.5);
	spaceship.setOrigin(SHIP_SIZE/2, SHIP_SIZE/2);
	spaceship.setPosition(200, 200);

	//make boxes
	for (int i = 0; i < ROW_OF_BRICKS; i++){
		for (int j = 0; j < BRICKS_IN_ROW; j++){
			RectangleShape rect;
			RectangleShape* p = &rect;

			rect.setSize(Vector2f(BRICKS_SIZE, BRICKS_SIZE));
			rect.setFillColor(Color::White);
			rect.setOrigin(BRICKS_SIZE/2, BRICKS_SIZE/2);
			rect.setPosition(BRICKS_SIZE/2 + (j * BRICKS_SIZE),
				BRICKS_SIZE/2 + (i * BRICKS_SIZE));

			bricks.push_back(p);
		}
	}

	//make all bullets
	for (int i = 0; i < BULLETS; i++){
		RectangleShape rect;
		RectangleShape* p = &rect;

		rect.setSize(Vector2f(BULLETS_SIZE, BULLETS_SIZE));
		rect.setFillColor(Color::Magenta);
		rect.setOrigin(BULLETS_SIZE/2, BULLETS_SIZE/2);
		rect.setPosition(900, 900); //make invisible

		bullets.push_back(p);
	}
}

int main(){
	//create the rectangles and AABBs
	initializeObjects();

	//window stuff
	ContextSettings settings;
	settings.antialiasingLevel = 2;
	window.create(VideoMode(WINDOW_W, WINDOW_H), "Uniform Grid", Style::Default, settings);
	window.setFramerateLimit(FPS);
	window.setKeyRepeatEnabled(true);
	window.setActive(false);

	while(window.isOpen()){
		//close if user wants to
		Event event;
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
					u = true;
					break;
					case sf::Keyboard::A:
					l = true;
					break;
					case sf::Keyboard::S:
					d = true;
					break;
					case sf::Keyboard::D:
					r = true;
					break;
					case sf::Keyboard::Space:
					shoot();
					break;
					case sf::Keyboard::Q:
					threeBullets = !threeBullets;
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
					u = false;
					break;
					case sf::Keyboard::A:
					l = false;
					break;
					case sf::Keyboard::S:
					d = false;
					break;
					case sf::Keyboard::D:
					r = false;
					break;
				}
				break;
			}
		}

		//moveAll();
		window.clear(Color::Black);
		window.draw(spaceship);
		/*for(list<RectangleShape*>::iterator it = bricks.begin(); it != bricks.end(); ++it){
			window.draw((**it));
		}*/
		/*for(list<RectangleShape*>::iterator it = bullets.begin(); it != bullets.end(); ++it){
			window.draw((**it));
		}*/
		window.display();
	}
}
