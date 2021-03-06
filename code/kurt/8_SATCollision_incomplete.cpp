#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#define FPS 60
#define TIMESTEP 1.0f / FPS
#define SPEED 200 * TIMESTEP
#define WINDOW_W 800
#define WINDOW_H 600

using namespace std;
using namespace sf;

RenderWindow window;
int objects;
vector<ConvexShape> shapes;
vector<RectangleShape> AABB;
bool rotateOn = false;
bool u, d, l, r;

//drawing AABBs
void drawAABBs(){
	for(int i = 0; i < objects; i++){
		Vector2f minimum = shapes[i].getTransform().transformPoint(shapes[i].getPoint(0));
		Vector2f maximum = minimum;
		for(int j = 1; j < shapes[i].getPointCount(); ++j){
			Vector2f point = shapes[i].getTransform().transformPoint(shapes[i].getPoint(j));
			minimum.x = min(minimum.x, point.x);
			minimum.y = min(minimum.y, point.y);
			maximum.x = max(maximum.x, point.x);
			maximum.y = max(maximum.y, point.y);
		}
		auto rect = FloatRect(minimum, maximum-minimum);
		AABB[i].setSize(Vector2f(rect.width, rect.height));
		AABB[i].setPosition(rect.left, rect.top);
	}
}

//checks if AABBs are colliding using min-width
bool isAABBColliding(int a, int b){
	Vector2f diff;
	diff.x = AABB[a].getGlobalBounds().left - AABB[b].getGlobalBounds().left;
	diff.y = AABB[a].getGlobalBounds().top - AABB[b].getGlobalBounds().top;
	
	//returns false if it is not colliding
	if (diff.x > AABB[b].getSize().x || diff.y > AABB[b].getSize().y ||
		-diff.x > AABB[a].getSize().x || -diff.y > AABB[a].getSize().y){
		return false;
	}
	return true;
}

/* SAT COLLISION */
Vector2f getPerpNormal(Vector2f corner1, Vector2f corner2){
	Vector2f temp = corner1 - corner2;
	Vector2f perp = Vector2f(-temp.y, temp.x);
	return perp;
}

float dotProduct(Vector2f v, Vector2f u){
	return ((v.x * u.x) + (v.y * u.y));
}

float getMinLS(vector<Vector2f> points, Vector2f perp){
	float mini;
	for (int i = 0; i < points.size(); i++){
		float p = dotProduct(points[i], perp);
		if (i != 0) mini = min(mini, p);
		else mini = p;
	}
	return mini;
}

float getMaxLS(vector<Vector2f> points, Vector2f perp){
	float maxi;
	for (int i = 0; i < points.size(); i++){
		float p = dotProduct(points[i], perp);
		if (i != 0) maxi = max(maxi, p);
		else maxi = p;
	}
	return maxi;
}

vector<Vector2f> getCorners(int index){
	vector<Vector2f> corners;
	corners.resize(shapes[index].getPointCount());
	for (int i = 0; i < shapes[index].getPointCount(); i++){
		corners.push_back(shapes[index].getTransform().transformPoint(shapes[index].getPoint(i)));
	}
	return corners;
}

void checkSATCollision(){
	for (int i = 0; i < objects; i++){
		for (int j = 0; j < objects; j++){
			if (i != j){
				if (isAABBColliding(i, j)){
					/* SAT Collision */
					bool isStillColliding = true;
					vector<Vector2f> corners1 = getCorners(i);
					vector<Vector2f> corners2 = getCorners(j);

					//check using perpendicular normals of first shape
					for (int k = 0; k < corners1.size(); k++){
						Vector2f perpNorm;
						//get normal
						if (i != 0) perpNorm = getPerpNormal(corners1[k], corners1[k+1]);
						else perpNorm = getPerpNormal(corners1[k], corners1[0]);
						//solve for the line segments
						float min1 = getMinLS(corners1, perpNorm);
						float max1 = getMaxLS(corners1, perpNorm);
						float min2 = getMinLS(corners2, perpNorm);
						float max2 = getMaxLS(corners2, perpNorm);
						//check if still colliding
						if (min2 > max1 || min1 > max2) {
							isStillColliding = false;
							break;
						}
					}

					//check using perpendicular normals of second shape
					if (isStillColliding){
						for (int k = 0; k < corners2.size(); k++){
							Vector2f perpNorm;
							//get normal
							if (i != 0) perpNorm = getPerpNormal(corners2[k], corners2[k+1]);
							else perpNorm = getPerpNormal(corners2[k], corners2[0]);
							//solve for the line segments
							float min1 = getMinLS(corners1, perpNorm);
							float max1 = getMaxLS(corners1, perpNorm);
							float min2 = getMinLS(corners2, perpNorm);
							float max2 = getMaxLS(corners2, perpNorm);
							//check if still colliding
							if (min2 > max1 || min1 > max2) {
								isStillColliding = false;
								break;
							}
						}
					}

					if (isStillColliding) {
						shapes[i].setFillColor(Color::Red);
						shapes[j].setFillColor(Color::Red);
					} 
					else {
						shapes[i].setFillColor(Color::Yellow);
						shapes[j].setFillColor(Color::Yellow);
					}
				}
			}
		}
	}
}

