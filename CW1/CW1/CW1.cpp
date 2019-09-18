//Wang Jinhao psyjw19 4302178
#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>

int main(int argc, const char* argv[])
{
	const char* wordsList[] = { "chaos", "liar", "gray", "available", "tomorrow" };		//store optional words
	const int wordsNum = sizeof(wordsList) / sizeof(char*);		//calculate the number of optional words (for randing)
	char replay = NULL;		//check whether the player wants to retry	
	char myGuess;		//store the character which the player puts in

	if (argc == 1) {
		srand(time(NULL));		//if there is no command line argument as the seed
	}
	else if (argc == 2) {
		srand(atoi(argv[1]));		//take command line argument as the seed
	}
	else {
		printf("The program should run with none or a single number of command line arguments.\n");		//command line argument validation check
		return 0;
	}
	
	while (true) {
		int life = 8;		//the maximum number of wrong guesses
		int correct = 0;		//how many characters in a word that the player has guessed right
		char alphabeta[27] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','\0' };
		
		int counter = rand() % wordsNum;		//choose an index randomly
		int length = strlen(wordsList[counter]);		//calculate the length of the chosen words
		const char* chosen = wordsList[counter];		//store the chosen words
		
		char* guess = (char*)malloc(length + 1);		//store the current progress of the game
		for (int i = 0; i < length; i++) {
			guess[i] = '-';
		}
		guess[length] = 0;

		while (life > 0) {
			bool judge = false;		//whether the player has guessed a character correctly
			bool repeat = true;		//whether the player guesses a character which (s)he has guessed before
			printf("\nGuess a letter for the word: '%s'\nYou have %d wrong guesses left, and have guessed %d letters out of %d so far.\nAvailable letters are: %s\n", guess, life, correct, length, alphabeta);
			while (true) {
				scanf_s("%c", &myGuess);
				if (myGuess == '\n') {
					continue;
				}
				else if (64 < myGuess && myGuess < 91) {		//if the character is uppercase, transform into lowercase
					myGuess = myGuess + 32;
					break;
				}
				else if (myGuess < 97 || myGuess > 122) {		//input validation check
					printf("'%c' is not a valid letter! Try again.\n", myGuess);
					continue;
				}
				else {
					break;
				}
			}
			
			for (int i = 0; i < 26; i++) {
				if (myGuess == alphabeta[i]) {		//turn the character, which is guessed by the player, in the alphabeta into dot
					alphabeta[i] = '.';
					repeat = false;
					break;
				}
			}
			if (repeat == true) {		//if no character in the alphabeta matches the guess character
				printf("\n!!! You already tried '%c' !!!\n", myGuess);
				continue;
			}
			for (int i = 0; i < length; i++) {		//compare with the chosen word and display the character which is guessed right
				if (myGuess == chosen[i]) {
					guess[i] = chosen[i];
					judge = true;
					correct = correct + 1;
				}
			}
			if (judge == true) {		//if the character is guessed right
				printf("\n*** Correct guess - '%c' IS in the word ***\n", myGuess);
				if (correct == length) {		//if the player has guessed all characters
					printf("\nWell done! The word was '%s'. You finished with %d wrong guesses left.\n", chosen, life);
					break;
				}
			}
			if (judge == false) {		//if the character is guessed wrong
				life = life - 1;
				printf("\n!!! Wrong guess - '%c' is not in the word !!!\n", myGuess);
				if (life == 0) {		//if the player has consumed the maximum number of guess
					printf("\nYou failed. The word was '%s'\n", chosen);
					break;
				}
			}
		}
		free(guess);
		guess = NULL;
		printf("Try again?(y/n)");
		while (true) {
			scanf_s("%c", &replay);
			if (replay == 'y' || replay == 'Y') {		//if the player wants to retry
				while ((replay = getchar()) != '\n');		//clear the standard input stream
				break;
			}
			if (replay == 'n' || replay == 'N') {		//if the player doesn't want to retry
				return 0;
			}
		}
	}
    return 0;
}

