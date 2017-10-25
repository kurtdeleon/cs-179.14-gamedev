#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#define FPS 60
#define TIMESTEP 1.0f / FPS
#define WINDOW_W 800
#define WINDOW_H 600

using namespace std;
using namespace sf;

RenderWindow window;
int objects;
vector<ConvexShape> shapes;
bool rotateOn = false;

void rotateShapes(){
	//rotate objects
	for (int i = 0; i < objects; i++) {
		shapes[i].rotate(6 * (i+1) * TIMESTEP);
	}
}

void initializeObjects(){
	cout << "How many shapes? ";
	cin >> objects;

	shapes.reserve(objects);

	for (int i = 0; i < objects; i++){
		int points;
		cout << "Shape " << i << ": ";
		cin >> points;
		shapes[i].setPointCount(points);

		for (int j = 0; j < points; j++){
			Vector2f pts;
			cin >> pts.x >> pts.y;
			if (j+1 != points) shapes[i].setPoint(j, pts);
			else shapes[i].setPosition(pts);
		}

		//shapes[i].setOrigin();
		shapes[i].setFillColor(Color::White);
	}
}

/*void SAT(){

}*/

int main(){
	//window stuff
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(VideoMode(WINDOW_W, WINDOW_H), "Drawing AABBs", Style::Default, settings);
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
						shapes[0].move(0, -13 * TIMESTEP);
						break;

						case sf::Keyboard::A:
						shapes[0].move(-13 * TIMESTEP, 0);
						break;

						case sf::Keyboard::S:
						shapes[0].move(0, 13 * TIMESTEP);
						break;

						case sf::Keyboard::D:
						shapes[0].move(13 * TIMESTEP, 0);
						break;

						case sf::Keyboard::F:
						rotateOn = !rotateOn;
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
						//
						break;

						case sf::Keyboard::A:
						//
						break;

						case sf::Keyboard::S:
						//
						break;

						case sf::Keyboard::D:
						//
						break;
					}
					break;
				}
			}
		}

		if (rotateOn) rotateShapes();
		window.clear(Color::Black);
		for(const auto& rect : rectangles) { window.draw(rect); }
			for(const auto& aabb : AABB) { window.draw(aabb); }
				window.display();
		}
	}
