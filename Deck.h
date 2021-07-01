#pragma once
#include "Card.h"
#include <vector>

using namespace std;

class Deck {
private:
	string values[13] = {"2","3","4","5","6","7","8","9","10","Jack","Queen","King","Ace"};
	string suitSymbols[4] = { "Spade" , "Heart", "Diamond", "Club"};
	int numberValues[13] = { 2,3,4,5,6,7,8,9,10,11,12,13,14 };

	vector<Card> ShuffleDeck();
	
public:
	
	
	friend class Deal;
	
};