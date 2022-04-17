#pragma once
#include"Trade_Data.h"
#include <string>
#include <exception>
namespace ENG
{ 
	class Engine
	{
	private:

		Trade_Data Data;

		Trade_Data* Get_last_nod();
		Trade_Data* Execute_nod(Trade_Data&);


		std::string Get_Identifier(const std::string &);
		std::string Get_Side(const std::string &);
		int Get_Quantity(const std::string &);
		int Get_Price(const std::string &);
		void Input_Check(const std::string &);
		Trade_Data* Get_best_offer(const std::string&, Trade_Data*);

		Trade_Data* Try_to_Buy(Trade_Data*);
		

	public:

		void Menu();

		void Print();  

		void Add_Trader(std::string& );

		void Add_Data_For_Trader(Trade_Data&, std::string&);

		void Combine_Similar_Traders(); // in case if you want to compress list of orders;

		void Match_orders();

		void Memory_cleaner(); 
	};
}
