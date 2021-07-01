#include "Player.h"
#include <string.h>

using namespace std;

Player::Player(string name)
{
	this->name = name;
}

Player::~Player()
{
	hand.clear();
}

Player::Player(const Player& copyPlayer)
{
	this->account = copyPlayer.account;
	this->dealStake = copyPlayer.dealStake;
	copy(copyPlayer.hand.begin(), copyPlayer.hand.end(), back_inserter(this->hand));
	//this->hand = copyPlayer.hand;
	this->ifAllIn = copyPlayer.ifAllIn;
	this->name = copyPlayer.name;
	this->highestFiveCards = copyPlayer.highestFiveCards;
	
}

int Player::makeBet(int currentHighestBet,int &pot, bool ifFlague, vector<Card> cardsOnTable)
{

	int answer;
	

	while (true)
	{
		cout << endl << endl;
		cout << "Nazwa gracza: "<<name << endl;
		cout << "Konto: " << account << endl;
		cout << "Twoja obecna stawka: " << dealStake << endl;
		cout << "Najwyzsza stawka: " << currentHighestBet << endl;
		cout << "Pula: " << pot << endl;
		if (!cardsOnTable.empty())
		{
			cout << "Karty na stole:"<<endl;
			for (auto card : cardsOnTable)
				cout << card.value << " " << card.suitSymbol << endl;
		}
		cout << "Karty na rece:" << endl;
		cout << hand[0].value  <<" "<< hand[0].suitSymbol << endl; 
		cout << hand[1].value << " " << hand[1].suitSymbol << endl;

		
		cout << "Co chcesz zrobic?" << endl;
		cout << "1. Pas/czekaj" << endl;
		if(!ifFlague)
		cout << "2. Sprawdz" << endl;
		cout << "3. Podbij" << endl;

		cin >> answer;

		if (answer == 1)
			return answer;
		else if (answer == 2 && !ifFlague )
		{
			if (currentHighestBet - dealStake < account)
			{
				pot += currentHighestBet - dealStake;
				account -= currentHighestBet - dealStake;
				dealStake += currentHighestBet - dealStake;
				
				return answer;
			}
			else
			{
				pot += account;
				dealStake = dealStake + account;
				account = 0;
				//ifAllIn = true;
				return 4;
			}
		}
		else if (answer == 3)
		{
			while (true)
			{
				cout << "Ile chcesz postawic? Max: " << account<< endl;
				int stake;
				cin >> stake;
				if (ifFlague && stake>0 && stake <= account)
				{
					pot += stake;
					dealStake += stake;
					account -= stake;
					if (account == 0)
					{
						answer = 5;
						ifAllIn = true;
					}
					
					

					return answer;
				}
				else if (stake <= account && stake > currentHighestBet)
				{
					pot += stake;
					dealStake+=stake;
					account -= stake;
					if (account==0)
					{
						answer = 4;
						//ifAllIn = true;
					}
					
					return answer;
				}
				else {
					cout << "Podaj wlasciwa wartosc" << endl;
					break;
				}
					
			}
			
		}
		else
			cout << "Podaj wlasciwa opcje" << endl;
	}
		
}

int Player::makeBetAfterCardsOnTable(int currentHighestBet, int& pot, bool ifFlague, vector<Card> cardsOnTable, bool ifFirstRound)
{

	int answer;


	while (true)
	{
		cout << endl << endl;
		cout << "Nazwa gracza: " << name << endl;
		cout << "Konto: " << account << endl;
		cout << "Twoja obecna stawka: " << dealStake << endl;
		cout << "Najwyzsza stawka: " << currentHighestBet << endl;
		cout << "Pula: " << pot << endl;
		if (!cardsOnTable.empty())
		{
			cout << "Karty na stole:" << endl;
			for (auto card : cardsOnTable)
				cout << card.value << " " << card.suitSymbol << endl;
		}
		cout << "Karty na rece:" << endl;
		cout << hand[0].value << " " << hand[0].suitSymbol << endl;
		cout << hand[1].value << " " << hand[1].suitSymbol << endl;


		cout << "Co chcesz zrobic?" << endl;
		cout << "1. Pas/czekaj" << endl;
		if (!ifFlague && !ifFirstRound)
			cout << "2. Sprawdz" << endl;
		cout << "3. Podbij" << endl;

		cin >> answer;

		if (answer == 1)
			return answer;
		else if (answer == 2 && (!ifFlague || !ifFirstRound))
		{
			if (currentHighestBet - dealStake < account)
			{
				pot += currentHighestBet - dealStake;
				account -= currentHighestBet - dealStake;
				dealStake += currentHighestBet - dealStake;

				return answer;
			}
			else
			{
				pot += account;
				dealStake = dealStake + account;
				account = 0;
				//ifAllIn = true;
				return 4;
			}
		}
		else if (answer == 3)
		{
			while (true)
			{
				cout << "Ile chcesz postawic? Max: " << account << endl;
				int stake;
				cin >> stake;
				if (ifFlague && stake > 0 && stake <= account)
				{
					pot += stake;
					dealStake += stake;
					account -= stake;
					if (account == 0)
					{
						answer = 5;
						ifAllIn = true;
					}



					return answer;
				}
				else if (stake <= account && stake+dealStake > currentHighestBet)
				{
					pot += stake;
					dealStake += stake;
					account -= stake;
					if (account == 0)
					{
						answer = 4;
						//ifAllIn = true;
					}

					return answer;
				}
				else {
					cout << "Podaj wlasciwa wartosc" << endl;
					break;
				}

			}

		}
		else
			cout << "Podaj wlasciwa opcje" << endl;
	}

}