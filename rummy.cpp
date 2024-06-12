#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <ctime>
#include "rummy.h"
using namespace std;

int main(int argc, char **argv)
{
	State state = initializeState();
	printState(state);
	while (gameOver(state) == false)
	{
		playUserTurn(state);
		if (gameOver(state))
			break;
		playAgentTurn(state);
		printState(state);
	}
	return 0;
}


void swap(vector<int> &cards, int pos1, int pos2)
{
	int temp = cards[pos1];
	cards[pos1] = cards[pos2];
	cards[pos2] = temp;
}


void shuffle(vector<int> &deck)
{
	srand(time(NULL));
	int size = deck.size();
	for (int i = size-1; i >0; i--)
	{
		int swapPos = rand() % i;
		swap(deck, i, swapPos);
	}
}


vector<int> getNewDeck()
{
	vector<int> deck;
	for (int i = 0; i < 52; i++)
	{
		deck.push_back(i);
	}
	shuffle(deck);
	return deck;
}


list<int> initializeRemaining()
{
	list<int> remaining;
	for (int i = 0; i < 52; i++)
		remaining.push_back(i);
	return remaining;
}


void dealCards(vector<int> &deck, vector<int> &userHand, vector<int> &agentHand)
{
	for (int i = 0; i < 14; i ++)
	{
		int topCard = deck.back();
		deck.pop_back();
		if (i%2 == 0)
			userHand.push_back(topCard);
		else
			agentHand.push_back(topCard);
	}
}


void adjustRemaining(list<int> &remaining, vector<int> hand)
{
	for (int i = 0; i < hand.size(); i++)
		remaining.remove(hand[i]);
}


State initializeState()
{
	State state;
	state.deck = getNewDeck();
	state.remaining = initializeRemaining();
	dealCards(state.deck, state.userHand, state.agentHand);
	adjustRemaining(state.remaining, state.agentHand);
	mergeSort(state.userHand, 0, state.userHand.size());
	state.turnCard = 52;
	return state;
}


char getSuit(int i)
{
	if (i < 13)
		return '&';
	else if (i < 26)
		return '%';
	else if (i < 39)
		return '$';
	else
		return '@';
}


char getRank(int i)
{
	int rank = i % 13;
	if (rank == 0)
		return 'A';
	if (rank == 1)
		return '2';
	if (rank == 2)
		return '3';
	if (rank == 3)
		return '4';
	if (rank == 4)
		return '5';
	if (rank == 5)
		return '6';
	if (rank == 6)
		return '7';
	if (rank == 7)
		return '8';
	if (rank == 8)
		return '9';
	if (rank == 9)
		return 'T';
	if (rank == 10)
		return 'J';
	if (rank == 11)
		return 'Q';
	return 'K';
}

void printOpponentHandandDeck()
{

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 56; j++)
		{
			int k = j % 8;
			if (k == 7)
				cout << "* ";
			else if (i == 0 || i == 9 || k == 0)
				cout << "*";
			else
				cout << "?";
		}
		cout << endl;
	}
	cout << endl;


	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i == 0 || i == 9 || j == 0 || j == 7)
				cout << "*";
			else
				cout << "?";
		}
		cout << endl;
	}
	cout << endl;
}


