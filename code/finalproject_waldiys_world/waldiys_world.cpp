#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <math.h>
#include <vector>

#define FPS 60.0f
#define TIMESTEP 1.0f / FPS
#define WINDOW_W 800
#define WINDOW_H 600

#define FORCE 8000.0f
#define FR_AIR 0.1f
#define FR_GND 0.85f
#define MAX_BULLETS 20.0f
#define BULLET_SIZE 12.5f
#define BULLET_SPEED 400 * TIMESTEP
#define TILE_SIZE 50.0f
#define CANNON_W 125.0f
#define CANNON_H 75.0f
#define CHAR_W 30.0f
#define CHAR_H 50.0f
#define FLAG_W 50.0f
#define FLAG_H 75.0f

#define GRID_SIZE 50
#define GRIDS ROW_OF_GRIDS * GRIDS_IN_ROW
#define ROW_OF_GRIDS WINDOW_H / GRID_SIZE
#define GRIDS_IN_ROW WINDOW_W / GRID_SIZE

using namespace std;
using namespace sf;

RenderWindow window;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               

struct TextureStorage { //structure for all textures, all textures are loaded here
	Texture groundTextures[6];
	Texture cloudTextures[3];
	Texture cannonBallTexture, characterTexture, cannonTexture, bg, flagTexture;
	Texture screenTextures[4];

	TextureStorage(){
		groundTextures[0].loadFromFile("assets/tile_up_mid.png");
		groundTextures[1].loadFromFile("assets/tile_filler.png");
		groundTextures[2].loadFromFile("assets/tile_side_left.png");
		groundTextures[3].loadFromFile("assets/tile_up_left.png");
		groundTextures[4].loadFromFile("assets/tile_side_right.png");
		groundTextures[5].loadFromFile("assets/tile_up_right.png");
		cloudTextures[0].loadFromFile("assets/cloud1.png");
		cloudTextures[1].loadFromFile("assets/cloud2.png");
		cloudTextures[2].loadFromFile("assets/cloud3.png");
		screenTextures[0].loadFromFile("assets/title_screen.png");
		screenTextures[1].loadFromFile("assets/pause_screen.png");
		screenTextures[2].loadFromFile("assets/win_screen.png");
		screenTextures[3].loadFromFile("assets/lose_screen.png");
		cannonTexture.loadFromFile("assets/cannon.png");
		characterTexture.loadFromFile("assets/waldiy.png");
		cannonBallTexture.loadFromFile("assets/cannon_ball.png");
		flagTexture.loadFromFile("assets/flag.png");
		bg.loadFromFile("assets/bg.png");
	}
};

struct Character { //structure for the character/player with its own members and member functions
	RectangleShape unit;
	bool isOnGround;
	Vector2f velocity, accel;
	float mass, mass_r;

	Character(float px, float py){
		unit.setSize(Vector2f(CHAR_W, CHAR_H));
		unit.setPosition(px, py);
		isOnGround = false;
		velocity = Vector2f(0, 0);
		accel = Vector2f(0, 100000.0f * TIMESTEP); //this is to simulate gravity, (0, 1666.67)
		mass = 20;
		mass_r = 1/mass; //for updating position through multiplication
	}

	Vector2f pos() { return unit.getPosition(); }
	FloatRect AABB() { return unit.getGlobalBounds(); }
	bool has(FloatRect r) { return unit.getGlobalBounds().intersects(r); }
	void drawPlayer() { window.draw(unit); }
	void jump(){ 
		if(isOnGround) {
			moveY(-1); //move it up
			velocity.y = -600.0f; 
			isOnGround = false;
		}
	}
	void limiter() {
		if (velocity.x > FORCE * TIMESTEP) velocity.x = FORCE * TIMESTEP; //max at 133.33 without friction
		else if (velocity.x < -FORCE * TIMESTEP) velocity.x = -FORCE * TIMESTEP; //max at -133.33 without friction
	}
	
	void changePos(Vector2f newPos) { unit.setPosition(newPos); } //for physics
	void moveX(float posX) { unit.setPosition(unit.getPosition().x + posX, unit.getPosition().y); } //for hard resets
	void moveY(float posY) { unit.setPosition(unit.getPosition().x, posY + unit.getPosition().y); } //for hard resets
	float left() { return unit.getPosition().x; } //returns left side of the player 
	float right() { return unit.getPosition().x + unit.getSize().x; } //returns right side of the player
	float top() { return unit.getPosition().y; } //returns top side of the player
	float bottom() { return unit.getPosition().y + unit.getSize().y; } //returns bottom side of the player
}; 

