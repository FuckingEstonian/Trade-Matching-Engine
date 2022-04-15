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

		std::string Get_Identifier(const std::string &);
		std::string Get_Side(const std::string &);
		int Get_Quantity(const std::string &);
		int Get_Price(const std::string &);
		void Input_Check(const std::string &);



	public:

		void Menu();

		void Print();  // test

		void Add_Trader(std::string& );

		void Memory_cleaner(); // must be private

		void Add_Data_For_Trader(Trade_Data&, std::string&);

	};
}
