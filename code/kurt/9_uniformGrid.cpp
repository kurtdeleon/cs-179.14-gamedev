#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <math.h>
#include <vector>

#define FPS 60
#define TIMESTEP 1.0f / FPS
#define WINDOW_W 800
#define WINDOW_H 600
#define SHIP_SIZE 20.0f
#define SPEED 175 * TIMESTEP
#define BULLET_SPEED SPEED / 2
#define BRICKS 3000
#define ROW_OF_BRICKS 30
#define BRICKS_IN_ROW 100
#define BRICKS_SIZE 8.0f
#define BULLETS 2000
#define BULLETS_SIZE 4.0f
#define PI M_PI / 180
#define GRIDS 300
#define ROW_OF_GRIDS 15
#define GRIDS_IN_ROW 20
#define GRIDS_SIZE 40.0f

using namespace std;
using namespace sf;

RenderWindow window;
RectangleShape spaceship;
bool u, d, l, r, threeBullets, isShooting;
list<RectangleShape*> bricks, bulletsPooled, bulletsShot;
FloatRect gridGuides[GRIDS];
list<vector<vector<RectangleShape*>>> grid;

/* 
main idea is to get that pointer, pop (delete) it 
from the bulletsPooled list, and then push it to the
bulletsShot list.
*/
void shoot(){
	if (threeBullets){
		if (bulletsPooled.size() >= 3){
			RectangleShape* p;

			p = bulletsPooled.front();
			bulletsPooled.pop_front();
			p->setPosition(spaceship.getPosition().x, spaceship.getPosition().y - 9);
			bulletsShot.push_back(p);

			p = bulletsPooled.front();
			bulletsPooled.pop_front();
			p->setPosition(spaceship.getPosition().x - 5, spaceship.getPosition().y - 9);
			p->rotate(20);
			bulletsShot.push_back(p);

			p = bulletsPooled.front();
			bulletsPooled.pop_front();
			p->setPosition(spaceship.getPosition().x + 5, spaceship.getPosition().y - 9);
			p->rotate(-20);
			bulletsShot.push_back(p);
		}
	}
	else {
		if (!bulletsPooled.empty()){
			RectangleShape* p = bulletsPooled.front();
			bulletsPooled.pop_front();

			p->setPosition(spaceship.getPosition().x, spaceship.getPosition().y - 9);
			bulletsShot.push_back(p);
		}
	}
}

void moveAll(){
	//movement
	if (u) spaceship.move(0, -SPEED);
	if (l) spaceship.move(-SPEED, 0);
	if (d) spaceship.move(0, SPEED);
	if (r) spaceship.move(SPEED, 0);
	if (isShooting) shoot();

	//move everything in shot bullets
	if(!bulletsShot.empty()){
		for(list<RectangleShape*>::iterator b = bulletsShot.begin(); b != bulletsShot.end(); ++b){
			float ang = (*b)->getRotation() * PI;
			(*b)->move(-BULLET_SPEED * sin(ang), -BULLET_SPEED * cos(ang));
		}
	}
}

bool isInsideWindow(RectangleShape r){
	if (r.getPosition().x <= -2 || r.getPosition().x >= WINDOW_W + 2 ||
		r.getPosition().y <= -2 || r.getPosition().y >= WINDOW_H + 2){
		return false;
	}
	return true;
}

void relocateBullet(RectangleShape* p){
	p->setSize(Vector2f(BULLETS_SIZE, BULLETS_SIZE));
	p->setFillColor(Color::White);
	p->setOrigin(BULLETS_SIZE/2, BULLETS_SIZE/2);
	p->setPosition(900, 900);
	bulletsPooled.push_back(p);
}

/*
.erase() returns the pointer to the next element in the list
if you just delete to whatever ur pointing, pwede maging invalid
yung iterator. fucking took me a while to solve lmao
*/
void updateBullets(){
	if (!bulletsShot.empty()){
		for(list<RectangleShape*>::iterator b = bulletsShot.begin(); b != bulletsShot.end();){
			if (!isInsideWindow(**b)) {
				relocateBullet(*b);
				b = bulletsShot.erase(b);
			}
			else {
				++b;
			}
		}
	}

	int counter = 0;
	for(list<vector<vector<RectangleShape*>>>::iterator g = grid.begin(); g != grid.end(); ++g){
		(*g)[1].clear(); // HAHA IM FUCKING RETARDED
		for(list<RectangleShape*>::iterator b = bulletsShot.begin(); b != bulletsShot.end(); ++b){
			if (gridGuides[counter].intersects((**b).getGlobalBounds())) {
				(*g)[1].push_back(*b);
			}
		}
		counter++;
	}
}