struct GridCell { //structure for a grid cell with its own members and member functions
	FloatRect guide;
	vector<RectangleShape*> tiles, cannons;
	vector<CircleShape*> bullets;
	bool containsPlayer, containsFlag;

	GridCell(float px, float py){ 
		guide = FloatRect(Vector2f(px, py), Vector2f(GRID_SIZE, GRID_SIZE)); //parameters are left position, top position, width, height
		containsPlayer = false;
		containsFlag = false;
	}

	bool has(FloatRect r) { return guide.intersects(r); } //universal collision check for all objects and for initializing and updating grids
};

RectangleShape background, titleScreen, pauseScreen, winScreen, loseScreen;
int gameState; //0 = title screen, 1 = game, 2 = pause, 3 = win, 4 = lose
RectangleShape* flag;
list<RectangleShape*> tiles, cannons;
list<CircleShape*> bullets;
list<GridCell*> grid;
Character* player;
TextureStorage* ts;
bool moveLeft, moveRight; //for movement
float timeBeforePause;

bool isInsideWindow(Vector2f pos, Vector2f size){ //for updating the uniform grid, and for shooting bullets
	if ((pos.x + size.x) < 0 || pos.x > WINDOW_W || (pos.x + size.x) < 0 || pos.y > WINDOW_H){
		return false;
	} return true;
}

void updatePosition(){ //update position of the player and the bullets
	//move based on boolean to somewhat reduce delay of movement
	if(moveLeft) player->accel.x += -(FORCE * player->mass_r); //also as (FORCE / player->mass)
	if(moveRight) player->accel.x += (FORCE * player->mass_r); //also as (FORCE / player->mass)
	//character movement
	player->velocity += player->accel * TIMESTEP;
	player->limiter(); //max velocity will not really be at 133.33 due to friction applied on both air and on the ground
	if (player->isOnGround) player->velocity -= FR_GND * player->velocity * player->mass_r; //also as (FR_GND * (player->velocity / player->mass))
	else player->velocity -= FR_AIR * player->velocity * player->mass_r; //also as (FR_AIR * (player->velocity / player->mass))
	//player->limiter(); <- if applied here the max velocity will be at 133.33
	Vector2f newPos = player->unit.getPosition() 
	+ (0.5f * player->accel * TIMESTEP * TIMESTEP) + (player->velocity * TIMESTEP); // newPos = oldPos + (1/2 * a * t * t) + (v * t)
	player->changePos(newPos);
	//bullet movement, bullets move to the left based on BULLET_SPEED
	for(list<CircleShape*>::iterator b = bullets.begin(); b != bullets.end(); ++b){ 
		if (isInsideWindow((**b).getPosition(), Vector2f((**b).getRadius(), (**b).getRadius()))) { (*b)->move(-BULLET_SPEED, 0); } 
	}
}

void updateGrid(){ //update the uniform grid
	for(list<GridCell*>::iterator g = grid.begin(); g != grid.end(); ++g){
		(**g).bullets.clear();
		if ((**g).has(player->AABB())) (**g).containsPlayer = true;
		else (**g).containsPlayer = false;

		for(list<CircleShape*>::iterator bu = bullets.begin(); bu != bullets.end(); ++bu){
			if ((**g).has((**bu).getGlobalBounds())) { (**g).bullets.push_back(*bu); }
		}
	}
}

Vector2f getMinVec(Vector2f a, Vector2f b){ //for overlap checking of getting the minimum vector (for player collision)
	if (a.x < b.x) return a;
	return b;
}

