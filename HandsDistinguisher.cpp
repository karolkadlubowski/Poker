#include "HandsDistinguisher.h"
#include <vector>
#include <algorithm>


using namespace std;

int HandsDistinguisher::recognizeFigure(vector<Card>& cards, vector<Card>& highestFiveCards)
{
	if (recognizeStraightFlush(cards, highestFiveCards))
	{
		cout << "Poker" << endl;
		return 9;
	}
	else if (recognizeFourOfAKind(cards, highestFiveCards))
	{
		cout << "Kareta" << endl;
		return 8;
	}
	else if (recognizeFullHouse(cards, highestFiveCards))
	{
		cout << "Full" << endl;
		return 7;
	}
	else if (recognizeFlush(cards, highestFiveCards))
	{
		cout << "Kolor" << endl;
		return 6;
	}
	else if (recognizeStraight(cards, highestFiveCards))
	{
		cout << "Strit" << endl;
		return 5;
	}
	else if (recognizeThreeOfAKind(cards, highestFiveCards))
	{
		cout << "Trojka" << endl;
		return 4;
	}
	else if (recognizeTwoPairs(cards, highestFiveCards))
	{
		cout << "Dwie pary" << endl;
		return 3;
	}
	else if (recognizePair(cards, highestFiveCards))
	{
		cout << "Para" << endl;
		return 2;
	}
	else if (recognizeHighCard(cards, highestFiveCards))
	{
		cout << "Wysoka karta" << endl;
		return 1;
	}
	else
		throw exception();
	return 0;
}


vector<Card> HandsDistinguisher::recognizeCardsInOneColor(vector<Card> Cards)
{
	int licznik = 0;
	string suitSymbols[4] = { "Spade" , "Heart", "Diamond", "Club" };
	vector<Card> outcome;

	for (auto symbol : suitSymbols)
	{
		for (auto c = Cards.begin(); c != Cards.end(); c++)
		{
			auto nextCard = next(c, 1);
			if (c->suitSymbol == symbol)
			{
				licznik++;
				outcome.push_back(*c);
			}

		}
		if (licznik > 4)
			break;
		licznik = 0;
	}
	if (licznik < 5)
		outcome.clear();
	return outcome;
}

vector<Card> HandsDistinguisher::recognizeStraightForStraightFlush(vector<Card> Cards)
{
	int licznik = 0;
	vector<Card> outcome;

	for (auto c = Cards.begin(); c != --Cards.end(); c++)
	{
		auto nextCard = next(c, 1);
		if (c->numberValue != nextCard->numberValue)
		{
			if ((c->numberValue)-1 == (nextCard->numberValue))
			{
				licznik++;
				outcome.push_back(*c);
			}
			else {
				licznik = 0;
				outcome.clear();
			}
			if (licznik == 4)
			{
				outcome.push_back(*nextCard);
				break;
			}
		}
		else
		{
			outcome.push_back(*c);
		}
	}
	if (licznik != 4)
		outcome.clear();
	return outcome;
}


bool HandsDistinguisher::recognizeStraightFlush(vector<Card> Cards, vector<Card>& highestFiveCards)
{
	vector<Card> flush = recognizeCardsInOneColor(Cards);
	vector<Card> straight = recognizeStraightForStraightFlush(Cards);

	if (flush.empty() || straight.empty())
		return false;
	else
	{
		vector<Card>::iterator f = flush.begin();


		while (f != flush.end())
		{
			auto s = straight.begin();
			while (s != straight.end())
			{
				if (*f == *s)
				{
					highestFiveCards.push_back(*f);
					break;
				}
				else
				{
					s++;
				}

			}
			f++;
		}
	}

	if (highestFiveCards.size() != 5)
	{
		highestFiveCards.clear();
		return false;
	}
	return true;

}

bool HandsDistinguisher::recognizeFourOfAKind(vector<Card> Cards, vector<Card>& highestFiveCards)
{

	int licznik = 0;
	for (auto c = Cards.begin(); c != --Cards.end(); c++)
	{
		auto nextCard = next(c, 1);
		if (c->numberValue == (nextCard->numberValue))
		{
			licznik++;
			highestFiveCards.push_back(*c);
			if (licznik == 3)
			{
				//player.highestFiveCards.push_back(*c);
				highestFiveCards.push_back(*nextCard);
				for (int i = 0; i < Cards.size(); i++)
				{
					if (highestFiveCards[0].numberValue != Cards[i].numberValue)
					{
						highestFiveCards.push_back(Cards[i]);
						return true;
					}
				}

			}

		}
		else
		{
			licznik = 0;
			highestFiveCards.clear();
		}

	}
	highestFiveCards.clear();
	return false;
}

