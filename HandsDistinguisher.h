#pragma once
#include "Deal.h"


using namespace std;
class HandsDistinguisher
{
	
	//Deal* deal;


	void concludeResults(Deal &deal);
	

	int recognizeFigure(vector<Card>& cards,vector<Card> &highestFiveCards);

	vector<Card> recognizeCardsInOneColor(vector<Card> Cards);
	vector<Card> recognizeStraightForStraightFlush(vector<Card> Cards);

	bool recognizeStraightFlush(vector<Card> Cards, vector<Card>& highestFiveCards);
	bool recognizeFourOfAKind(vector<Card> Cards, vector<Card>& highestFiveCards);
	bool recognizeFullHouse(vector<Card> Cards, vector<Card>& highestFiveCards);
	bool recognizeFlush(vector<Card> Cards, vector<Card>& highestFiveCards);
	bool recognizeStraight(vector<Card> Cards, vector<Card>& highestFiveCards);
	bool recognizeThreeOfAKind(vector<Card> Cards, vector<Card>& highestFiveCards);
	bool recognizeTwoPairs(vector<Card> Cards, vector<Card>& highestFiveCards);
	bool recognizePair(vector<Card> Cards, vector<Card>& highestFiveCards);
	bool recognizeHighCard(vector<Card> Cards, vector<Card>& highestFiveCards);


	void whoseFigureIsHigher(int figure, list<Player>& highestCardsPlayers);

	list<Player> recognizeHigherFlushStraight(list<Player> highestCardsPlayers);
	list<Player> recognizeHigherFourOfAKind(list<Player> highestCardsPlayers);
	list<Player> recognizeHigherFullHouse(list<Player> highestCardsPlayers);
	list<Player> recognizeHigherFlush(list<Player> highestCardsPlayers);
	list<Player> recognizeHigherStraight(list<Player> highestCardsPlayers);
	list<Player> recognizeHigherThreeOfAKind(list<Player> highestCardsPlayers);
	list<Player> recognizeHigherTwoPairs(list<Player> highestCardsPlayers);
	list<Player> recognizeHigherPair(list<Player> highestCardsPlayers);
	list<Player> recognizeHigherHighCard(list<Player> highestCardsPlayers);

	
	

public:
	//HandsDistinguisher(Deal deal);
	HandsDistinguisher() 
	{
	}
	

	friend class Game;
};

