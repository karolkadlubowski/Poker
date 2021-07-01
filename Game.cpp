#include "Game.h"
#include <iostream>
#include <string>
#include <sstream>


#include "Functions.h"
#include "HandsDistinguisher.h"

//#include "Player.h"


using namespace std;

Game::Game()
{
	
	int playersAmount=0;
	string checkIfInt;
	while(true){
		cout << "Podaj ilosc graczy (2-4)" << endl;
		cin >> checkIfInt;
		if (checkIfIntFromOutputStream(checkIfInt, playersAmount))
		{
			if (playersAmount > 1 && playersAmount < 5)
				break;
			else
				cout << "Liczba graczy musi byc z przedzialu 2-4" << endl;
		}
		else
			cout << "Podaj liczbe" << endl;
	} 

	
	string name;

	for (int i = 1; i <= playersAmount; i++)
	{
		cout << "Podaj imie gracza nr " + convertIntToString(i)<< endl;
		cin >> name;
		bool isNameLocked = false;
		for (Player player : players)
		{
			if (player.name == name)
			{
				i--;
				cout << "To imie jest juz zajete przez innego gracza, podaj inne." << endl;
				isNameLocked = true;
				break;
			}
		}
		if(!isNameLocked)
			players.push_back(Player(name));
	}

	cout << endl << endl << endl;
	
	}


void Game::ProceedToTheGame() 
{

	
	while (true)
	{
		if (players.size()> 1)
		{
			Deal deal(deck, players);
			
			try {
				
				deal.hand2CardsAround();


				deal.firstBet();

				deal.showThreeCards();
				deal.everyNextBet(deal.players.begin());



				deal.showOneCard();
				deal.everyNextBet(deal.players.begin());


				deal.showOneCard();

				deal.everyNextBet(deal.players.begin());

				HandsDistinguisher handDistinguisher;
				handDistinguisher.concludeResults(deal);


				deal.dividePot();
				for (Player player : deal.resignedPlayers)
					deal.players.push_back(player);
				updateAccounts(deal.players);
				if (players.size() > 1)
				{
					players.push_back(*players.begin());
					players.pop_front();
				}
				cin;
			}
			catch (const exception& ex)
			{
				cout << "Cos poszlo nie tak, sprawdz zapisana talie." << endl;
				deal.printDeckToFile();
				return;
			}
		}
		else
		{
			cout << "Przy stole pozostal tylko jeden gracz: " << players.begin()->name << endl;
			return;
		}
	}
}

void Game::updateAccounts(list<Player> playersOfTheDeal)// do poprawki
{
	for (Player playerOfTheDeal : playersOfTheDeal)
	{
		for (Player& player : players)
		{
			if (playerOfTheDeal.name == player.name)
				player.account = playerOfTheDeal.account;
		}
	}

	auto pplayer = players.begin();
	//auto pplayerOfTheDeal = playersOfTheDeal.begin();
	while ( pplayer != players.end() )
	{
		//pplayer->account = pplayerOfTheDeal->account;
		if (pplayer->account == 0)
		{
			cout << pplayer->name << " przegrywa wszystkie pieniadze i zostaje usuniety z gry" << endl;
			pplayer = players.erase(pplayer);
			//pplayerOfTheDeal = playersOfTheDeal.erase(pplayerOfTheDeal);
		}
		else
		{
			pplayer++;
			//pplayerOfTheDeal++;
		}

	}
}