bool HandsDistinguisher::recognizeFullHouse(vector<Card> Cards, vector<Card>& highestFiveCards)
{

	bool ifThree = false;
	Card threeCard;
	bool ifPair = false;


	for (auto c = ++Cards.begin(); c < --Cards.end(); c++)
	{
		auto nextCard = next(c, 1);
		auto prevCard = prev(c, 1);
		if ((c->numberValue) == (nextCard->numberValue) && nextCard->numberValue == prevCard->numberValue)
		{
			highestFiveCards.push_back(*c);
			highestFiveCards.push_back(*nextCard);
			highestFiveCards.push_back(*prevCard);
			ifThree = true;
			threeCard = *c;
			break;

		}
	}

	for (auto c = Cards.begin(); c < --Cards.end(); c++)
	{
		auto nextCard = next(c, 1);

		if ((c->numberValue) == (nextCard->numberValue) && c->numberValue != threeCard.numberValue)
		{
			ifPair = true;
			highestFiveCards.push_back(*c);
			highestFiveCards.push_back(*nextCard);

			break;
		}
	}
	if (!(ifThree && ifPair))
	{
		highestFiveCards.clear();
		return false;
	}

	return true;
}

bool HandsDistinguisher::recognizeFlush(vector<Card> Cards, vector<Card>& highestFiveCards)
{
	int licznik = 0;
	string suitSymbols[4] = { "Spade" , "Heart", "Diamond", "Club" };


	for (auto symbol : suitSymbols)
	{
		for (auto c = Cards.begin(); c != Cards.end(); c++)
		{
			auto nextCard = next(c, 1);
			if (c->suitSymbol == symbol)
			{
				licznik++;
				highestFiveCards.push_back(*c);
			}
			if (licznik == 5)
				return true;

		}
		highestFiveCards.clear();
		licznik = 0;

	}

	return false;

}

bool HandsDistinguisher::recognizeStraight(vector<Card> Cards, vector<Card>& highestFiveCards)
{
	int licznik = 0;
	while (true) {
		auto deleteCopiesIterator = ++Cards.begin();
		while (deleteCopiesIterator != Cards.end())
		{
			if (deleteCopiesIterator->numberValue == prev(deleteCopiesIterator, 1)->numberValue)
			{
				Cards.erase(deleteCopiesIterator);
				break;
			}
			else
				deleteCopiesIterator++;
		}
		break;
	}


	for (auto c = Cards.begin(); c != --Cards.end(); c++)
	{
		auto nextCard = next(c, 1);
		if (c->numberValue != nextCard->numberValue)
		{
			if ((c->numberValue)-1 == (nextCard->numberValue))
			{
				licznik++;
				highestFiveCards.push_back(*c);
			}
			else {
				licznik = 0;
				highestFiveCards.clear();
			}
			if (licznik == 4)
			{
				highestFiveCards.push_back(*nextCard);
				break;
			}
		}
		else
		{
			highestFiveCards.push_back(*c);
		}
	}
	if (licznik != 4)
	{
		highestFiveCards.clear();
		return false;
	}

	return true;
}

bool HandsDistinguisher::recognizeThreeOfAKind(vector<Card> Cards, vector<Card>& highestFiveCards)
{
	int licznik = 0;


	for (auto c = Cards.begin(); c != --Cards.end(); c++)
	{
		auto nextCard = next(c, 1);
		if ((c->numberValue) == (nextCard->numberValue))
		{
			licznik++;
			if (licznik == 2)
			{
				highestFiveCards.push_back(*nextCard);
				for (int i = 0; i < Cards.size(); i++)
				{
					if (highestFiveCards[0].numberValue != Cards[i].numberValue)
						highestFiveCards.push_back(Cards[i]);

					if (highestFiveCards.size() == 5)
						break;

				}
				return true;
			}
			highestFiveCards.push_back(*c);
			highestFiveCards.push_back(*nextCard);
		}
		else {
			licznik = 0;
			highestFiveCards.clear();
		}

	}
	highestFiveCards.clear();
	return false;
}

bool HandsDistinguisher::recognizeTwoPairs(vector<Card> Cards, vector<Card>& highestFiveCards)
{
	int licznik = 0;


	for (auto c = Cards.begin(); c != --Cards.end(); c++)
	{
		auto nextCard = next(c, 1);
		if ((c->numberValue) == (nextCard->numberValue))
		{
			highestFiveCards.push_back(*c);
			highestFiveCards.push_back(*nextCard);
			licznik++;
		}

		if (licznik == 2)
		{
			for (int i = 0; i < Cards.size(); i++)
			{
				if (highestFiveCards[0].numberValue != Cards[i].numberValue && highestFiveCards[2].numberValue != Cards[i].numberValue)
				{
					highestFiveCards.push_back(Cards[i]);
					return true;
				}
			}

		}
	}
	highestFiveCards.clear();
	return false;
}

