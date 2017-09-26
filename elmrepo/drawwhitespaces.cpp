#include <iostream>
#include <string>
//#include <thread>
//#include <chrono>
using namespace std;

string input;
int pos, enemy, pos2, height, width, rowToPutEnemy, putEnemy, rowToPutPlayer, putPlayer;
//pos = player pos // pos2 = enemy pos
void draw(int height, int width);
void move(string dir);

int main(){
	//get height/width
	cin >> height >> width;
	draw(height, width);
	// cout << "Your goal is to move close enough to your enemy and kill him. Good luck." << endl;
	// enemy = 1;
	// while (1){
	// 	draw(height, width);
	// 	cin >> input;
	// 	if (enemy < 1){
	// 		cout << "You vanquished your foe!" << endl;
	// 		cout << "This program will close in 2 seconds." << endl;
	// 		cout << "Thank you for playing!" << endl;
	// 		//this_thread::sleep_for(chrono::seconds(2));
	// 		break;
	// 	}
	// }
}

void draw(int height, int width){
	if(height % 2 == 0) rowToPutEnemy = height - 1; else rowToPutEnemy = height;
	if(width == 1 || width == 2) putEnemy = 1;
	else{
		if((width % 2 == 1)) putEnemy = width + width/2;
		else if((width % 2 == 0)) putEnemy = width + (width/2 - 2);
	}
	if (height == 0 || width == 0){
		cout << "Invalid dimensions. Please try again.";
	}
	else{
		for(int row = 0; row <= height*2; row++){
			if(row % 2 == 0){
				for(int putChar1 = 0; putChar1 <= width*3; putChar1++){
					if(putChar1 % 3 == 0) cout << "+";
					else cout << "-";
				}
			}else if(row % 2 == 1 && row == rowToPutEnemy){
			 	for(int spec = 0; spec <= width*3; spec++){
					if(spec % 3 == 0) cout << "|";
			 		else if(spec == putEnemy) cout << "0";
					else cout << " ";
 				}
 			}else if(row % 2 == 1 && row != rowToPutEnemy){
				for(int putChar2 = 0; putChar2 <= width*3; putChar2++){
					if(putChar2 % 3 == 0) cout << "|";
					else cout << " ";
				}
			}
			cout << "\n";
		}
	}
}

// void move(string dir){
// 	int temp = 0;

// 	switch(tolower(tempInput)){
// 		case 'north': case: 'up': case 'n':
// 		if (pos < width) { //upper line wrap around
// 			temp = width*(height-1) + pos;
// 		}
// 		else {
// 			temp = pos - width;
// 		}

// 		case 'east': case: 'right': case 'e':
// 		if ((pos % width) == (width - 1)){
// 			temp = pos - (width - 1);
// 		}
// 		else {
// 			temp = pos++;
// 		}

// 		case 'south': case: 'up': case 'n':
// 		if (pos >= width*(length-1)){ //lower line wrap around
// 			temp = pos % width;
// 		}
// 		else {
// 			temp = pos + width;
// 		}

// 		case 'west': case: 'left': case 'n':
// 		if (pos % width == 0){
// 			temp = pos + (width - 1);
// 		}
// 		else {
// 			temp = pos--;
// 		}
		
// 		case 'help':
// 		temp = pos;
// 		cout << "Available commands:" << endl;
// 		cout << "attack | hit | a   =>     attack" << endl;
// 		cout << "north | up | n     =>     move up" << endl;
// 		cout << "east | right | e   =>     move right" << endl;
// 		cout << "south | down | s   =>     move down" << endl;
// 		cout << "west | left | w    =>     move left" << endl;
		
// 		case 'attack': case: 'hit': case: 'a':
// 		temp = pos;
// 		if (pos == pos2){
// 			enemy--;
// 		}
// 		else {
// 			cout << "Nothing happened.";
// 		}
// 	}
// 	pos = temp;
// }