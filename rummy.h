
#ifndef __RUMMY_H__
#define __RUMMY_H__

using namespace std;

struct State {
	vector<int> deck;
	vector<int> agentHand;
	vector<int> userHand;
	list<int> remaining;
	int turnCard;
};


void swap(vector<int> &cards, int pos1, int pos2);


void shuffle(vector<int> &deck);


vector<int> getNewDeck();


list<int> initializeRemaining();


void dealCards(vector<int> &deck, vector<int> &userHand, vector<int> &agentHand);


void adjustRemaining(list<int> &remaining, vector<int> hand);


State initializeState();


char getSuit(int i);


char getRank(int i);


void printOpponentHandandDeck();


void printTurnCard(int v);


void printHand(vector<int> hand);


void printState(State state);



void merge(vector<int> integers, int a1, int a2, int b1, int b2, vector<int> &output);


void mergeSort(vector<int> &integers, int start, int finish);

bool isWinner(vector<int> hand);


bool gameOver(State state);

void playUserTurn(State &state);


int evaluate(State state);

bool takeTurnCard(State state);


int removeWorstCard(State &state);

void playAgentTurn(State &state);

#endif