bool HandsDistinguisher::recognizePair(vector<Card> Cards, vector<Card>& highestFiveCards)
{


	for (auto c = Cards.begin(); c != --Cards.end(); c++)
	{
		auto nextCard = next(c, 1);
		if ((c->numberValue) == (nextCard->numberValue))
		{
			highestFiveCards.push_back(*c);
			highestFiveCards.push_back(*nextCard);
			for (int i = 0; i < Cards.size(); i++)
			{
				if (highestFiveCards[0].numberValue != Cards[i].numberValue)
					highestFiveCards.push_back(Cards[i]);
				if (highestFiveCards.size() == 5)
					return true;
			}

		}
	}
	//player.highestFiveCards.clear();
	return false;
}

bool HandsDistinguisher::recognizeHighCard(vector<Card> Cards, vector<Card>& highestFiveCards)
{

	for (int i = 0; i < 5; i++)
		highestFiveCards.push_back(Cards[i]);

	return true;
}


void HandsDistinguisher::concludeResults(Deal &deal)
{
	vector<int> playerResults;
	
	cout << "Karty na stole:" << endl;
	for (Card card : deal.tableCards)
		cout << card.value << " " << card.suitSymbol << endl;
	int highestScore = 0;
	for (auto player = deal.players.begin(); player != deal.players.end(); player++)
	{
		cout << endl << "Karty gracza " << player->name << endl;
		vector<Card> cards = deal.tableCards;
		cards.push_back(player->hand[0]);
		cout << player->hand[0].value << " " << player->hand[0].suitSymbol << endl;
		cards.push_back(player->hand[1]);
		cout << player->hand[1].value << " " << player->hand[1].suitSymbol << endl;
		sort(cards.begin(), cards.end(), [](Card const& A, Card const& B) -> bool {return A.numberValue > B.numberValue; });


		int score = recognizeFigure(cards, player->highestFiveCards);
		playerResults.push_back(score);
		if (score > highestScore)
		{
			highestScore = score;
			deal.WinnersOfTheDeal.clear();
			deal.WinnersOfTheDeal.push_back(*player);

		}
		else if (highestScore == score)
			deal.WinnersOfTheDeal.push_back(*player);
		
	}

	whoseFigureIsHigher(highestScore, deal.WinnersOfTheDeal);

	cout << endl << "Zwyciezcy:" << endl;
	for (Player player : deal.WinnersOfTheDeal)
	{
		cout << player.name << endl;
	}



}



void HandsDistinguisher::whoseFigureIsHigher(int figure, list<Player>& highestCardsPlayers)
{
	if (highestCardsPlayers.size() == 1)
		return;
	else
	{
		highestCardsPlayers = recognizeHigherHighCard(highestCardsPlayers);
		
		switch (figure)
		{
		case 9:
			highestCardsPlayers = recognizeHigherFlushStraight(highestCardsPlayers);
			break;
		case 8:
			highestCardsPlayers = recognizeHigherFourOfAKind(highestCardsPlayers);
			break;
		case 7:
			highestCardsPlayers = recognizeHigherFullHouse(highestCardsPlayers);
			break;
		case 6:
			highestCardsPlayers = recognizeHigherFlush(highestCardsPlayers);
			break;
		case 5:
			highestCardsPlayers = recognizeHigherStraight(highestCardsPlayers);
			break;
		case 4:
			highestCardsPlayers = recognizeHigherThreeOfAKind(highestCardsPlayers);
			break;
		case 3:
			highestCardsPlayers = recognizeHigherTwoPairs(highestCardsPlayers);
			break;
		case 2:
			highestCardsPlayers = recognizeHigherPair(highestCardsPlayers);
			break;
		case 1:
			highestCardsPlayers = recognizeHigherHighCard(highestCardsPlayers);
			break;
		default:
			throw exception();
		}
		
	}
}

list<Player> HandsDistinguisher::recognizeHigherFlushStraight(list<Player> highestCardsPlayers)
{
	int highestCard = 0;
	list<Player> finalWinners;
	for (auto i = highestCardsPlayers.begin(); i != highestCardsPlayers.end(); i++)
	{
		int firstCard = i->highestFiveCards[0].numberValue;

		if (firstCard > highestCard)
		{
			highestCard = firstCard;
			finalWinners.clear();
			finalWinners.push_back(*i);

		}
		else if (firstCard == highestCard)
			highestCardsPlayers.push_back(*i);
	}
	return finalWinners;
}

