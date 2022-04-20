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

class Output_Data
{
public:
	std::string T1;
	std::string T2;
	std::string Sid;
	unsigned int Q1;
	unsigned int Q2;
	unsigned int Pr;
	bool out_triger;

	Output_Data* next;
	Output_Data* prev;

	Output_Data(std::string Trader1 = "empty", std::string Trader2 = "empty", std::string Side = "No",
		unsigned int QuanT1 = 0, unsigned int QuanT2 = 0, unsigned int Price = 0) :
		T1(Trader1), T2(Trader2), Q1(QuanT1), Q2(QuanT2), Pr(Price),
		Sid(Side), out_triger(false), next(NULL), prev(NULL) {};
	
	Output_Data* Add_nod();
	void Geet_Data_from_Traders(Trade_Data*, Trade_Data*);
	void Clean_It();
	bool Analyse();
	void Print();
	void Print_for_recursion();

};

