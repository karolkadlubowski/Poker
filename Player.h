#pragma once

#include <iostream>
#include <string>
#include <list>
#include "Card.h"
#include<vector>
#include "HandsDistinguisher.h"


using namespace std;

class Player 
{
	string name;
	int account=10000;
	vector<Card> hand;
	int dealStake=0;
	bool ifAllIn=false;
	vector<Card> highestFiveCards;

	int makeBet(int currentHighestBet,int &pot, bool ifFlague,vector<Card> cardsOnTable);
	int makeBetAfterCardsOnTable(int currentHighestBet, int& pot, bool ifFlague, vector<Card> cardsOnTable, bool ifFirstRound);

public:
	Player(string name);
	Player() {}

	~Player();

	Player(const Player& copyPlayer);


	friend class Game;
	friend class Deal;
	friend class HandsDistinguisher;
};