Vector2f getCentroid(vector<Vector2f> p){
	Vector2f centroid;
	float area;

	for (int i = 0; i < p.size(); i++){
		if (i+1 != p.size()){
			area += (p[i].x * p[i+1].y) - (p[i+1].x * p[i].y);
			centroid.x += (p[i].x + p[i+1].x) * ((p[i].x * p[i+1].y) - (p[i].y * p[i+1].x));
			centroid.y += (p[i].y + p[i+1].y) * ((p[i].x * p[i+1].y) - (p[i].y * p[i+1].x));
		}
		else {
			area += (p[i].x * p[0].y) - (p[0].x * p[i].y);
			centroid.x += (p[i].x + p[0].x) * ((p[i].x * p[0].y) - (p[i].y * p[0].x));
			centroid.y += (p[i].y + p[0].y) * ((p[i].x * p[0].y) - (p[i].y * p[0].x));
		}
	}
	area *= 0.5;
	centroid.x *= 1 / (6*area);
	centroid.y *= 1 / (6*area);

	return centroid;
}

void initializeObjects(){
	//get number of shapes to make
	cout << "How many shapes? ";
	cin >> objects;
	shapes.resize(objects);
	AABB.resize(objects);

	//shapes
	for (int i = 0; i < objects; i++){
		//initialize
		int points;
		vector<Vector2f> allPoints;

		//get points of shape
		cout << "Shape " << i << " points: ";
		cin >> points;
		shapes[i].setPointCount(points);
		allPoints.resize(points);

		//set and get points
		for (int j = 0; j < points; j++){
			Vector2f pts;
			cin >> pts.x >> pts.y;
			shapes[i].setPoint(j, pts);
			allPoints.push_back(pts);
		}
		//set origin
		shapes[i].setOrigin(getCentroid(allPoints));

		//set position
		Vector2f pts;
		cin >> pts.x >> pts.y;
		shapes[i].setPosition(pts);

		//fill shape color
		shapes[i].setFillColor(Color::White);

		//fill AABB deets
		AABB[i].setFillColor(Color::Transparent);
		AABB[i].setOutlineColor(Color::Magenta);
		AABB[i].setOutlineThickness(1.5);
	}
}

void moveAll(){
	//movement
	if (u) shapes[0].move(0, -SPEED);
	if (l) shapes[0].move(-SPEED, 0);
	if (d) shapes[0].move(0, SPEED);
	if (r) shapes[0].move(SPEED, 0);
}

void rotateShapes(){
	//rotate objects
	for (int i = 0; i < objects; i++) {
		shapes[i].rotate(6 * (i+1) * TIMESTEP);
	}
}

void resetColors(){
	for (int i = 0; i < objects; i++) {
		shapes[i].setFillColor(Color::White);
	}
}

int main(){
	//create the rectangles and AABBs
	initializeObjects();

	//window stuff
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(VideoMode(WINDOW_W, WINDOW_H), "Separating Axis Theorem", Style::Default, settings);
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
					case sf::Keyboard::R:
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
		
		moveAll();
		if (rotateOn) rotateShapes();
		drawAABBs();
		resetColors();
		checkSATCollision();
		
		window.clear(Color::Black);
		for(const auto& shape : shapes) { window.draw(shape); }
		for(const auto& aabb : AABB) { window.draw(aabb); }
		window.display();
	}
}