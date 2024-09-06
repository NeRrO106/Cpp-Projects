#include <iostream>
#include <vector>
#include <curses.h>

using namespace std;

enum Direction{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct SnakeSegment{
	int x, y;
	SnakeSegment(int col, int row) : x(col), y(row){}
};

class SnakeGame{
	private:
		int width, height;
		bool gameOver;
		int score;
		Direction dir;
		vector<SnakeSegment> snake;
		SnakeSegment fruit;
	public:
		SnakeGame(int w, int h);
		void GenerateFruit();
		void Setup();
		void Draw();
		void Input();
		void Logic();
		void Run();
};
SnakeGame:SnakeGame(int w, int h){
	width = w;
	height = h;
	gameOver = false;
	score = 0;
	dir = RIGHT;
	snake.push_back(SnakeSegment(width / 2, height / 2));
	GenerateFruit();
}
void SnakeGame:GenerateFruit(){
	fruit.x = rand() % width;
	fruit.y = rand() % height;
}

void SnakeGame:Draw(){
 	system("clear");
	for(int i = 0; i < width + 2; i++){
		cout << "#";
	}
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			if(j==0) cout << "#";
			bool printSnake = false;
			for(size_t k = 0; k < snake.size(); k++){
				if(snake[k].x == j && snake[k].y == i){
					cout << "S";
					printSnake = true;
				}
			}
			if(!printSnake && fruit.x == j && fruit.y == i){
				cout << "F";
			}
			if(!printSnake && fruit.x != j && fruit.y != i){
				cout << ".";
			}
			if(j == width - 1) cout << "#";
		}
	}
	for(int i = 0; i < width + 2; i++) cout << "#";
	cout << "Scor: " << score <<endl;
}
void SnakeGame:Setup(){

}
