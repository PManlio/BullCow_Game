#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map // to make syntax UnrealEngine4 friendly

// constructor ---> ci permette di modificare i valori privati della classe FBullCowGame.h
FBullCowGame::FBullCowGame() { 
	Reset(); 
}
// quando crei un nuovo elemento, avente Classe FBullCowGame, questo costruttore verrà invocato automaticamente

// ste prime due funzioni non servono ad altro se non a restituire i valori delle variabili private della classe FBullCowGame.h
// in sostanza, sono i costruttori, tramite cui possiamo accedere alle variabili di classe (nello specifico, sono i Getter)
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3, 4}, {4, 7}, {5, 10}, {6, 16}, {7, 20} }; // {lunghezza_della_parola, numero_di_tentativi}; map è una tabella, in sostanza.
	return WordLengthToMaxTries[MyHiddenWord.length()]; // qua passiamo il primo parametro, ossia la lunghezza della parola; il numero di tentativi ci sarà restituito appositamente
}

void FBullCowGame::Reset() {
	const FString HIDDEN_WORD = "planet"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const{
	if (!IsIsogram(Guess)) { //if the guess isn't an isogram
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) { //if the guess isn't all lowercase 
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) { //if the guess length is wrong
		return EGuessStatus::Wrong_Length; 
	}
	else return EGuessStatus::OK;
}

// receives a VALID guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess){

	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {

		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {

			// if they match, then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				// if they're in the same place
				if (MHWChar == GChar) {
					BullCowCount.Bulls++; // increment bulls
				}
				else {
					BullCowCount.Cows++; // increment cows
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	// setup our map del tipo TMap<char, bool> LetterSeen;
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) { // e cioè "esegui il ciclo for per tutte le lettere della parola Word

		Letter = tolower(Letter); //metodo che prende la singola lettera e, se è in Uppercase, la porta al lowercase

		if (LetterSeen[Letter]) {// if the letter is in the map we do NOT have an isogram
			return false;
		}
		else { // add the letter to the map as seen
			LetterSeen[Letter] = true;
		}		
	}
	return true; // for expample in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const {
	for (auto Letter : Word) {
		if (!islower(Letter)) { // if not a lowercase letter turn false
			return false;
		}
		else { // otherwiise turn true
			return true;
		}
	}
	return false;
}
