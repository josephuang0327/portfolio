/*
Author: Wei Chieh Huang
Date:	18/Feb/2020
Description: The user will play a collection of a mini-games with the component(AI) and the one
			 with more points wins. The games will be randomly chosen. The second part is using
			 the macro function.
*/
//#include "Assignment2.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

#define sub_macro(num1,num2) (num1 - num2)
#define cube_macro(num1) (num1 * num1 * num1)
#define min_macro(num1, num2) ((num1 <= num2) ? num1 : num2)
#define odd_macro(num1) ((num1 % 2 == 0) ? 0 : 1)
int subf(int, int);
int cubef(int);
int minf(int, int);
int oddf(int);
// above are macro function

void macroFunc();
void EvenOdd();
void Menu();
void GenerateName();
void RPS();
void NumberGuess();
void DiceGame();
int CheckScore(int);
int RollDice(int);
int MinigameMenu(int);
int CheckEven(int, int);
// above are function initialization

int pScore = 0;
int opScore = 0;
int currentRounds = 0;
char opName[10];

int main (int argc, char *argv[])
{
	int option;
	int gameChooser = 0;
	int rounds = 0;
	bool optionCheck = false;
	// above is variable initialization
	GenerateName();
	Menu();						// prints the menu list
	cin >> option;				// user input option
	while(optionCheck == false)	// a loop for a invalid input to input again
	{
		if(option == 0)			//if user input 0 means quit
		{
			break;				// stop program
		}
		else if(option == 1)	// when input 1 means to play mini-games
		{
			cout << "Welcome to CSE240 Mini-Game Collection" << endl;
			cout << "I am your opponent " << opName << endl;
			rounds = MinigameMenu(rounds);		// call the mini-game menu function and ask for rounds
			currentRounds = rounds;
			while(currentRounds > 0)
			{
				gameChooser = rand() % 4;		// random from 0 ~ 3

				switch(gameChooser)				// choose what game to play with
				{
					case 0 :					// even odd game
						EvenOdd();
						cout << "\n" << endl;
						break;
					case 1 :					// rock paper Scissor game
						RPS();
						cout << "\n" << endl;
						break;
					case 2 :					// number guessing game
						NumberGuess();
						cout << "\n" << endl;
						break;
					case 3 :					// dice roll game
						DiceGame();
						cout << "\n" << endl;
						break;
					default :
						break;
				}

				currentRounds--;
				if(pScore == (rounds + 1) / 2)	// check if player wins
				{
					cout << "Congrats! You are the final winner! " << endl;
					break;
				}
				else if (opScore == (rounds + 1) / 2)	//check if opponent wins
				{
					cout << "The final winner is " << opName << " ! " << endl;
					break;
				}
			}
			optionCheck = true;					// stop the loop

		}
		else if(option == 2)					// when input 2 means go to macro code
		{
			optionCheck = true;					// stop loop
			macroFunc();
		}
		else									// user enter invalid input
		{
			cout << "Please type in a valid number!" << endl;
			cin >> option;						// re-input for the option
		}
	}



	return 0;
}