list<Player> HandsDistinguisher::recognizeHigherFourOfAKind(list<Player> highestCardsPlayers)
{
	int highestCard = 0;
	list<Player> highestFour;
	for (auto i = highestCardsPlayers.begin(); i != highestCardsPlayers.end(); i++)
	{
		int firstCard = i->highestFiveCards[0].numberValue;

		if (firstCard > highestCard)
		{
			highestCard = firstCard;
			highestFour.clear();
			highestFour.push_back(*i);

		}
		else if (firstCard == highestCard)
			highestFour.push_back(*i);
	}
	if (highestFour.size() == 1)
		return highestFour;
	else
	{
		highestCard = 0;
		list<Player> finalWinners;
		for (auto i = highestFour.begin(); i != highestFour.end(); i++)
		{
			int lastCard = i->highestFiveCards[0].numberValue;

			if (lastCard > highestCard)
			{
				highestCard = lastCard;
				finalWinners.clear();
				finalWinners.push_back(*i);

			}
			else if (lastCard == highestCard)
				highestCardsPlayers.push_back(*i);
		}
		return finalWinners;
	}
}

list<Player> HandsDistinguisher::recognizeHigherFullHouse(list<Player> highestCardsPlayers)
{
	int highestCard = 0;
	list<Player> highestThree;
	for (auto i = highestCardsPlayers.begin(); i != highestCardsPlayers.end(); i++)
	{
		int firstCard = i->highestFiveCards[0].numberValue;

		if (firstCard > highestCard)
		{
			highestCard = firstCard;
			highestThree.clear();
			highestThree.push_back(*i);

		}
		else if (firstCard == highestCard)
			highestThree.push_back(*i);
	}
	if (highestThree.size() == 1)
		return highestThree;
	else
	{
		highestCard = 0;
		list<Player> finalWinners;
		for (auto i = highestThree.begin(); i != highestThree.end(); i++)
		{
			int lastCard = i->highestFiveCards[4].numberValue;

			if (lastCard > highestCard)
			{
				highestCard = lastCard;
				finalWinners.clear();
				finalWinners.push_back(*i);

			}
			else if (lastCard == highestCard)
				finalWinners.push_back(*i);
		}
		return finalWinners;
	}
}

list<Player> HandsDistinguisher::recognizeHigherFlush(list<Player> highestCardsPlayers)
{
	int highestCard = 0;
	list<Player> finalWinners;
	int cardIndex = 0;
	while (true) {
		for (auto i = highestCardsPlayers.begin(); i != highestCardsPlayers.end(); i++)
		{
			int firstCard = i->highestFiveCards[cardIndex].numberValue;

			if (firstCard > highestCard)
			{
				highestCard = firstCard;
				finalWinners.clear();
				finalWinners.push_back(*i);

			}
			else if (firstCard == highestCard)
				highestCardsPlayers.push_back(*i);
		}
		if(finalWinners.size()==1)
			return finalWinners;
		highestCardsPlayers = finalWinners;
		if (cardIndex < 4)
			cardIndex++;
		else
			return finalWinners;
	}
}

list<Player> HandsDistinguisher::recognizeHigherStraight(list<Player> highestCardsPlayers)
{
	int highestCard = 0;
	list<Player> finalWinners;
	for (auto i = highestCardsPlayers.begin(); i != highestCardsPlayers.end(); i++)
	{
		int firstCard = i->highestFiveCards[0].numberValue;

		if (firstCard > highestCard)
		{
			highestCard = firstCard;
			finalWinners.clear();
			finalWinners.push_back(*i);

		}
		else if (firstCard == highestCard)
			finalWinners.push_back(*i);
	}
	return finalWinners;
}

list<Player> HandsDistinguisher::recognizeHigherThreeOfAKind(list<Player> highestCardsPlayers)
{
	int highestCard = 0;
	list<Player> highestThree;
	for (auto i = highestCardsPlayers.begin(); i != highestCardsPlayers.end(); i++)
	{
		int firstCard = i->highestFiveCards[0].numberValue;

		if (firstCard > highestCard)
		{
			highestCard = firstCard;
			highestThree.clear();
			highestThree.push_back(*i);

		}
		else if (firstCard == highestCard)
			highestThree.push_back(*i);
	}
	if (highestThree.size() == 1)
		return highestThree;
	else
	{
		highestCard = 0;
		int cardIndex = 3;
		list<Player> finalWinners;
		while (true) {
			for (auto i = highestCardsPlayers.begin(); i != highestCardsPlayers.end(); i++)
			{
				int firstCard = i->highestFiveCards[cardIndex].numberValue;

				if (firstCard > highestCard)
				{
					highestCard = firstCard;
					finalWinners.clear();
					finalWinners.push_back(*i);

				}
				else if (firstCard == highestCard)
					finalWinners.push_back(*i);
			}
			if (finalWinners.size() == 1)
				return finalWinners;
			highestCardsPlayers = finalWinners;
			if (cardIndex < 4)
				cardIndex++;
			else
				return finalWinners;
		}
	}
}