Vector2f overlapCheck(float aTop, float aBottom, float aLeft, float aRight, float bTop, float bBottom, float bLeft, float bRight){ //for player collision
	//(overlapAmount, direction)
	//0 = top, 1 = bottom, 2 = left, 3 = right
	bool isOverlappingX = false; //for wall (horizontal) collision
	bool isOverlappingY = false; //for ground (vertical) collision
	Vector2f minX, minY; //store overlap amount in vector.x, store direction in vector.y

	if ((aTop < bTop && aBottom < bBottom) || (aTop > bTop && aBottom > bBottom)) isOverlappingY = true;
	if ((aRight > bLeft && aRight < bRight) || (aLeft > bLeft && aLeft < bRight)) isOverlappingX = true;

	if (isOverlappingY){
		bool above = false; bool below = false;
		if (aTop < bTop && aBottom < bBottom) above = true; //on top of the ground
		if (aTop > bTop && aBottom > bBottom) below = true; //below the ground

		if (above && below) minY = getMinVec(Vector2f(aBottom - bTop, 0), Vector2f(bBottom - aTop, 1)); 
		else if (above && !below) minY = Vector2f(aBottom - bTop, 0);
		else minY = Vector2f(bBottom - aTop, 1);
	}
	if (isOverlappingX){
		bool onLeft = false; bool onRight = false;
		if (aRight > bLeft && aRight < bRight) onLeft = true; //player going right colliding to a wall
		if (aLeft > bLeft && aLeft < bRight) onRight = true; //player going left colliding to a wall

		if (onLeft && onRight) minX = getMinVec(Vector2f(aRight - bLeft, 2), Vector2f(bRight - aLeft, 3));
		else if (onLeft && !onRight) minX = Vector2f(aRight - bLeft, 2);
		else minX = Vector2f(bRight - aLeft, 3);
	}

	if (isOverlappingX && isOverlappingY) return getMinVec(minX, minY);
	else if (isOverlappingX && !isOverlappingY) return minX;
	else return minY;
}

void checkWorldCollision(){
	//hard reset on borders of window, player will fall to the ground basically
	if (player->left() < 0) { 
		player->moveX(-player->left()); //if removed, it can go beyond the screen
		player->velocity.x = 0; 
		player->accel.x = 0; 
	} else if (player->right() > WINDOW_W) { 
		player->moveX(0); //so that it won't really go beyond the screen; removing the moveX will make the player go beyond the screen actually
		player->velocity.x = 0;
		player->accel.x = 0; 
	}

	//check for death by falling
	if (player->top() > WINDOW_H) { gameState = 4; }

	for(list<GridCell*>::iterator g = grid.begin(); g != grid.end() && gameState == 1; ++g){
	//player-tile collision
		if(!(**g).tiles.empty() && (**g).containsPlayer){ //if a tile and the player is on the same grid cell
			for(vector<RectangleShape*>::iterator ti = (**g).tiles.begin(); ti != (**g).tiles.end() && gameState == 1; ++ti){
				if (player->has((**ti).getGlobalBounds())) { //this means they're colliding in some way
					Vector2f penetrationInfo = overlapCheck(player->top(), player->bottom(), 
						player->left(), player->right(), (**ti).getPosition().y, 
						(**ti).getPosition().y + (**ti).getSize().y, (**ti).getPosition().x, 
						(**ti).getPosition().x + (**ti).getSize().x);

				//collision response is applied to shallower penetration (penetrationInfo.y)
				switch((int) penetrationInfo.y){
					case 0: player->moveY(-penetrationInfo.x); player->velocity.y = 0; player->isOnGround=true; break; 
					case 1: player->moveY(penetrationInfo.x); player->velocity.y = 0; player->isOnGround=false; break; 
					case 2: player->moveX(-penetrationInfo.x); player->velocity.x = 0; player->isOnGround=false; break;
					case 3: player->moveX(penetrationInfo.x); player->velocity.x = 0; player->isOnGround=false; break;
					}
				}
			}
		}
	
		//player-cannon collision
		if(!(**g).cannons.empty() && (**g).containsPlayer){ //if a cannon and the player is on the same grid cell
			for(vector<RectangleShape*>::iterator ca = (**g).cannons.begin(); ca != (**g).cannons.end() && gameState == 1; ++ca){
				if (player->has((**ca).getGlobalBounds())) { //this means they're colliding in some way
					Vector2f penetrationInfo = overlapCheck(player->top(), player->bottom(), 
						player->left(), player->right(), (**ca).getPosition().y, 
						(**ca).getPosition().y + (**ca).getSize().y, (**ca).getPosition().x, 
						(**ca).getPosition().x + (**ca).getSize().x);

				//collision response is applied to shallower penetration (penetrationInfo.y)
				switch((int) penetrationInfo.y){
					case 0: player->moveY(-penetrationInfo.x); player->velocity.y = 0; player->isOnGround=true; break; 
					case 1: player->moveY(penetrationInfo.x); player->velocity.y = 0; player->isOnGround=false; break; 
					case 2: player->moveX(-penetrationInfo.x); player->velocity.x = 0; player->isOnGround=false; break;
					case 3: player->moveX(penetrationInfo.x); player->velocity.x = 0; player->isOnGround=false; break;
					}
				}
			}			
		}
		//player-bullet collision
		if(!(**g).bullets.empty() && (**g).containsPlayer){ //if a bullet and the player is on the same grid cell
			for(vector<CircleShape*>::iterator bu = (**g).bullets.begin(); bu != (**g).bullets.end() && gameState == 1; ++bu){
				if (player->has((**bu).getGlobalBounds())){ //this means they're colliding in some way 
					gameState = 4; //you lose the game
				}
			}	
		}
		//player-flag collision
		if((**g).containsFlag && (**g).containsPlayer){ //this means they're colliding in some way
			if (player->has(flag->getGlobalBounds())) gameState = 3; //if the player touches(collides) with the flag, you win the game
		}
	}
}

