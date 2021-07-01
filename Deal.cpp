#include <iostream>
#include <fstream>


#include "Deal.h"
#include "Functions.h"

using namespace std;



Deal::Deal(Deck deck, list<Player> players)
{

	this->shuffledDeck = deck.ShuffleDeck();
	

	this->errorDeck = this->shuffledDeck;
	this->players = players;

}

Deal::Deal(const Deal& copyDeal)
{
	this->bigBlind = copyDeal.bigBlind;
	this->boardStake = copyDeal.boardStake;
	this->players = copyDeal.players;
	this->pot = copyDeal.pot;
	this->shuffledDeck = copyDeal.shuffledDeck;
	this->tableCards = copyDeal.tableCards;
	this->errorDeck = copyDeal.errorDeck;
	this->WinnersOfTheDeal = copyDeal.WinnersOfTheDeal;
	this->resignedPlayers = copyDeal.resignedPlayers;
}

void Deal::hand2CardsAround()
{

	for (list<Player>::iterator iter = players.begin(); iter != players.end(); iter++)
	{
		iter->hand.push_back(shuffledDeck.back());
		shuffledDeck.pop_back();
		iter->hand.push_back(shuffledDeck.back());
		shuffledDeck.pop_back();
	}
}


bool Deal::isThereAWinner()
{
	if (players.size() == 1)
		return true;
	else
		return false;
}

void Deal::showThreeCards()
{
	for (int i = 1; i <= 3; i++)
	{
		tableCards.push_back(shuffledDeck.back());
		shuffledDeck.pop_back();
	}
}

void Deal::showOneCard()
{
	tableCards.push_back(shuffledDeck.back());
	shuffledDeck.pop_back();

}

int Deal::playersChoice(Player& player)
{
	int answer;


	while (true)
	{
		cout << endl << endl;
		cout << "Nazwa gracza: " << player.name << endl;
		cout << "Konto: " << player.account << endl;
		cout << "Twoja obecna stawka: " << player.dealStake << endl;
		cout << "Najwyzsza stawka: " << currentHighest << endl;
		cout << "Pula: " << pot << endl;
		if (!tableCards.empty())
		{
			cout << "Karty na stole:" << endl;
			for (auto card : tableCards)
				cout << card.value << " " << card.suitSymbol << endl;
		}
		cout << "Karty na rece:" << endl;
		cout << player.hand[0].value << " " << player.hand[0].suitSymbol << endl;
		cout << player.hand[1].value << " " << player.hand[1].suitSymbol << endl;


		cout << "Co chcesz zrobic?" << endl;
		cout << "1. Pas" << endl;
		cout << "2. Sprawdz" << endl;
		cout << "3. Podbij" << endl;
		while (true)
		{
			string stringAnswer;
			cin >> stringAnswer;
			if (checkIfIntFromOutputStream(stringAnswer, answer) && answer < 4 && answer>0)
				break;
			else
				cout << "Podaj odpowiednia opcje" << endl;
		}

		if (answer == 1)
		{
			return 1;
		}
		else if (answer == 2)
		{
			if (currentHighest - player.dealStake < player.account)
			{
				pot += currentHighest - player.dealStake;
				player.account -= currentHighest - player.dealStake;
				player.dealStake += currentHighest - player.dealStake;

				return answer;
			}
			else
			{
				pot += player.account;
				player.dealStake = player.dealStake + player.account;
				player.account = 0;
				player.ifAllIn = true;
				return answer;
			}
		}
		else if (answer == 3)
		{
			while (true)
			{
				cout << "Ile chcesz postawic? Max: " << player.account << endl;
				int stake;
				while (true)
				{
					string stringStake;
					cin >> stringStake;
					if (checkIfIntFromOutputStream(stringStake, stake))
						break;
					else
						cout << "Podaj odpowiednia liczbe" << endl;
				}
				if (stake <= player.account && stake + player.dealStake > currentHighest)
				{
					pot += stake;
					player.dealStake += stake;
					player.account -= stake;
					if (player.account == 0)
					{

						player.ifAllIn = true;
					}



					return answer;
				}

				else {
					cout << "Podaj wlasciwa wartosc" << endl;
					break;
				}

			}

		}
	}
}

void Deal::firstBet()
{
	bigBlind = ++players.begin();
	auto lastPlayer = --players.end();
	auto currentPlayer = players.begin();
	currentPlayer->dealStake = 50;
	currentPlayer->account = currentPlayer->account - 50;
	pot += currentPlayer->dealStake;
	cout << endl << currentPlayer->name << " wplaca mala ciemna." << endl;

	currentPlayer = next(currentPlayer, 1);

	currentPlayer->dealStake = 100;
	currentHighest = 100;
	currentPlayer->account = currentPlayer->account - 100;
	pot += currentPlayer->dealStake;

	cout << endl << currentPlayer->name << " wplaca duza ciemna." << endl;

	if (players.size() == 2)
		currentPlayer = players.begin();
	else
		currentPlayer = next(currentPlayer, 1);
	bool ifFirstRound = true;
	auto flague = currentPlayer;
	int playersAnswer;
	while ((currentPlayer != flague || ifFirstRound) && players.size() > 1)
	{
		ifFirstRound = false;
		if (!currentPlayer->ifAllIn) {
			playersAnswer = playersChoice(*currentPlayer);
			if (playersAnswer == 1)
			{
				if (currentPlayer == lastPlayer)
				{
					if (currentPlayer == flague)
					{
						flague = players.begin();
						ifFirstRound = true;
					}
					resignedPlayers.push_back(*currentPlayer);
					players.erase(currentPlayer);
					currentPlayer = players.begin();
					lastPlayer = --players.end();
				}
				else
				{
					if (currentPlayer == flague)
					{
						flague = next(currentPlayer, 1);
						ifFirstRound = true;
					}
					resignedPlayers.push_back(*currentPlayer);
					currentPlayer = players.erase(currentPlayer);
				}
			}
			else if (playersAnswer == 2)
			{
				if (currentPlayer == lastPlayer)
					currentPlayer = players.begin();
				else
					currentPlayer = next(currentPlayer, 1);
			}
			else if (playersAnswer == 3)
			{
				if (currentHighest < currentPlayer->dealStake)
					currentHighest = currentPlayer->dealStake;

				firstBetEveryNextRound(currentPlayer);
				return;
			}
		}
		else
		{
			if (currentPlayer == lastPlayer)
				currentPlayer = players.begin();
			else
				currentPlayer = next(currentPlayer, 1);
		}
	}
}

