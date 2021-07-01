#include "Deck.h"

#include <vector>
#include <time.h>

using namespace std;




vector<Card> Deck::ShuffleDeck() 
{
	vector<Card> sortedDeck;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 13; j++)
			sortedDeck.push_back(Card(values[j], suitSymbols[i],numberValues[j]));

	vector<Card> shuffledDeck;

	int n = 52;
	int randomIndex;
	srand(time(NULL));

	while (!sortedDeck.empty())
	{
		
		randomIndex = rand() % n + 0;
		shuffledDeck.push_back(sortedDeck[randomIndex]);
		sortedDeck.erase(sortedDeck.begin()+randomIndex);
		n--;
	}

	return shuffledDeck;
	
}