list<Player> HandsDistinguisher::recognizeHigherTwoPairs(list<Player> highestCardsPlayers)
{
	int highestCard = 0;
	list<Player> highestFirstPair;
	for (auto i = highestCardsPlayers.begin(); i != highestCardsPlayers.end(); i++)
	{
		int firstCard = i->highestFiveCards[0].numberValue;

		if (firstCard > highestCard)
		{
			highestCard = firstCard;
			highestFirstPair.clear();
			highestFirstPair.push_back(*i);

		}
		else if (firstCard == highestCard)
			highestFirstPair.push_back(*i);
	}
	if (highestFirstPair.size() == 1)
		return highestFirstPair;
	else
	{
		highestCard = 0;
		list<Player> highestSecondPair;
		for (auto i = highestFirstPair.begin(); i != highestFirstPair.end(); i++)
		{
			int secondCard = i->highestFiveCards[2].numberValue;

			if (secondCard > highestCard)
			{
				highestCard = secondCard;
				highestSecondPair.clear();
				highestSecondPair.push_back(*i);

			}
			else if (secondCard == highestCard)
				highestSecondPair.push_back(*i);
		}
		if (highestSecondPair.size() == 1)
			return highestSecondPair;
		else
		{
			highestCard = 0;
			list<Player> lastCard;
			for (auto i = highestSecondPair.begin(); i != highestSecondPair.end(); i++)
			{
				int fifthCard = i->highestFiveCards[4].numberValue;

				if (fifthCard > highestCard)
				{
					highestCard = fifthCard;
					lastCard.clear();
					lastCard.push_back(*i);

				}
				else if (fifthCard == highestCard)
					lastCard.push_back(*i);
			}
			return lastCard;
		}
	}
}


list<Player> HandsDistinguisher::recognizeHigherPair(list<Player> highestCardsPlayers)
{
	int highestCard = 0;
	list<Player> highestPair;
	for (auto i = highestCardsPlayers.begin(); i != highestCardsPlayers.end(); i++)
	{
		int firstCard = i->highestFiveCards[0].numberValue;

		if (firstCard > highestCard)
		{
			highestCard = firstCard;
			highestPair.clear();
			highestPair.push_back(*i);

		}
		else if (firstCard == highestCard)
			highestPair.push_back(*i);
	}
	if (highestPair.size() == 1)
		return highestPair;
	else
	{
		list<Player> finalWinners;
		int cardIndex = 2;
		
		while (true) {
			highestCard = highestPair.begin()->highestFiveCards[cardIndex].numberValue;
			for (auto i = highestPair.begin(); i != highestPair.end(); i++)
			{
				int firstCard = i->highestFiveCards[cardIndex].numberValue;

				if (firstCard > highestCard)
				{
					highestCard = firstCard;
					finalWinners.clear();
					finalWinners.push_back(*i);

				}
				else if (firstCard == highestCard)
					finalWinners.push_back(*i);
			}
			if (finalWinners.size() == 1)
				return finalWinners;
			highestPair = finalWinners;
			finalWinners.clear();
			if (cardIndex < 4)
				cardIndex++;
			else
				return highestPair;
		}
	}
}

list<Player> HandsDistinguisher::recognizeHigherHighCard(list<Player> highestCardsPlayers)
{
	int highestCard = 0;
	list<Player> finalWinners;
	int cardIndex = 0;
	while (true) {
		highestCard = 0;
		for (auto i = highestCardsPlayers.begin(); i != highestCardsPlayers.end(); i++)
		{
			int firstCard = i->highestFiveCards[cardIndex].numberValue;
			
			if (firstCard > highestCard)
			{
				highestCard = firstCard;
				finalWinners.clear();
				finalWinners.push_back(*i);

			}
			else if (firstCard == highestCard)
				finalWinners.push_back(*i);
		}
		if (finalWinners.size() == 1)
			return finalWinners;
		highestCardsPlayers = finalWinners;
		if (cardIndex < 4)
			cardIndex++;
		else
			return finalWinners;
	}
}









