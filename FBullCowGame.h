#pragma once
#include <string>

// to make syntax UnrealEngine4 friendly
using FString = std::string;
using int32 = int;

// all values initialised to zero
struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};


// se tu crei degli enum -senza specificare CLASS dopo enum, e metti dei nomi uguali (vedi OK) avremo errore;
// scrivendo CLASS dopo enum, forziamo la creazione di una classe differente, con cui possiamo utilizzare anche nomi che altrimenti sarebbero già impegnati
enum class EGuessStatus { //la classe enum è una lista di valori.
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};


class FBullCowGame {
public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	void Reset();
	EGuessStatus CheckGuessValidity(FString) const; //prima questo metodo era BOOL. Così facendo ne abbbiamo sostituito il valore di ritorno, con una enum
	
	// counts bulls & cows, and increasing try numbers assmuming valid guess
	FBullCowCount SubmitValidGuess(FString);

private: //valori iniziali che si possono modificare tramite il costruttore definito in FBullCowGame.cpp
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	// metodi private
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};