bool cannonShoot(float secondsElapsed){
	if (secondsElapsed > 1.8) { //each bullet (is) constantly spawns/(fired) every 1.8 seconds, thus when it reaches this point, it will load another bullet
		CircleShape* shootMe; 
		for(list<RectangleShape*>::iterator ca = cannons.begin(); ca != cannons.end(); ++ca){
			bool found = false; //bullet initially pooled (not part of the screen)
			for(list<CircleShape*>::iterator bu = bullets.begin(); bu != bullets.end() && !found; ++bu){
				if (!isInsideWindow((**bu).getPosition(), Vector2f((**bu).getRadius(), (**bu).getRadius()))) { //loading the bullet to the screen
					shootMe = *bu;
					Vector2f newPos = (**ca).getPosition();
					newPos += Vector2f(0, BULLET_SIZE*2); //position to where the bullet is loaded
					shootMe->setPosition(newPos);
					found = true; //bullet is already in the screen
				}
			}
		} return true; //bullet ready to be fired
	} return false;
}

void initializeGrid(){
	//MAKE THE GRID STRUCTURES
	for (int i = 0; i < ROW_OF_GRIDS; i++){
		for (int j = 0; j < GRIDS_IN_ROW; j++){
			GridCell* gc = new GridCell{(float)GRID_SIZE * j, (float)GRID_SIZE * i};
			grid.push_back(gc);
		}
	}
	//PUT STUFF INTO GRIDS
	for(list<GridCell*>::iterator g = grid.begin(); g != grid.end(); ++g){
		//put character
		if ((**g).has(player->AABB())) { (**g).containsPlayer = true; }
		if ((**g).has(flag->getGlobalBounds())) { (**g).containsFlag = true; }
		//put tiles
		for(list<RectangleShape*>::iterator ti = tiles.begin(); ti != tiles.end(); ++ti){
			if (isInsideWindow((**ti).getPosition(), (**ti).getSize())){
				if ((**g).has((**ti).getGlobalBounds())) { (**g).tiles.push_back(*ti); }
			}
		}
		//put cannons
		for(list<RectangleShape*>::iterator ca = cannons.begin(); ca != cannons.end(); ++ca){
			if (isInsideWindow((**ca).getPosition(), (**ca).getSize())) {
				if ((**g).has((**ca).getGlobalBounds())) { (**g).cannons.push_back(*ca); }
			}
		}
	}
}