void printTurnCard(int v)
{
	char suit = getSuit(v);
	char rank = getRank(v);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i == 0 || i == 9 || j == 0 || j == 7)
				cout << "*";
			else if ((j == 1 && i == 1) || (j == 6 && i == 8) || (j == 3 && i == 4))
				cout << rank;
			else if ((j == 6 && i == 1) || (j == 1 && i == 8) || (j == 4 && i == 5))
				cout << suit;
			else
				cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void printHand(vector<int> hand)
{
	int size = hand.size();
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < size; j++)
		{
			char rank = getRank((hand[j]));
			char suit = getSuit((hand[j]));
			for (int k = 0; k < 8; k++)
			{
				if (k == 7)
					cout << "* ";
				else if (i == 0 || i == 9 || k == 0)
					cout << "*";
				else if ((k == 1 && i == 1) || (k == 6 && i == 8) || (k == 3 && i == 4))
					cout << rank;
				else if ((k == 6 && i == 1) || (k == 1 && i == 8) || (k == 4 && i == 5))
					cout << suit;
				else
					cout << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

void printState(State state)
{

	printOpponentHandandDeck();
	if (state.turnCard < 52)
		printTurnCard(state.turnCard);
	printHand(state.userHand);
}


void merge(vector<int> integers, int a1, int m, int b2, vector<int> &output)
{
	int a2, b1;
	a2 = b1 = m;
	while (a1 < a2 && b1 < b2)
	{
		if (integers[a1] <= integers[b1])
			output.push_back(integers[a1++]);
		else
			output.push_back(integers[b1++]);
	}

	while (a1 < a2)
		output.push_back(integers[a1++]);
	while (b1 < b2)
		output.push_back(integers[b1++]);
}

void mergeSort(vector<int> &integers, int start, int finish)
{
	if ((finish - start) <= 1)
		return;
	int m = (finish - start) / 2;
	mergeSort(integers, start, start+m);
	mergeSort(integers, start+m, finish);

	vector<int> temp;
	merge(integers, start, start+m, finish, temp);
	int tempIndex = 0;
	for (int i = start; i < finish; i++)
		integers[i] = temp[tempIndex++];
}

bool isWinner(vector<int> hand)
{
	mergeSort(hand, 0, hand.size());


	if (hand[0] % 13 < 10 && hand[1] == hand[0] + 1 && hand[2] == hand[0] + 2
				&& hand[3] == hand[0] + 3)
	{

		if (hand[4] % 13 < 11 && hand[5] == hand[4] + 1 && hand[6] == hand[4] + 1)
			return true;

		if (hand[4] % 13 == hand[5] % 13 && hand[4] % 13 == hand[6] % 13)
			return true;
	}


	if (hand[0] % 13 < 11 && hand[1] == hand[0] + 1 && hand[2] == hand[0] + 2)
	{

		if (hand[3] % 13 < 10 && hand[4] == hand[3] + 1 && hand[5] == hand[3] + 2
					&& hand[6] == hand[3] + 3)
			return true;

		if (hand[3] % 13 == hand[4] % 13 && hand[3] % 13 == hand[5] % 13
					&& hand[3] % 13 == hand[6] % 13)
			return true;
	}

	vector<int> nonMatches;
	for (int i = 0; i < hand.size(); i++)
	{
		if (hand[i] % 13 != hand[0] % 13)
			nonMatches.push_back(hand[i]);
	}

	if (nonMatches.size() != 3 && nonMatches.size() != 4)
		return false;

	bool areInARow = true;
	for (int i = 0; i < nonMatches.size(); i++)
	{
		if (nonMatches[i] != nonMatches[0] + i)
			areInARow = false;
	}
	if (areInARow)
		return true;

	for (int i = 0; i < nonMatches.size(); i++)
	{
		if (nonMatches[i] % 13 != nonMatches[0] % 13)
			return false;
	}
	return true;
}

/*
 * True deðer dönerse kaybediyoruz
 * False dönerse berabere
 */
bool gameOver(State state)
{
	/* Kazanip kazanmadigimizi kontrol ediyoruz */
	if (isWinner(state.userHand))
	{
		cout << "Kazandýn!" << endl;
		printHand(state.userHand);
		return true;
	}

	/* Kazandiysak buraya giriyoruz*/
	if (isWinner(state.agentHand))
	{
		cout << "!" << endl;
		printHand(state.agentHand);
		cout << "Kaybettin:(" << endl;
		return true;
	}

	/* Kimse kazanmadiysa false dönüyoruz */
	return false;
}


void playUserTurn(State &state)
{
	if (state.turnCard < 52)
		cout << "Kartini acmak icin \"t\" tusuna bas." << endl;
	cout << "Kartini gormek icin  \"d\" tusuna bas ." << endl;
	char choice;
	cin >> choice;
	while (choice != 'd' && (choice != 't' || state.turnCard == 52))
	{
		if (state.turnCard < 52)
			cout << "Kartini acmak icin \"t\" tusuna bas." << endl;
		cout << "Kartini gormek icin  \"d\" tusuna bas." << endl;
		cin >> choice;
	}

	if (choice == 't')
		state.userHand.push_back(state.turnCard);

	else
	{
		state.userHand.push_back(state.deck.back());
		state.deck.pop_back();
	}
	printHand(state.userHand);

	cout << "Karti geri vermek icin \"g\" veya elinizi yeniden duzenlemek icin \"r\" basiniz.";
	cout << endl;
	cin >> choice;
	while (choice != 'g' && choice != 'r')
	{
		cout << "Karti geri vermek icin \"g\" veya elinizi yeniden duzenlemek icin \"r\" basiniz.";
		cout << endl;
		cin >> choice;
	}
	while (choice != 'g')
	{

		if (choice == 'r')
		{
			char pos1, pos2;
			cout << "Degistirilecek ilk kartin konumunu girin [1-8]." << endl;
			cin >> pos1;
			while (pos1 < '1' || pos1 > '8')
			{
				cout << "Degistirilecek ilk kartin konumunu girin [1-8]." << endl;
				cin >> pos1;
			}
			cout << "Degistirilecek ikinci kartin konumunu girin [1-8]." << endl;
			cin >> pos2;
			while (pos2 < '1' || pos2 > '8')
			{
				cout << "Degistirilecek ikinci kartin konumunu girin [1-8]." << endl;
				cin >> pos2;
			}

			swap(state.userHand, pos1-49, pos2-49);
			printHand(state.userHand);
		}

		cout << "Karti geri vermek icin \"g\" veya elinizi yeniden duzenlemek icin \"r\" basiniz.";
		cout << endl;
		cin >> choice;
		while (choice != 'g' && choice != 'r')
		{
			cout << "Karti geri vermek icin \"g\" veya elinizi yeniden duzenlemek icin \"r\" basiniz.";
			cout << endl;
			cin >> choice;
		}
	}
	if (choice == 'g')
	{
		cout << "Geri vermek istediginiz kartin pozisyonunu girin [1-8].";
		cout << endl;
		char pos;
		cin >> pos;
		while (pos < '1' || pos > '8')
		{
			cout << "Geri vermek istediginiz kartin pozisyonunu girin [1-8].";
			cout << endl;
			cin >> pos;
		}
		state.turnCard = state.userHand[pos-49];					// Dönen karti ayarliyoruz
		state.remaining.remove(state.turnCard);						// Kalan kartlari düzenliyoruz
		state.userHand.erase(state.userHand.begin()+pos-49);		// Kullanicinin elindeki kartlari düzenliyoruz
	}
}

int evaluate(State state)
{
	mergeSort(state.agentHand, 0, state.agentHand.size());
	vector<int> hand = state.agentHand;
	list<int> remaining = state.remaining;
	int score = 0;					// Elin skorunu yazdiriyoruz
	int rank;								// Kartin puanini yazdiriyoruz
	int val;								// Kartin degerini yazdiriyoruz
	if (isWinner(hand))
		return 100;


	for (int i = 0; i < hand.size() - 3; i++)
	{
		val = hand[i];
		rank = val % 13;

		int matchCount = 0;
		for (int j = i + 1; j < hand.size(); j++)
		{
			if (rank == hand[j] % 13)
				matchCount++;
		}
		if (matchCount == 3)
		{
			score += 15;
			matchCount = 0;
		}

if (val < 10 && val+1 == hand[i+1] && val+2 == hand[i+2]
				&& val+3 == hand[i+3])
			score += 15;
	}
for (int i = 0; i < hand.size() - 2; i++)
	{
		val = hand[i];
		rank = val % 13;
		int matchCount = 0;
		for (int j = i + 1; j < hand.size(); j++)
		{
			if (rank == hand[j] % 13)
				matchCount++;
		}
		if (matchCount == 2)
		{
			score += 9;

			for (list<int>::iterator it = remaining.begin();
						it != remaining.end(); it++)
				if (*it % 13 == rank)
					score ++;
			matchCount = 0;
		}


		if (rank < 11 && val+1 == hand[i+1] && val+2 == hand[i+2])
		{
			score += 9;

			for (list<int>::iterator it = remaining.begin();
						it != remaining.end(); it++)
			{
				if (rank > 0 && *it == val - 1)
					score++;
				if (rank < 10 && *it == val + 3)
					score++;
			}
		}
	}


	for (int i = 0; i < hand.size() - 1; i++)
	{
		val = hand[i];
		rank = val % 13;


		int matchCount = 0;
		for (int j = i + 1; j < hand.size(); j++)
		{
			if (rank == hand[j] % 13)
				matchCount++;
		}
		if (matchCount == 1)
		{
			/* Kalan sayisini kontrol ediyoruz */
			for (list<int>::iterator it = remaining.begin();
						it != remaining.end(); it++)
				if (*it % 13 == rank)
					score++;
			matchCount = 0;
		}
		if (rank < 12 && val+1 == hand[i+1])
		{

			for (list<int>::iterator it = remaining.begin();
						it != remaining.end(); it++)
			{
				if (rank > 0 && *it == val - 1)
				{
					score++;
					for (list<int>::iterator jt = remaining.begin();
						jt != remaining.end(); jt++)
						if (rank > 1 && *jt == val - 2)
							score++;
				}
				if (rank < 11 && *it == val + 2)
				{
					score++;
					for (list<int>::iterator jt = remaining.begin();
						jt != remaining.end(); jt++)
						if (rank < 10 && *jt == val + 3)
							score++;
				}
			}
		}
	}

	return score;
}
bool takeTurnCard(State state)
{
	State originalState = state;
	vector<int> testHand = state.agentHand;
	testHand.push_back(state.turnCard);


	while (state.agentHand.empty() == false)
		state.agentHand.pop_back();

	for (int i = 0; i < testHand.size(); i++)
	{
		for (int j = 0; j < testHand.size(); j++)
		{
			if (i != j)
				state.agentHand.push_back(testHand[j]);
		}

		if (isWinner(state.agentHand))
			return true;

		if (evaluate(state) > evaluate(originalState))
			return true;

		while (state.agentHand.empty() == false)
			state.agentHand.pop_back();
	}
	return false;
}


int removeWorstCard(State &state)
{
	State testState = state;


	while (testState.agentHand.empty() == false)
		testState.agentHand.pop_back();

	int maxEval = 0;
	int maxEvalIndex = 0;
	int eval = 0;

	for (int i = 0; i < state.agentHand.size(); i++)
	{
		for (int j = 0; j < state.agentHand.size(); j++)
		{
			if (i != j)
				testState.agentHand.push_back(state.agentHand[j]);
		}

		eval = evaluate(testState);
		if (eval > maxEval)
		{
			maxEval = eval;
			maxEvalIndex = i;
		}


		while (testState.agentHand.empty() == false)
			testState.agentHand.pop_back();
	}

	int returnVal = state.agentHand[maxEvalIndex];

	/* En kötü kartý kaldýrýyoruz */
	state.agentHand.erase(state.agentHand.begin() + maxEvalIndex);

	return returnVal;
}

/*
 * Bilgisayarin islemlerini ayarliyoruz
 */
void playAgentTurn(State &state)
{

	if (takeTurnCard(state))
	{
		cout << "Bilgisayar donen karti aldi!" << endl;
		int turnCard = state.turnCard;
		state.agentHand.push_back(turnCard);
		state.turnCard = removeWorstCard(state);
	}
	else
	{
		cout << "Bilgisayar elini cizdirdi." << endl;
		state.agentHand.push_back(state.deck.back());
		state.remaining.remove(state.deck.back());
		state.deck.pop_back();
		state.turnCard = removeWorstCard(state);
	}
}