void macroFunc()
{
	int num1 = 10, num2 = 17;
	cout << "subf: " << subf(num1, num2) << endl;
	cout << "sub_macro: " << sub_macro(num1, num2) << "\n" << endl;			// works the same as previous line here

	num1 = 10, num2 = 17;
	cout << "subf: " << subf(num1++, num2--) << endl;						// subtract first than ++ or --

	num1 = 10, num2 = 17;
	cout << "sub_macro: " << sub_macro(num1++, num2--) << "\n" << endl;		// the result are the same here

	num1 = 10, num2 = 17;
	cout << "cubef: " << cubef(num1)<< endl;								// num1 = 12 , num2 = 15
	cout << "cube_macro: " << cube_macro(num1) << "\n" << endl;				// works the same as previous line here

	num1 = 10, num2 = 17;
	cout << "cubef: " << cubef(--num1) << endl;								// 9^3 = 7229

	num1 = 10, num2 = 17;
	cout << "cube_macro: " << cube_macro(--num1) << "\n" << endl;			// this function triplet the function which make num1 - 1 three times, become 9 * 8 * 7 = 504

	num1 = 10, num2 = 17;
	cout << "minf: " << minf(num1, num2) << endl;
	cout << "min_macro: " << min_macro(num1, num2) << "\n" << endl;			// works the same as previous line here

	num1 = 10, num2 = 17;
	cout << "minf: " << minf(--num1, --num2) << endl;						// both -1 which is 9 and 16 return 9

	num1 = 10, num2 = 17;
	cout << "min_macro: " << min_macro(--num1, --num2) << "\n" << endl;		// both minus two because macro duplicate --num which is 8 and 15 return 8

	num1 = 10, num2 = 17;
	cout << "oddf: " << oddf(num1) << endl;
	cout << "odd_macro: " << odd_macro(num1) << "\n" << endl;				// works the same as previous line here

	num1 = 10, num2 = 17;
	cout << "oddf: " << oddf(num1++) << endl;

	num1 = 10, num2 = 17;
	cout << "odd_macro: " << odd_macro(num1++) << "\n" << endl;				// the result are the same here

}
int subf(int num1, int num2)
{
	return num1 - num2;
}
int cubef(int num1)
{
	return num1 * num1 * num1;
}
int minf(int num1, int num2)
{
	if(num1 <= num2)
	{
		return num1;
	}
	else
	{
		return num2;
	}
}
int oddf(int num1)
{
	if(num1 % 2 == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}




int CheckScore(int checkPoint)					// check score function to display score
{
	if(checkPoint == 1)							// if player wins player score + 1
	{
		pScore += 1;
	}
	else if (checkPoint == 0)					// if opponent wins opponent score + 1
	{
		opScore += 1;
	}
	cout << "\n" << endl;
	cout << "Player Score - " << pScore << endl;
	cout << opName << " Score - " << opScore << endl;
	return 0;
}


void EvenOdd()									// even odd game function
{
	int guess;
	int numberInput;
	int randNumPick;
	int total;
	int pWinCheck = 0;
	// above is variable initialization

	cout << "Even/Odd game!" << endl;
	cout << "Guess even or odd! (0 for even, 1 for odd): " << endl;
	cin >> guess;								// ask user for guessing even or odd

	while(guess != 0 && guess != 1)				// if the user input other than 1 or 0, than ask for input again
	{
		cout << "Invalid! Please enter 0 for even, 1 for odd" << endl;
		cin >> guess;
	}

	cout << "Enter a number (between 0 to 100): " << endl;
	cin >> numberInput;							// ask for a number between 0 to 100
	while(numberInput < 0 || numberInput > 100)	// if the user input exceed the range, than ask for input again
	{
		cout << "Invalid! Please enter a number between 0 to 100" << endl;
		cin >> numberInput;
	}
	srand(time(NULL));							// let the rand() function keep changing
	randNumPick = rand() % 100;					// get random number from 0 to 100
	cout << opName << " picked " << randNumPick << endl;

	total = CheckEven(numberInput, randNumPick);// call checkEven function to check for even

	if(total == 1) 								// total = even number
	{
		if(guess == 0) 							// user guess even
		{
			cout << "Congratulations you win this round!" << endl;
			pWinCheck = 1;
			CheckScore(pWinCheck);
		}
		else									// user guess odd
		{
			cout << opName << " wins this round" << endl;
			CheckScore(pWinCheck);
		}
	}
	else 										// total = odd number
	{
		if(guess == 1) 							// user guess odd
		{
			cout << "Congratulations you win this round!" << endl;
			pWinCheck = 1;
			CheckScore(pWinCheck);
		}
		else 									// user guess even
		{
			cout << opName << " wins this round" << endl;
			CheckScore(pWinCheck);
		}
	}

}
int CheckEven(int num1, int num2)				// check total is even
{
	int total;
	bool isEven = false;
	total = num1 + num2;						// add two number together
	if(total % 2 == 0)							// if is even
	{
		cout << num1 << " + " << num2 << " = " << total << " - Even!" << endl;
		isEven = true;
	}
	else
	{
		cout << num1 << " + " << num2 << " = " << total << " - Odd!" << endl;
		isEven = false;
	}
	if(isEven == true)							// set return value
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void RPS()
{
	int playerRPS;
	int opRPS;
	int pWinCheck = 0;

	cout << "Rock, Paper, Scissors game!" << endl;
	cout << "Choose a throw!" << endl;
	cout << "1. Rock" << endl;
	cout << "2. Paper" << endl;
	cout << "3. Scissors" << endl;
	cin >> playerRPS;

	while(playerRPS != 1 && playerRPS != 2 && playerRPS != 3)	// if input invalid numbers
	{
		cout << "Invalid!" << endl;
		cout << "Choose a throw!" << endl;
		cout << "1. Rock" << endl;
		cout << "2. Paper" << endl;
		cout << "3. Scissors" << endl;
		cin >> playerRPS;
	}
	srand(time(NULL));
	opRPS = rand() %3 + 1;							//choose from 1~3 Rock, Paper, Scissors
	if(opRPS == 1)
	{
		cout << "\n"  << opName << " throws Rock! " << endl;
	}
	else if(opRPS == 2)
	{
		cout << "\n"  << opName << " throws Paper! " << endl;
	}
	else
	{
		cout << "\n"  << opName << " throws Scissors! " << endl;
	}

	if(playerRPS == opRPS)												// condition for tie
	{
		while(playerRPS == opRPS)										// if it is a tie go again
		{
			cout << "It's a tie!! Go again!" << endl;
			cout << "Choose a throw!" << endl;
			cout << "1. Rock" << endl;
			cout << "2. Paper" << endl;
			cout << "3. Scissors" << endl;
			cin >> playerRPS;
			while(playerRPS != 1 && playerRPS != 2 && playerRPS != 3)	// if player input invalid number
			{
				cout << "Invalid!" << endl;
				cout << "Choose a throw!" << endl;
				cout << "1. Rock" << endl;
				cout << "2. Paper" << endl;
				cout << "3. Scissors" << endl;
				cin >> playerRPS;
			}
			opRPS = rand() %3 + 1;
			if(opRPS == 1)								// tells the player what the opponent throw
			{
				cout << "\n" << opName << " throws Rock! " << endl;
			}
			else if(opRPS == 2)
			{
				cout << "\n" << opName << " throws Paper! " << endl;
			}
			else
			{
				cout << "\n" << opName << " throws Scissors! " << endl;
			}
		}
	}
	if(playerRPS != opRPS)								// when player is not tie with opponent
	{
		if(playerRPS == 1)								// if player shoot rock
		{
			if(opRPS == 3)								// if opponent shoot scissors
			{
				cout << "You win this round!" << endl;
				pWinCheck = 1;
				CheckScore(pWinCheck);					// call score function
			}
			else										// otherwise opponent wins
			{
				cout << opName << " wins this round!" << endl;
				CheckScore(pWinCheck);					// call score function

			}
		}
		else if(playerRPS == 2)							// if player shoot paper
		{
			if(opRPS == 1)								// if player shoot rock
			{
				cout << "You win this round!" << endl;
				pWinCheck = 1;
				CheckScore(pWinCheck);					// call score function
			}
			else										// otherwise opponent wins
			{
				cout << opName << " wins this round!" << endl;
				CheckScore(pWinCheck);
			}
		}
		else											// if player shoot scissors
		{
			if(opRPS == 2)								// if opponent shoot paper
			{
				cout << "You win this round!" << endl;
				pWinCheck = 1;
				CheckScore(pWinCheck);					// call score function
			}
			else										// otherwise opponent wins
			{
				cout << opName << " wins this round!" << endl;
				CheckScore(pWinCheck);					// call score function
			}
		}
	}
}

void NumberGuess()						//number guessing game
{
	int guessCount = 1;
	int range1, range2 = 0;
	int randomNumber;
	int rangeDiff = 0;
	int playerGuess;
	int pWinCheck = 0;
	// initailize variable above

	srand(time(NULL));					// set the rand() function for it to keep changing
	range1 = rand() %1000;				// random range1 from 0 to 1000
	range2 = rand () %1000;				// random range2 from 0 to 1000

	if(range1 > range2)					// to get a positive difference
	{
		rangeDiff = range1 - range2;		// find the difference
	}
	else if(range2 > range1)
	{
		rangeDiff = range2 - range1;
	}

	while(rangeDiff < 30 || rangeDiff > 100)		// if range difference is smaller than 30 or larger than 100 do it again
	{
		range1 = rand() %1000;						// random range1
		range2 = rand () %1000;						// random range2
		if(range1 > range2)
		{
			rangeDiff = range1 - range2;			// find the difference
		}
		else if(range2 > range1)
		{
			rangeDiff = range2 - range1;
		}
	}

	if(range1 < range2)								// range1 is smaller than be the first number
	{
		randomNumber = rand() %(range2 - range1) + range1;
		cout << "Player I'm thinking of a number between " << range1 << " to " << range2 << endl;
	}
	else											// range2 is smaller than be the first number
	{
		randomNumber = rand() %(range1 - range2) + range2;
		cout << "Player I'm thinking of a number between " << range2 << " to " << range1 << endl;

	}

	cout << "Number Guessing Game!" << endl;
	//cout << "The random number is " <<  randomNumber << endl;
	cout << "You have 5 guesses" << endl;

	while(guessCount < 6 && randomNumber != playerGuess)	// let the player play 5 times and check if hits the number
	{
		cout << "What guesses # "<< guessCount << " ? " << endl;
		cin >> playerGuess;
		if(playerGuess < randomNumber)
		{
			cout << "Higher!" << endl;
		}
		else if(playerGuess > randomNumber)
		{
			cout << "Lower!" << endl;
		}
		guessCount += 1;
	}
	if(playerGuess == randomNumber && guessCount <= 6)		// if player guess correct within 5 attempt
	{
		cout << "The random number is " <<  randomNumber << endl;
		cout << "You wins this round " << endl;
		pWinCheck = 1;
		CheckScore(pWinCheck);								// call score function
	}
	else													// if player guess wrong after 5 attempt
	{
		cout << "The random number is " <<  randomNumber << endl;
		cout << opName << " wins this round " << endl;
		pWinCheck = 0;
		CheckScore(pWinCheck);								// call score function
	}

}

void DiceGame()												// Dice Game
{
	int playerTotal = 0;
	int opTotal = 0;
	int diceAmount;
	int diceSides;
	int diceNum;
	int i;
	int pWinCheck = 0;
	// initialization above

	cout << "Dice Roll Showdown!" << endl;
	cout << "How many sides do the dice have (input a positive number) : " << endl;
	cin >> diceSides;										// ask for sides of dice


	while(diceSides <= 0)									// check for positive numbers
	{
		cout << "Please enter a positive number!" << endl;
		cin >> diceSides;
	}

	cout << "How many dice will each player roll? (input a positive number) : " << endl;
	cin >> diceAmount;
	while(diceAmount <= 0)									// check for positive numbers
	{
		cout << "Please enter a positive number!" << endl;
		cin >> diceAmount;
	}

	srand(time(NULL));
	cout << "Player Rolled:" << endl;
	for(i = 0; i < diceAmount; i++ )						// roll amount of dice player wants
	{
		diceNum = RollDice(diceSides);						// call the RollDice Function
		cout << diceNum << endl;
		playerTotal += diceNum;								// Add for total
	}
	cout << "Total: " << playerTotal << endl;

	cout << opName <<" Rolled:" << endl;
	for(i = 0; i < diceAmount; i++ )						// same loop for the opponent
	{
		diceNum = RollDice(diceSides);						// function of RollDice
		cout << diceNum << endl;
		opTotal += diceNum;									// opponents total
	}
	cout << "Total: " << opTotal << endl;

	if(playerTotal > opTotal)								// if player total larger than opponent
	{
		cout << "You wins this round!" << endl;
		pWinCheck = 1;
		CheckScore(pWinCheck);								// call score function
	}
	else if (playerTotal < opTotal)							// if opponent larger than player
	{
		cout << opName << " wins this round!" << endl;
		CheckScore(pWinCheck);
	}
	else													// if tie
	{
		cout << "It's a TIE !!" << endl;
		currentRounds += 1;
		pWinCheck = 2;
		CheckScore(pWinCheck);								// call score function
	}

}
int RollDice(int sides)										// require function
{
	int randomSides;
	randomSides = (rand() % sides) + 1;						// random the value of dice
	return randomSides;
}

void Menu()
{
	cout << "Welcome to the CSE240 Assignment 2!\n" << endl;
	cout << "Menu:" << endl;
	cout << "1 - CSE240 Mini-Game Collection" << endl;
	cout << "2 - Macros vs Functions Throw-down" << endl;
	cout << "0 - Exit\n" << endl;
	cout << "Choose an option:" << endl;
}
int MinigameMenu(int rounds)								// function of rounds to play
{

	cout << "How many rounds should we play? (Choose and odd number)" << endl;
	cin >> rounds;
	while(rounds % 2 == 0 || rounds <= 0)
	{
		cout << "Please enter a positive odd number!" << endl;
		cin >> rounds;
	}
	return rounds;
}
void GenerateName()										//Generate name
{
	int randName;
	srand(time(NULL));
	randName = rand() % 100;							// random in 100 names

	FILE *infile;										// pointer to file
	//infile = fopen("//Users//joseph//Downloads//random_names.txt","r");	// open file
	infile = fopen("random_names.txt","r");
	int i;
	//cout << "rand num:  " << randName << endl;
	if(infile != NULL)									// check if file open
	{
		cout << "The file did open" << endl;			// check if file open than tell user
		for(i = 0; i < randName; i++)
		{
			fscanf(infile, "%s", opName);
			//cout << opName << endl;					// print the scan
		}
	}
	else
	{
		cout << "The random_name.txt file did not open" << endl;
	}
	fclose(infile);										// close file
}
