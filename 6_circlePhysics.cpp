#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>
#include <stdlib.h>

#define FPS 60
#define TIMESTEP 1.0f / 60.0f
#define FORCE 1000.0f
#define MASS 1.0f 
#define MASS_RECIP 1.0f
#define MASS2 0.5f
#define MASS2_RECIP 2.0f
#define WIDTH 800
#define HEIGHT 600
#define RADIUS 25.0f
#define ELASTICITY 1.0f
#define FRICTION 0.2f * TIMESTEP

using namespace std;
using namespace sf;

RenderWindow window;
int c, counter;
bool withFriction = false;
vector<CircleShape> circles;
vector<Vector2f> velocity, acceleration, position;

void initializeObjects(int a){
	//resize vectors
	circles.reserve(a);
	velocity.reserve(a);
	acceleration.reserve(a);
	position.reserve(a);
	
	//create circles and their valus
	for(int i = 0; i < a; i++){
		//make temp circle
		CircleShape tempCircle;
		tempCircle.setRadius(RADIUS);
		tempCircle.setFillColor(Color::Magenta);

		//make temp position
		Vector2f tempPos((i % 6) * 110 + 120, 0.f);
		Vector2f temp(0.f, 0.f);

		if(i < 6) tempPos.y = 75.0f;
		else if(i >= 6 && i < 12) tempPos.y = 165.0f;
		else if(i >= 12 && i < 18) tempPos.y = 255.0f;
		else if(i >= 18 && i < 24) tempPos.y = 345.0f;
		else if(i >= 24 && i < 30) tempPos.y = 435.0f;
		else if(i >= 30 && i < 36) tempPos.y = 525.0f;

		tempCircle.setOrigin(RADIUS, RADIUS);
		tempCircle.setPosition(tempPos);

		//push values to vectors
		velocity.push_back(temp);
		acceleration.push_back(temp);
		position.push_back(tempPos);
		circles.push_back(tempCircle);
	}
	circles[0].setFillColor(Color::White);
	//clearCollisionCheck();
}

void collisionResponse(int i, int j, Vector2f collisionNormal, float dist){
	Vector2f relVelocity((velocity[i].x - velocity[j].x), (velocity[i].y - velocity[j].y));
	float normalVelocity = (relVelocity.x * collisionNormal.x) + (relVelocity.y * collisionNormal.y);
	float impulse, mass1, mass2;

	if (normalVelocity < 0) { 
		if (i == 0){
			mass1 = MASS_RECIP;
			mass2 = MASS2_RECIP;
		}
		else if (j == 0){
			mass1 = MASS2_RECIP;
			mass2 = MASS_RECIP;
		}
		else {
			mass1 = MASS2_RECIP;
			mass2 = MASS2_RECIP;
		}
		impulse = -((1 + ELASTICITY)*normalVelocity) /
		((dist * dist) * (mass1 + mass2));
		velocity[i] += (impulse*mass1) * collisionNormal;
		velocity[j] -= (impulse*mass2) * collisionNormal;
	}
}

void checkCircleCollision(){
	for (int i = 0; i < c; i++){
		float dist;
		Vector2f temp(0.f, 0.f);
		for (int j = 0; j < c; j++){
			if (i != j){
				temp.x = position[i].x - position[j].x;
				temp.y = position[i].y - position[j].y;
				dist = sqrt((temp.x * temp.x) + (temp.y * temp.y));
				if (RADIUS*2 > dist) collisionResponse(i, j, temp, dist);
				else continue;
			}
		}
	}
}

void checkWallCollision(){
	for (int i = 0; i < c; i++){
		float cx = position[i].x;
		float cy = position[i].y;

		//check collision in walls
		if(cy + RADIUS > HEIGHT - 1) {
			velocity[i].y *= -ELASTICITY;
			position[i].y == HEIGHT - RADIUS;
		}
		if(cy - RADIUS < 0){
			velocity[i].y *= -ELASTICITY;
			position[i].y == RADIUS;
		}
		if(cx + RADIUS > WIDTH - 1){
			velocity[i].x *= -ELASTICITY;
			position[i].x == WIDTH - RADIUS;
		}
		if(cx - RADIUS < 0){
			velocity[i].x *= -ELASTICITY;
			position[i].y == RADIUS;
		}

		//move circles
		circles[i].setPosition(position[i]);
	}
}

void updatePosition(){
	for (int i = 0; i < c; i++){
		if (withFriction){
			if (i != 0) velocity[i] -= FRICTION * velocity[i] * MASS2_RECIP;
			else velocity[i] -= FRICTION * velocity[i] * MASS_RECIP;
		} 
		else {
			velocity[i] += acceleration[i] * TIMESTEP;
		}
		position[i] += (0.5f * acceleration[i] * TIMESTEP * TIMESTEP) + (velocity[i] * TIMESTEP);
		circles[i].setPosition(position[i]);
	}
}

int main(int argc, char** argv){
	//window stuff
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(VideoMode(WIDTH, HEIGHT), "Circle Physics 2", Style::Default, settings);
	window.setFramerateLimit(FPS);
	window.setKeyRepeatEnabled(false);
	window.setActive(false);

	//make circles if argument is 0 < x < 35
	c = atoi(argv[1]) + 1;
	if ((c-1) > 35 || (c-1) < 0){
		window.close();
		cout << "Only numbers between 0 and 35 are allowed." << endl;
	}
	else {
		initializeObjects(c);
	}

	//controls
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
					acceleration[0].y += -(FORCE * MASS);
					break;
					case Keyboard::A:
					acceleration[0].x += -(FORCE * MASS);
					break;
					case Keyboard::S:
					acceleration[0].y += FORCE * MASS;
					break;
					case Keyboard::D:
					acceleration[0].x += FORCE * MASS;
					break;
					case Keyboard::F:
					withFriction = !withFriction;
					cout << withFriction << endl;
					if (withFriction) circles[0].setFillColor(Color::Green);
					else circles[0].setFillColor(Color::White);
					break;
					case Keyboard::Escape:
					window.close();
					break;
				}
				break;
				case Event::KeyReleased:
				switch(event.key.code){
					case Keyboard::W:
					acceleration[0].y = 0;
					break;
					case Keyboard::A:
					acceleration[0].x = 0;
					break;
					case Keyboard::S:
					acceleration[0].y = 0;	
					break;
					case Keyboard::D:
					acceleration[0].x = 0;
					break;
				}
				break;
			}
		}

		//update positions first before checking for collisions
		updatePosition();
		checkCircleCollision();
		checkWallCollision();

		window.clear(Color::Black);
		for(const auto& circ : circles){
			window.draw(circ);
		}
		window.display();
	}
}