void initializeGrids(){
	int counter = 0;
	for(list<vector<vector<RectangleShape*>>>::iterator g = grid.begin(); g != grid.end(); ++g){
		for(list<RectangleShape*>::iterator b = bricks.begin(); b != bricks.end(); ++b){
			if (gridGuides[counter].intersects((**b).getGlobalBounds())) {
				(*g)[0].push_back(*b);
			}
		}
		counter++;
	}

	/*counter = 0;
	for(list<vector<vector<RectangleShape*>>>::iterator g = grid.begin(); g != grid.end(); ++g){
		cout << counter << ": " << (*g)[0].size() << endl;
		counter++;
	}*/
	
}

void cleanUp(){
	bricks.remove(NULL);
	bulletsShot.remove(NULL);
}


void checkCollisionPerGrid(){
	bool hasIncremented;
	for(list<vector<vector<RectangleShape*>>>::iterator g = grid.begin(); g != grid.end(); ++g){
		if (!(*g)[0].empty() && !(*g)[1].empty()){
			for(vector<RectangleShape*>::iterator br = (*g)[0].begin(); br != (*g)[0].end(); ++br){
				for(vector<RectangleShape*>::iterator bu = (*g)[1].begin(); bu != (*g)[1].end(); ++bu){
					if ((**br).getGlobalBounds().intersects((**bu).getGlobalBounds())){
						(*br)->setPosition(900, 900);
					}
				}
			}
		}
	}
}

void initializeObjects(){
	threeBullets = false;
	isShooting = false;
	spaceship.setSize(sf::Vector2f(SHIP_SIZE, SHIP_SIZE));
	spaceship.setFillColor(Color::White);
	spaceship.setOrigin(SHIP_SIZE/2, SHIP_SIZE/2);
	spaceship.setPosition(WINDOW_H*2/3, WINDOW_W/2);

	//make boxes
	for (int i = 0; i < ROW_OF_BRICKS; i++){
		for (int j = 0; j < BRICKS_IN_ROW; j++){
			RectangleShape* p = new RectangleShape();

			p->setSize(Vector2f(BRICKS_SIZE, BRICKS_SIZE));
			p->setOrigin(BRICKS_SIZE/2, BRICKS_SIZE/2);
			p->setFillColor(Color::Magenta);
			//p->setOutlineThickness(1.0);
			//p->setOutlineColor(Color::Black);
			p->setPosition(BRICKS_SIZE/2 + (j * BRICKS_SIZE),
				BRICKS_SIZE/2 + (i * BRICKS_SIZE));

			bricks.push_back(p);
		}
	}

	//make grid
	Vector2f size = Vector2f(GRIDS_SIZE, GRIDS_SIZE);
	int counter = 0;
	for (int i = 0; i < ROW_OF_GRIDS; i++){
		for (int j = 0; j < GRIDS_IN_ROW; j++){
			vector<vector<RectangleShape*>> mainVec;
			vector<RectangleShape*> v1, v2;
			mainVec.push_back(v1);
			mainVec.push_back(v2);
			grid.push_back(mainVec);

			//make grid guides
			Vector2f pos = Vector2f(GRIDS_SIZE * j, GRIDS_SIZE * i);
			gridGuides[counter] = FloatRect(pos, size);
			counter++; 
		}
	}

	//make all bullets
	for (int i = 0; i < BULLETS; i++) { 
		RectangleShape* r = new RectangleShape();
		relocateBullet(r);
	}

	initializeGrids();
}

int main(){
	//create the rectangles and AABBs
	initializeObjects();

	//window stuff
	ContextSettings settings;
	settings.antialiasingLevel = 2;
	window.create(VideoMode(WINDOW_W, WINDOW_H), "Uniform Grids", Style::Default, settings);
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
					isShooting = true; 
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
					case sf::Keyboard::Space:
					isShooting = false;
					break;
				}
				break;
			}
		}

		moveAll();
		updateBullets();
		checkCollisionPerGrid();
		//cleanUp();
		window.clear(Color::Black);
		window.draw(spaceship);
		for(list<RectangleShape*>::iterator it = bulletsShot.begin(); it != bulletsShot.end(); ++it){ window.draw(**it); }
		for(list<RectangleShape*>::iterator it = bricks.begin(); it != bricks.end(); ++it){ window.draw(**it); }
		//cout << bulletsShot.size() << " " << bulletsPooled.size() << endl; //tester
		//cout << grid.size() << endl;
		window.display();
	}
}