void Deal::firstBetEveryNextRound(list<Player>::iterator current)
{
	auto currentPlayer = current;
	auto flague = currentPlayer;
	auto lastPlayer = --players.end();
	if (currentPlayer == lastPlayer)
		currentPlayer = players.begin();
	else
		currentPlayer = next(currentPlayer, 1);
	int playersAnswer;

	while (currentPlayer != flague)
	{
		if (!currentPlayer->ifAllIn)
		{
			playersAnswer = playersChoice(*currentPlayer);
			if (playersAnswer == 1)
			{
				if (currentPlayer == lastPlayer)
				{
					if (currentPlayer == flague)
					{
						flague = players.begin();
					}
					resignedPlayers.push_back(*currentPlayer);
					players.erase(currentPlayer);
					currentPlayer = players.begin();
					lastPlayer = --players.end();
				}
				else
				{
					if (currentPlayer == flague)
					{
						flague = next(currentPlayer, 1);
					}
					resignedPlayers.push_back(*currentPlayer);
					currentPlayer = players.erase(currentPlayer);
				}
			}
			else if (playersAnswer == 2)
			{
				if (currentPlayer == lastPlayer)
					currentPlayer = players.begin();
				else
					currentPlayer = next(currentPlayer, 1);
			}
			else if (playersAnswer == 3)
			{
				if (currentHighest < currentPlayer->dealStake)
					currentHighest = currentPlayer->dealStake;
				flague = currentPlayer;
				if (currentPlayer == lastPlayer)
					currentPlayer = players.begin();
				else
					currentPlayer = next(currentPlayer, 1);
			}
		}
		else
		{
			if (currentPlayer == lastPlayer)
				currentPlayer = players.begin();
			else
				currentPlayer = next(currentPlayer, 1);
		}
	}
}

void Deal::everyNextBet(list<Player>::iterator currentPlayer)
{
	if (players.size() == 1)
		return;
	auto flague = currentPlayer;
	auto lastPlayer = --players.end();

	int playersAnswer;
	bool ifFirstRound = true;
	while (currentPlayer != flague || ifFirstRound)
	{
		ifFirstRound = false;
		if (!currentPlayer->ifAllIn)
		{
			playersAnswer = playersChoice(*currentPlayer);
			if (playersAnswer == 1)
			{
				if (currentPlayer == lastPlayer)
				{
					if (currentPlayer == flague)
					{
						flague = players.begin();
						ifFirstRound = true;
					}
					resignedPlayers.push_back(*currentPlayer);
					players.erase(currentPlayer);
					currentPlayer = players.begin();
					lastPlayer = --players.end();

				}
				else
				{
					if (currentPlayer == flague)
					{
						flague = next(currentPlayer, 1);
						ifFirstRound = true;
					}
					resignedPlayers.push_back(*currentPlayer);
					currentPlayer = players.erase(currentPlayer);

				}
			}
			else if (playersAnswer == 2)
			{
				if (currentPlayer == lastPlayer)
					currentPlayer = players.begin();
				else
					currentPlayer = next(currentPlayer, 1);
			}
			else if (playersAnswer == 3)
			{
				if (currentHighest < currentPlayer->dealStake)
					currentHighest = currentPlayer->dealStake;
				flague = currentPlayer;
				if (currentPlayer == lastPlayer)
					currentPlayer = players.begin();
				else
					currentPlayer = next(currentPlayer, 1);
			}
		}
		else
		{
			if (currentPlayer == lastPlayer)
				currentPlayer = players.begin();
			else
				currentPlayer = next(currentPlayer, 1);
		}
	}
}

void Deal::dividePot()
{

	int betForEveryone = pot / WinnersOfTheDeal.size();
	cout << "Zwyciezcy dostana po " << betForEveryone << endl;
	for (Player winner : WinnersOfTheDeal)
	{
		for (Player& player : players)
			if (player.name == winner.name)
				player.account += betForEveryone;
	}
}

bool Deal::printDeckToFile()
{
	ofstream file("errorDeck.txt");
	if (file.good())
	{
		for (Card& card : errorDeck)
		{
			file << "shuffledDeck.push_back(Card(\"" << card.value << "\",\"" << card.suitSymbol << "\"," << card.numberValue << "));" << endl;
		}
		file.close();
		return true;
	}
	file.close();
	return false;

}