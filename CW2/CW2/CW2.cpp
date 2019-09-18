//Wang Jinhao psyjw19 4302178
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, const char* argv[]) {
	vector<string> wordsList;
	string word;
	
	if (argc == 1) {
		ifstream fin("wordlist.txt");
		while (!fin.eof()) {
			fin >> word;
			wordsList.push_back(word);
		}
	}
	else if (argc == 2) {
		ifstream fin(argv[1]);
		if (!fin) {
			cout << "File doesn't exit.\n";
			return 0;
		}
		while (!fin.eof()) {
			fin >> word;
			wordsList.push_back(word);
		}
	}
	else if (argc > 2) {
		cout << "Invalid command line arguments!\n";
		return 0;
	}

	const int wordsNum = wordsList.size();
	
	char replay = NULL;
	char myGuess;

	srand(time(NULL));		//if there is no command line argument as the seed

	while (true) {
		
		int life = 8;		//the maximum number of wrong guesses
		int correct = 0;		//how many characters in a word that the player has guessed right
		string alphabeta = "abcdefghijklmnopqrstuvwxyz";

		int counter = rand() % wordsNum;		//choose an index randomly
				
		const string chosen = wordsList[counter];		//store the chosen words
		const int length = chosen.size();

		string guess;		//store the current progress of the game
		guess.resize(length, '-');

		while (life > 0) {
			bool judge = false;		//whether the player has guessed a character correctly
			bool repeat = true;		//whether the player guesses a character which (s)he has guessed before
			cout << "\nGuess a letter for the word: '" << guess << "'\nYou have " << life << " wrong guesses left, and have guessed " << correct << " letters out of " << length << " so far.\nAvailable letters are: " << alphabeta << "\n" << endl;
			while (true) {
				cin >> myGuess;
				myGuess = tolower(myGuess);
				if (myGuess == '\n') {
					continue;
				}
				else if (myGuess < 97 || myGuess > 122) {		//input validation check
					cout << "'" << myGuess << "' is not a valid letter! Try again.\n" << endl;
					//printf("'%c' is not a valid letter! Try again.\n", myGuess);
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
				cout << "\n!!! You already tried '" << myGuess << "' !!!\n" << endl;
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
				cout << "\n *** Correct guess - '" << myGuess << "' IS in the word ***\n" << endl;
				if (correct == length) {		//if the player has guessed all characters
					cout << "\nWell done! The word was " << chosen << ". You finished with " << life << "wrong guesses left.\n" << endl;
					break;
				}
			}
			if (judge == false) {		//if the character is guessed wrong
				life = life - 1;
				cout << "\n!!! Wrong guess -'" << myGuess << "' is not in the word !!!\n" << endl;
				if (life == 0) {		//if the player has consumed the maximum number of guess
					cout << "\nYou failed. The word was " << chosen << "\n" << endl;
					break;
				}
			}
		}
		
		printf("Try again?(y/n)");
		while (true) {
			cin >> replay;
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
	

