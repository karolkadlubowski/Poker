#include "Functions.h"

#include <sstream>

using namespace std;



bool checkIfIntFromOutputStream(string isNumber, int& number)
{

	unique_ptr<stringstream> isInt(new stringstream(isNumber));

	if (*isInt >> number)
		return true;
	else
		return false;
}

string convertIntToString(int number)
{
	stringstream ss;
	ss << number;
	string result;
	ss >> result;
	return result;
}