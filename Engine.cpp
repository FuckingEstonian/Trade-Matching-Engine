#include "Engine.h"
namespace ENG
{
	void Engine::Print()
	{
		Trade_Data* Pointer = &Data;
		while (Pointer != NULL)
		{
			std::cout << "Name : " << Pointer->Trader_Identifier << std::endl;
			std::cout << "Operation : " << Pointer->Side << std::endl;
			std::cout << "Quantity : " << Pointer->Quatntity << std::endl;
			std::cout << "Price : " << Pointer->Price << std::endl;
			std::cout << "Number : " << Pointer->Number_in_list << std::endl;
			if (Pointer->next == NULL) std::cout << "Next NULL" << std::endl;
			if (Pointer->prev == NULL) std::cout << "Prev NULL" << std::endl;
			std::cout << "++++++++++++++++++++++++++++++++" << std::endl;
			Pointer = Pointer->next;
		}
	}


	Trade_Data* Engine::Get_last_nod()
	{
		Trade_Data* last_nod = &Data;
		while (last_nod->next != NULL)
		{
			last_nod = last_nod->next;
		}
		return last_nod;
	}

	std::string Engine::Get_Identifier(const std::string& Input)
	{
		std::string Identifier;
		short iterator(0);

		while (Input[iterator] != ' ')
		{
			Identifier += Input[iterator];
			iterator++;
		}
		return Identifier;
	}
	std::string Engine::Get_Side(const std::string& Input)
	{
		std::string Side;
		short iterator(0);

		while (Input[iterator] != ' ')
		{
			iterator++;
		}
		Side = Input[iterator+1];

		if (Side == "b") Side = "B";
		if (Side == "s") Side = "S";
		if (Side != "B" && Side != "S")
			throw std::exception("Wrong enter (Side must be 'B' or 'S')");
		
		return Side;
	}
	int Engine::Get_Quantity(const std::string& Input)
	{
		int Quantity(0);
		std::string S_Quantity;
		short iterator(0);
		short space_number(0);

		while (space_number != 2)
		{
			if (Input[iterator] == ' ') space_number++;
			iterator++;
		}

		while (Input[iterator] != ' ')
		{
			S_Quantity += Input[iterator];
			if (S_Quantity == "-")
				throw std::exception("Wrong enter (Quantity can't be negative)\n");
			iterator++;
		}

		Quantity = stoi(S_Quantity);
		if (Quantity == 0)
			throw std::exception("Wrong enter (Quantity can't be 0)\n");

		return Quantity;
	}
	int Engine::Get_Price(const std::string & Input)
	{
		int Price(0);
		std::string S_Price;
		short iterator(0);
		short space_number(0);

		while (space_number != 3)
		{
			if (Input[iterator] == ' ') space_number++;
			iterator++;
		}

		while (Input[iterator])
		{
			S_Price += Input[iterator];
			if (S_Price == "-")
				throw std::exception("Wrong enter (Price can't be negative)\n");
			iterator++;
		}

		Price = stoi(S_Price);
		if (Price == 0)
			throw std::exception("Wrong enter (Price can't be 0)\n");

		return Price;
	}
	void Engine::Input_Check(const std::string& Input)
	{
		size_t correct_space_number(3); /// size_t
		size_t min_char_number(7);

		size_t iterator(0);
		size_t real_space_number(0);

		if (Input.size() < min_char_number)
			throw std::exception("Wrong enter(not enough symbols in row)\n");
		if (Input[iterator] == ' ')
			throw std::exception("Wrong enter(row can't start from 'space')\n");

		while (iterator <= Input.size())
		{
			if (Input[iterator] == ' ' &&
				iterator != Input.size() )real_space_number++;
			iterator++;
		}

		if (real_space_number != correct_space_number)
		{
			throw std::exception("Wrong enter (number of wor must be 4)\n");
		}

	}

	void Engine::Add_Trader()
	{
		Trade_Data* Last_nod = Get_last_nod();
		Trade_Data* New_nod = new Trade_Data ((Last_nod->Number_in_list)+1);
		
		Add_Data_For_Trader(*New_nod);

		Last_nod->next = New_nod;
		New_nod->prev = Last_nod;
	}

	void Engine::Add_Data_For_Trader(Trade_Data& Trader)
	{
		std::string Input;
		bool check_trigger(false);
		while (check_trigger != true)
		{
			std::cout << "Enter string: ";
			try
			{
				std::getline(std::cin, Input);

				Engine::Input_Check(Input);

				Trader.Trader_Identifier = Get_Identifier(Input);
				Trader.Side = Get_Side(Input);
				Trader.Quatntity = Get_Quantity(Input);
				Trader.Price = Get_Price(Input);
				check_trigger = true;
			}
			catch(std::exception & input_excep)
			{
				std::cout << input_excep.what() << std::endl;
			}	
		}
	}

	void Engine::Memory_cleaner()
	{
		std::cout << "Cleaner started" << std::endl;
		Trade_Data* Dead_nod = Get_last_nod();
		Trade_Data* temp;
		while (Dead_nod->Number_in_list != 1)
		{
			temp = Dead_nod;
			Dead_nod = Dead_nod->prev;
			std::cout << temp->Number_in_list << std::endl;

			delete temp;
		}
		std::cout << "Cleaner ended" << std::endl;
	}
}
