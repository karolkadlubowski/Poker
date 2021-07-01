#pragma once

#include <list>
#include <vector>

#include "Deal.h"

using namespace std;

class Game
{
private:

	list<Player> players;
	Deck deck;

	void updateAccounts(list<Player> playersOfTheDeal);
	
	

public:
	Game();

	

	void ProceedToTheGame();

	friend class Deal;
};

