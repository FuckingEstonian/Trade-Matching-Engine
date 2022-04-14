#pragma once
#include <iostream>

class Trade_Data
{
public:
	std::string Trader_Identifier;
	std::string Side;
	unsigned int Quatntity;
	unsigned int Price;
	unsigned int Number_in_list;

	Trade_Data* next;
	Trade_Data* prev;

	Trade_Data(int number = 1, std::string Trader = "T0", std::string Operation = "No", int Pr = 0,
		int Quan = 0) : Trader_Identifier(Trader), Side(Operation), 
		Price(Pr), Quatntity(Quan), next(NULL), prev(NULL), Number_in_list(number) {};

};

