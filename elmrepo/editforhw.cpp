#include <SFML/Graphics.hpp>
#include <iostream>

#define FPS 60
#define CSIZE 6
#define CIRCLES 60
#define RECTANGLES 40
#define WINDOW_H 800
#define WINDOW_W 600

using namespace std;
using namespace sf;

sf::Color color[CSIZE];
sf::CircleShape cArray[CIRCLES];
sf::RectangleShape rArray[RECTANGLES];
int curr = 0;
//sf::CircleShape* c = &cArray[0];
//sf::RectangleShape* r = &rArray[0];


void moveAll(){
	for (int i = 0; i < CIRCLES; i++){
		cArray[i].move(0,0.4);
	}
	for (int i = 0; i < RECTANGLES; i++){
		rArray[i].move(0.4,0);
	}
}

void renderingThread(sf::RenderWindow* window){
	while(window->isOpen()){
		window->clear(sf::Color::Black);
		for(int i = 0; i < CIRCLES; i++){
			window->draw(cArray[i]);
		}
		for(int i = 0; i < RECTANGLES; i++){
			window->draw(rArray[i]);
		}
		window->display();
		moveAll();
	}
}

int main(){

//initialize shit
	sf::RenderWindow window(sf::VideoMode(WINDOW_H, WINDOW_W), "Vectors & Circles");
	window.setFramerateLimit(FPS);
srand(time(NULL));

color[0] = sf::Color::Red;
color[1] = sf::Color::Green;
color[2] = sf::Color::Blue;
color[3] = sf::Color::Yellow;
color[4] = sf::Color::Cyan;
color[5] = sf::Color::White;

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
window.setActive(false);
sf::Thread thread(&renderingThread, &window);
thread.launch();

while( window.isOpen() )
{
	window.clear(sf::Color::Black);
	sf::Event event;
	while (window.pollEvent(event)){
		if (event.type == sf::Event::Closed){
			window.close();
		}
	}	//window.display();
}
return 0;
}

