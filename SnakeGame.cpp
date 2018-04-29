#include<iostream>
#include<conio.h>
#include<ctime>
#include<Windows.h>
using namespace std;

int width = 50;
int height = 20;
int fruitXgenerator(){
	int x = rand()%width;
	if(x==0) return fruitXgenerator();
	else return x;
}

int fruitYgenerator(){
	int y = rand()%height;
	if(y==0) return fruitYgenerator();
	else return y;
}	

bool gameover = false;//initially, game is not over
enum Direction {LEFT, RIGHT, UP, DOWN}; //initially, if not press button, game will not start

int fruitX = fruitXgenerator();//initially generate food
int fruitY = fruitYgenerator();
Direction keyboardDir = LEFT;//initially moving left

class snake{
	public:
	void updateHead();
	void updateTail();
	
	snake(){//constructor 
		snakedir = new snakeDirection;
		snakepos = new snakePosition;
		snakedir->dir = LEFT;
		snakedir->next = NULL;
		snakepos->x = width/2;
		snakepos->y = height/2;
		snakepos->next = NULL;
	}
	~snake(){//destrcutor
		while(snakedir){
			Direction* tmp = &snakedir->dir;
			snakedir = snakedir->next;
			delete tmp;
		}
		while(snakepos){
			int* xtmp = &snakepos->x;
			int* ytmp = &snakepos->y;
			snakepos = snakepos->next;
			delete xtmp;
			delete ytmp;
		}	
	}
	
	void updateMap();
	void clearscreen();
	void input();
	bool hitFruit();
	bool find(int x, int y);
	bool over();
	void run();
	
	private:
	struct snakeDirection{
		Direction dir;
		snakeDirection* next;
	};
	snakeDirection* snakedir;//snake heading direction
	
	struct snakePosition{
		int x;
		int y;
		snakePosition* next;
	};
	snakePosition* snakepos;//snake position. One direction, one position
};

void snake::updateMap(){
	clearscreen();//clean screen
	for(int i=0; i<=width; i++){//draw the edge
		cout << "#";
	}
	cout <<	endl;//the second line
	for(int i=1; i<height; i++){//loop in row
		for(int j=0; j<=width; j++){//loop in column
			bool found = find(j,i);//determine whether there is snake body
			
			
			if(j==0 || j==width) cout << "#";//draw the edge
			else{
				if(i==fruitY && j==fruitX) cout <<"*";//determine whether there is a fruit
				else if(found) cout << "o";//if there is snake body, cout "o"
				else cout <<" ";//if there's only space
			}		
		}
		cout << endl;//parsing to next line
	}
	for(int i=0; i<=width; i++){
		cout <<"#";
	}	
}

void snake::clearscreen(){
	system("cls");
}	

void snake::input(){//read in keyboard, if no input, do nothing
	if(kbhit()){
		switch(_getch()){
			case 119:
				keyboardDir = UP;
				break;
			case 97:
				keyboardDir = LEFT;
				break;
			case 100:
				keyboardDir = RIGHT;
				break;
			case 115:
				keyboardDir = DOWN;
				break;
			default:;
		}
	}	
}

bool snake::hitFruit(){
	switch(snakedir->dir){
		case LEFT:
			if(fruitX == snakepos->x-1 && fruitY == snakepos->y) return true;
			else return false;
		case RIGHT:
			if(fruitX == snakepos->x+1 && fruitY == snakepos->y) return true;
			else return false;
		case UP:
			if(fruitY == snakepos->y-1 && fruitX == snakepos->x) return true;
			else return false;
		case DOWN:
			if(fruitX == snakepos->y+1 && fruitX == snakepos->x) return true;
			else return false;	
		default: 
			return false;
	}	
}

void snake::updateHead(){
	snakeDirection* temp = new snakeDirection;
	snakeDirection* curr = snakedir;
	temp->dir = keyboardDir;////////////////
	temp->next = curr;//////////////////////////
	snakedir = temp;
	
	snakePosition* postemp = new snakePosition;
	snakePosition* poscurr = snakepos;
	switch(keyboardDir){
		case LEFT:
		postemp->x = poscurr->x -1;
		postemp->y = poscurr->y;
		break;
		case RIGHT:
		postemp->x = poscurr->x +1;
		postemp->y = poscurr->y;
		break;
		case UP:
		postemp->x = poscurr->x;
		postemp->y = poscurr->y -1;
		break;
		case DOWN:
		postemp->x = poscurr->x;
		postemp->y = poscurr->y +1;
		break;
	}	
	postemp->next = poscurr;
	snakepos = postemp;
}

void snake::updateTail(){
	if(!hitFruit()){
		snakeDirection* temp = new snakeDirection;
		temp = snakedir;
		while(temp->next->next){
			temp=temp->next;
		}
		delete temp->next;
		temp->next = NULL;
		
		snakePosition* postemp = new snakePosition;
		postemp = snakepos;
		while(postemp->next->next){
			postemp=postemp->next;
		}
		delete postemp->next;
		postemp->next = NULL;
		
	}
	else{
		fruitX = fruitXgenerator();
		fruitY = fruitYgenerator();
	}	
}

bool snake::find(int x, int y){
	snakePosition* search = new snakePosition;
	search = snakepos;
	
	while(search){
		if(search->x == x && search->y == y) return true;
		else search = search->next;
	}
	
	return false;
}

bool snake::over(){
	switch(keyboardDir){
		case LEFT:
		if(snakepos->x == 1) return true;
		else return false;
		case RIGHT:
		if(snakepos->x == width-1) return true;
		else return false;
		case UP:
		if(snakepos->y == 1) return true;
		else return false;
		case DOWN:
		if(snakepos->y == height-1) return true;
		else return false;
	}
}	

void snake::run(){
	while(!gameover){
		updateMap();
		input();
		if(over()){
			gameover = true;
			break;
		}
		else{
			updateHead();
			updateTail();
		}
		Sleep(75);
	}
}

int main(){
	srand(time(NULL));
	snake game;
	game.run();
	return 0;
}	