// Author: Andrew Cassidy
// Date: 1/27/20
// Description: Assignment 1 for CS315. Creates a game called cards
// that implements a decks/piles of cards using doubly linked list structures
// and arrays that stores these structures for n players.

#include <iostream>
#include "LList.h"

using namespace std;

int randReduce(int randNum, int rangeRange) {
	// Converts a large pseudo-random number randNum
	// to one in the range 1 to rangeRange.
	return (randNum % rangeRange) + 1;
}

int checkWeight(LList players[], int numPlayers) {
	// check if any player has a weight = 0; if so, they have won!
	// will return the player number or -1 if no one won
	int answer = -1;
	for (int i = 0; i < numPlayers; i++) {
		if (players[i].getWeight() == 0) {
			return i + 1;
		}
	}
	return answer;
}

int main(int argc, char * argv[]) {
	// get turns, cards and player totals
	const int NUM_PLAYERS = stoi(argv[1]);
	const int NUM_CARDS = stoi(argv[2]);
	const int NUM_TURNS = stoi(argv[3]);
	// error handling on last 3 inputs
	if (NUM_PLAYERS <= 0 || NUM_CARDS <= 0 || NUM_TURNS <= 0) {
		cout << "ERROR: invalid input(s)\nExiting game...\n";
		return 0;
	}
	// title screen!
	cout << "Cards!\nBy: Andrew Cassidy\n\n";
	// make array of the players
	LList players[NUM_PLAYERS];
	// initialize all player decks with each deck of length NUM_CARDS
	for (int i = 0; i < NUM_PLAYERS; i++) {
		for (int j = 0; j < NUM_CARDS; j++) {
			node * newCard = new node;
			newCard->setKey(NUM_CARDS - j);
			players[i].insertTop(newCard);
		}	
	}
	// important values while the game goes on
	int currTurn = 1;
	int winner = -1;
	int randNum;
	// game loop
	while (currTurn <= NUM_TURNS && winner == -1) {
		cout << "turn " << currTurn << ": ";
		// get random number from stdin
		cin >> randNum;
		// NUM_PLAYERS sided die roll. determines who's turn it is
		int currPlayer = randReduce(randNum, NUM_PLAYERS);
		cout << "player " << currPlayer;
		// currPlayer rolls 2 sided die and a NUM_PLAYERS (n) sided die
		cin >> randNum;
		int twoSidedRoll = randReduce(randNum, 2);
		cin >> randNum;
		int nSidedRoll = randReduce(randNum, NUM_PLAYERS);
		cout << " send a card to " << nSidedRoll;
		// currPlayer decides to discard from top or bot to player nSidedRoll
		if (currPlayer != nSidedRoll) {
			// if we're sending a card to a diff person off the top of deck
			if (twoSidedRoll == 1) {
				cout << ", from top\n";
				node * removedCard = players[currPlayer - 1].removeTop();
				players[nSidedRoll - 1].insertTop(removedCard);
			}
			// if we're sending a card to a diff person off the bot of deck
			else {
				cout << ", from bottom\n";
				node * removedCard = players[currPlayer - 1].removeBot();
				players[nSidedRoll - 1].insertTop(removedCard);
			}
		}
		else {
			// if we're sending a card from ourself from bot of deck
			if (twoSidedRoll == 2) {
				cout << ", from bottom\n";
				node * removedCard = players[currPlayer - 1].removeBot();
				players[currPlayer - 1].insertTop(removedCard);
			}
			// send card from ourself off top deck is same as doing nothing
			else
				cout << ", from top\n";
		}
		// print the players and their weights
		for (int i = 0; i < NUM_PLAYERS; i++) {
			cout << "\tplayer " << i+1 << ": weight: ";
			cout << players[i].getWeight() << endl;
		}
		// turn is over. go back up and do it again!
		currTurn += 1;
		// check if there is a winner
		winner = checkWeight(players, NUM_PLAYERS);
	}
	// if game ended with no winner, make person with smallest weight win
	if (winner == -1) {
		int smallestWeight = 100000000;
		// search for the first player with smallest weight
		for (int i = 0; i < NUM_PLAYERS; i++) {
			if (players[i].getWeight() < smallestWeight) {
				smallestWeight = players[i].getWeight();
				winner = i + 1;
			}
		}
		cout << "Game is over [turn limit reached]; player " << winner;
		cout << " has the smallest weight.\n";
	}
	else
		cout << "Game is over; player " << winner << " has no cards left.\n";
	return 0;
}
