#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class NumberGuessGame{
	private:
		int level;
		int secretNumber;
		int maxAttempts;
		int currentAttempts;
		void generateSecretNumber();
	public:
		NumberGuessGame(int);
		void startGame();
		void playRound();
		bool isCorrectGuess(int);
};

NumberGuessGame::NumberGuessGame(int level){
	this->level = level;
	switch(level){
		case 1:
			this->maxAttempts = 3;
			break;
		case 2:
			this->maxAttempts = 5;
			break;
		case 3:
			this->maxAttempts = 10;
			break;
	}
	generateSecretNumber();
}
void NumberGuessGame::generateSecretNumber(){
	srand((unsigned) time(NULL));
	if(this->level == 1){
		secretNumber = rand() % 10 + 1;
	}
	if(this->level == 2){
		secretNumber = rand() % 50 + 1;
	}
	if(this->level == 3){
		secretNumber = rand() % 100 + 1;
	}
}

void NumberGuessGame::startGame(){
	cout << "Start Joc" << endl;
	while(currentAttempts < maxAttempts){
		playRound();
	}
	cout << "Joc terminat! Numarul secret era: " << secretNumber << endl;
}

void NumberGuessGame::playRound(){
	int guess;
	cout << "Introdu un numar: ";
	cin >> guess;
	currentAttempts++;
	if(isCorrectGuess(guess)){
		cout << "Felicitari ai ghicit numarul!" << endl;
		exit(0);
	}
	else{
		cout << "Ai gresit incearca iar." << endl;
	}
}
bool NumberGuessGame::isCorrectGuess(int guess){
	return guess == secretNumber;
}

int main(){
	int level;
	cout << "Nivel 1 - 3 incercari si numarul este cuprins intre 0 si 10" << endl;
	cout << "Nivel 2 - 5 incercari si numarul este cuprins intre 0 si 50" << endl;
	cout << "Nivel 3 - 10 incercari si numarul este cuprins intre 0 si 100" << endl;
	cout << "Introdu nivelul de dificultate:" << endl;
	cin >> level;
	NumberGuessGame game(level);
	game.startGame();
	return 0;
}
