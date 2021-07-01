#pragma once
#include <iostream>
#include <vector>
#include "Deck.h"
#include <list>
#include "Player.h"
#include "Game.h"
#include "HandsDistinguisher.h"

using namespace std;

class Deal{
private:
	list<Player> players;
	list<Player> resignedPlayers;
	vector<Card> shuffledDeck;
	vector<Card> errorDeck;
	vector<Card> tableCards;

	int boardStake=0;
	int currentHighest=0;
	int pot=0;

	list<Player>::iterator bigBlind;

	list<Player> WinnersOfTheDeal;

	void hand2CardsAround();

	/*void makeRoundAroundTable();
	void makeRoundAroundTableAfterCardsOnTable();*/

	void firstBet();
	void firstBetEveryNextRound(list<Player>::iterator current);
	void everyNextBet(list<Player>::iterator currentPlayer);

	bool isThereAWinner();

	void showThreeCards();

	void showOneCard();

	int playersChoice(Player& player);


	void dividePot();

	bool printDeckToFile();

public:
	Deal(Deck deck, list<Player> players);

	Deal() {}

	Deal(const Deal& copyDeal);

	friend class Game;
	friend class HandsDistinguisher;
};