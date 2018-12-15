/*  This is the console executable, that makes use of
	the BullCow class
	this acts as the view in a MVC pattern, and is responsible for all
	user interaction. For game logic, see the FBullCowGame class.
*/ // per il TODO vai su View -> Task List (Ctrl+T)
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax UnrealEngine4 friendly
using FText = std::string; //FText viene utilizzato solo per gli output dell'utente (e quindi si utilizza nel main()). All'interno, useremo FString
using int32 = int;

// methods & function prototypes
void PrintIntro();
FText GetValidGuess();
void PlayGame();
void PrintBack(FText);
bool AskToPlayAgain();
void PrintGameSummary();

// instanciating the object FBullCowGame
FBullCowGame BCGame;


int main() {
	bool bPlayAgain;
	do {
		PrintIntro();
		PlayGame();

		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain); //andava bene pure chiamare il metodo AskToPlayAgain() all'interno del while, tanto restituisce un TRUE/FALSE

	//NewFunction(); //esempio per l'opzione di visual studio: extract function

	return 0;
}

void PrintIntro() {
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n\n\n";
	return;
}

void PlayGame() {
	
	BCGame.Reset(); //il metodo Reset riporta i valori MyCurrentTry e MyMaxTries ai loro valori di costruttore (quelli di default, va)

	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << MaxTries << std::endl;

	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		// submit valid guess to the game & receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ", Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

// loop continually until the user give a valid word
FText GetValidGuess() {
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status; //uno stato che non sia nessuno di quelli scritti sotto, giusto per avviare il loop senza problemi
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "\nTry no. " << CurrentTry << " of " << BCGame.GetCurrentTry() << std::endl;
		std::cout << "\n\nEnter your guess: \n";
		std::getline(std::cin, Guess);

		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram (you have to write a word without repeating letters).\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all in lowercase.\n\n";
			break;
		default:
			Status = EGuessStatus::OK;
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

void PrintBack(FText Guess) {
	std::cout << "your guess is: " << Guess << " ?\n\n\n";
}

bool AskToPlayAgain(){
	std::cout << "Do you want to play again with the same word? (y/n) " << std::endl;
	FText Response = "";
	std::getline(std::cin, Response);

	return ((Response[0] == 'y') || (Response[0] == 'Y'));
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "\tGG - YOU WIN!!\n\n";
	}
	else {
		std::cout << "\tSUCH BAD LUCK!\n\n";
	}
}