void initializeGame(){ 
	int t, c, index;
	float px, py;
	ts = new TextureStorage{};
	background.setSize(Vector2f(WINDOW_W, WINDOW_H)); background.setTexture(&(ts->bg)); 
	titleScreen.setSize(Vector2f(WINDOW_W, WINDOW_H)); titleScreen.setTexture(&(ts->screenTextures[0]));
	pauseScreen.setSize(Vector2f(WINDOW_W, WINDOW_H)); pauseScreen.setTexture(&(ts->screenTextures[1]));
	winScreen.setSize(Vector2f(WINDOW_W, WINDOW_H)); winScreen.setTexture(&(ts->screenTextures[2]));
	loseScreen.setSize(Vector2f(WINDOW_W, WINDOW_H)); loseScreen.setTexture(&(ts->screenTextures[3]));

	//CREATE CHARACTER (WALDIY)
	cin >> px >> py;
	player = new Character{px, py};
	player->unit.setTexture(&(ts->characterTexture));
	//CREATE TILES (FOR PLATFORM)
	cin >> t;
	for (int i = 0; i < t; i++){
		RectangleShape* p = new RectangleShape();
		cin >> px >> py >> index;
		p->setSize(Vector2f(TILE_SIZE, TILE_SIZE));
		p->setPosition(px, py);
		p->setTexture(&(ts->groundTextures[index])); //index = array index for ground textures
		tiles.push_back(p);
	}
	//CREATE CANNONS (FOR FIRING BULLETS)
	cin >> c;
	for (int i = 0; i < c; i++){
		RectangleShape* p = new RectangleShape();
		cin >> px >> py;
		p->setSize(Vector2f(CANNON_W, CANNON_H));
		p->setPosition(px, py);
		p->setTexture(&(ts->cannonTexture));
		cannons.push_back(p);
	}
	//CREATE BULLETS (TO AVOID)
	for (int i = 0; i < MAX_BULLETS; i++){
		CircleShape* b = new CircleShape();
		b->setRadius(BULLET_SIZE);
		b->setPosition(900, 900); //out of bounds
		b->setTexture(&(ts->cannonBallTexture));
		bullets.push_back(b);
	}
	//CREATE FLAG (TO WIN)
	cin >> px >> py;
	flag = new RectangleShape(Vector2f(FLAG_W, FLAG_H));
	flag->setPosition(px, py);
	flag->setTexture(&(ts->flagTexture));

	initializeGrid();
	gameState = 0; //set to title screen at the start
} 


int main(){
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(VideoMode(WINDOW_W, WINDOW_H), "[STABLE] Waldiy's World", Style::Default, settings);
	window.setFramerateLimit(FPS);
	window.setKeyRepeatEnabled(true); //weird... hahaha it can work even if it's false
	window.setActive(false);
	Clock clock;

	initializeGame(); //data-driven levels happen here, parsed through text file

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
					if (gameState == 1) player->jump();
					break;
					case Keyboard::A:
					if (gameState == 1) moveLeft = true; 
					break;
					case Keyboard::D:
					if (gameState == 1) moveRight = true;
					break;
					case Keyboard::P:
					if (gameState == 1) {
						timeBeforePause = clock.restart().asSeconds();
						gameState++; //go to gameState = 2
					}
					else if (gameState == 2) gameState--; //go to gameState = 1
					break;
					case Keyboard::Space:
					if (gameState == 0) gameState++; //go to gameState = 1
					else if (gameState == 3 || gameState == 4) window.close();
					break;
					case Keyboard::Escape:
					window.close();
					break;
				}
				break;
				case Event::KeyReleased:
				switch(event.key.code){
					case Keyboard::A:
					if (gameState == 1) {
						moveLeft = false;
						player->accel.x = 0;
						if (player->velocity.x < 0) player->velocity.x = -70; //for smooth movement when sudden turn to another direction happens
					}
					break;
					case Keyboard::D:
					if (gameState == 1) {
						moveRight = false;
						player->accel.x = 0;
						if (player->velocity.x > 0) player->velocity.x = 70; //for smooth movement when sudden turn to another direction happens
					}
					break;
				}
				break;
			}
		}
		
		//do stuff
		window.clear(Color::Black); //try removing this
		if (gameState == 0){
			window.draw(titleScreen);
		}
		else {
			if (gameState == 1){ //doing functions
				if (cannonShoot(clock.getElapsedTime().asSeconds() + timeBeforePause)) { clock.restart(); } //reset the timer/clock every time a bullet is fired
				updatePosition();
				updateGrid();
				checkWorldCollision();
			}
			//drawing the world
			window.draw(background);
			for(list<RectangleShape*>::iterator it = tiles.begin(); it != tiles.end(); ++it){ window.draw(**it); }
			for(list<CircleShape*>::iterator it = bullets.begin(); it != bullets.end(); ++it){ 
				if (isInsideWindow((**it).getPosition(), Vector2f((**it).getRadius(), (**it).getRadius()))) { window.draw(**it); } 
			} //bullet will only be drawn when it is already fired
			for(list<RectangleShape*>::iterator it = cannons.begin(); it != cannons.end(); ++it){ window.draw(**it); }
			player->drawPlayer();
			window.draw(*flag);

			if (gameState == 2) {window.draw(pauseScreen); clock.restart();} //pseudo-pause, it happens that after pausing more than 1 bullet has been fired from the cannon
			else if (gameState == 3) window.draw(winScreen);
			else if (gameState == 4) window.draw(loseScreen);
		}
		window.display();
	}
}