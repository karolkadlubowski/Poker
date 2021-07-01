#pragma once
#include <string>
//#include "HandsDistinguisher.h"

using namespace std;

class Card {

	string value;
	string suitSymbol;
	int numberValue;
public:
	Card() {}
	Card(const Card& copyCard);
	Card(string,string,int);

	bool operator==(const Card& card2);

	friend class Player;
	friend class Deal;
	friend class HandsDistinguisher;
	
};