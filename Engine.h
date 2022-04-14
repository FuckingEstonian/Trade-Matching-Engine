#pragma once
#include"Trade_Data.h"
#include <string>
namespace ENG
{ 
	class Engine
	{
	private:

		Trade_Data Data;

		Trade_Data* Get_last_nod();

		std::string Get_Identifier(std::string);
		std::string Get_Side(std::string);
		int Get_Quantity(std::string);
		int Get_Price(std::string);

	public:

		void Print();  // test

		void Add_Trader();

		void Memory_cleaner(); // must be private

		void Add_Data_For_Trader(Trade_Data&);

	};
}
