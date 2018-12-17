/*
Benjamin Williams
17/12/2018
This is a classic number guessing game, where the user can specify their own boundaries of where the number generated will lie.
The number is generated using the rand() function found in the cstdlib library, and the seed is generated using the current time.
The number of guesses that the user receives is calculated based on the worst case scenario of the binary search algorithm.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <math.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int getNumbers(string pos);
void getGuesses(int numberGenerated, int numGuesses);


int main() {
	srand(static_cast<unsigned int> (time(0))); //seeds the random number generator
	int numberGenerated, startingNumber, endingNumber, numGuesses;

	cout << "Welcome to the random number guesser!  The goal of this game is to guess a "
		 << "number between the boundaries that you specify. Good luck!" << endl;

	char playAgain = 'y';
	while(playAgain == 'y') {
		//Gets the starting and ending numbers
		startingNumber = getNumbers("starting");
		endingNumber = getNumbers("ending");

		//ensures that the starting and ending values have a separation of at least 10
		while(endingNumber - startingNumber < 10) {
			cout << "\n\nError: Please enter values that have a difference of at least 10.\n\n";
			startingNumber = getNumbers("starting");
			endingNumber = getNumbers("ending");
		}

		//generates a random number between the starting and ending numbers
		numberGenerated = rand() % endingNumber + startingNumber;

		//calculates the number of guesses the user receives based on the worst case performance of binary search
		numGuesses = ceil(log(endingNumber - startingNumber) / log(2));

		cout << "Number generated between " << startingNumber << " and " << endingNumber << "." << endl;
		cout << "You have " << numGuesses << " attempts to guess the number. Good luck!" << endl;

		getGuesses(numberGenerated, numGuesses);

		cout << "Do you want to play again? (y/n): ";
		cin >> playAgain;
	}
}

int getNumbers(string pos) {
	int number;
	cout << "Please enter the " << pos << " number: ";
	cin >> number;
	
	//Ensures that the user entered an integer value
	while(cin.fail()) {
		cout << "\nError, please enter an integer: ";
		cin.clear();
		cin >> number;
	}

	return number; //returns the value inputted
}

bool testNumber(int numberGuessed, int numberGenerated, int numGuesses) {
	//tests if the number guessed is higher than, lower than, or equal to the number generated
	if(numberGuessed < numberGenerated) {
		cout << "Higher! You have " << numGuesses << " more attempts." << endl;
		return true;
	} else if(numberGuessed > numberGenerated) {
		cout << "Lower! You have " << numGuesses << " more attempts." << endl;
		return true;
	} else {
		cout << "Correct!" << endl;
		return false;
	}
}

void getGuesses(int numberGenerated, int numGuesses) {
	//runs the main functionality of the game, asks the user for a guess if the number of guesses is greater than 0
	int numberGuessed;
	bool guessing = true;
	while(guessing) {
		if(numGuesses > 0) {
			cout << "Please enter a guess: ";
			cin >> numberGuessed;
		} else {
			cout << "Game over! Better luck next time!" << endl;
			guessing = false;
			break;
		}

		numGuesses--;
		guessing = testNumber(numberGuessed, numberGenerated, numGuesses);
	}
}