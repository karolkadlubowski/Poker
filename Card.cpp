#include "Card.h"

using namespace std;

Card::Card(string value, string suitSymbol,int numberValue)
{
	this->value = value;
	this->suitSymbol = suitSymbol;
	this->numberValue = numberValue;
}

bool Card::operator==(const Card& card2)
{
	if (
		this->numberValue == card2.numberValue &&
		this->suitSymbol == card2.suitSymbol &&
		this->value == card2.value
		)
		return true;
	return false;
}

Card::Card(const Card& copyCard)
{
	this->suitSymbol = copyCard.suitSymbol;
	this->value = copyCard.value;
	this->numberValue = copyCard.numberValue;
}