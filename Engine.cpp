#include "Engine.h"
namespace ENG
{
	void Engine::Print()
	{
		Trade_Data* Pointer = &Data;
		while (Pointer != NULL)
		{

			std::cout << "¹ " << Pointer->Number_in_list << "\t";
			std::cout << Pointer->Trader_Identifier << " ";
			std::cout << Pointer->Side << " ";
			std::cout << Pointer->Quatntity << " ";
			std::cout << Pointer->Price << "\n";
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

	Trade_Data* Engine::Execute_nod(Trade_Data& Nod)
	{
		Trade_Data* temp = &Nod;
		if (temp == &Data)
		{
			Data.Quatntity = 0;
			Data.Side = "No";
			Data.Price = 10000;
			return temp;
		}
		Trade_Data* temp_next = Nod.next;
		Trade_Data* temp_prev = Nod.prev;

		if(temp_next != NULL) temp_next->prev = temp_prev;
		temp_prev->next = temp_next;

		delete &Nod;
		return temp_prev;
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
		size_t correct_space_number(3); 
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

	bool Engine::Analyse_Market(Trade_Data* Order)
	{
		Trade_Data* temp_order = Order->prev;
		int total_sellers(0);
		int total_buyers(0);
		int money_sell(0);
		int money_buy(0);

		while (temp_order != NULL)
		{
			if (temp_order->Side == "B" && temp_order->Quatntity != 0)
			{
				total_buyers += temp_order->Quatntity;
				money_buy += (temp_order->Quatntity) * temp_order->Price;
			}
			if (temp_order->Side == "S" && temp_order->Quatntity != 0)
			{
				total_sellers += temp_order->Quatntity;
				money_sell += (temp_order->Quatntity) * temp_order->Price;
			}
			temp_order = temp_order->prev;
		}

		if ((total_buyers <= 1 && Order->Side == "S") ||
			(total_sellers <= 1 && Order->Side == "B"))
		{
			std::cout << Order->Number_in_list << "\tfalse\n";
			return false;
		}

		unsigned int mutch_number = std::min(total_buyers, total_sellers);
		unsigned int s_price(0), b_price(0);
		if (total_sellers != 0)
			s_price = (money_sell / total_sellers);
		if (total_buyers != 0)
			b_price = (money_buy / total_buyers);

		if ((Order->Side == "B" && Order->Price > s_price) ||
			(Order->Side == "S" && Order->Price < b_price))
		{
			std::cout << Order->Number_in_list << "\ttrue\t";
			if (Order->Side == "B")std::cout << s_price << "\n";
			if (Order->Side == "S")std::cout << b_price << "\n";
			return true;
		}
		return false;
	}

	void Engine::Add_Trader(std::string& Input)
	{
		Trade_Data* Last_nod = Get_last_nod();
		Trade_Data* New_nod = new Trade_Data ((Last_nod->Number_in_list)+1);
		
		Add_Data_For_Trader(*New_nod, Input);

		Last_nod->next = New_nod;
		New_nod->prev = Last_nod;
	}

	void Engine::Add_Data_For_Trader(Trade_Data& Trader, std::string& Input)
	{
		//std::string Input_Safe = "Nothing";
		bool check_trigger(false);
		while (check_trigger != true)
		{
			if(Input == "nothing")std::cout << "Enter string: ";
			try
			{
				if (Input == "nothing")std::getline(std::cin, Input);
				if (Input == "end")return;
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
				Input = "nothing";
			}	
		}
	}

	void Engine::Combine_Similar_Traders()
	{
		Trade_Data* Offers = & Data;
		while (Offers != NULL)
		{
			Trade_Data* temp = Offers->next;
			while (temp != NULL)
			{
				if (Offers->Trader_Identifier == temp->Trader_Identifier &&
					Offers->Side == temp->Side &&
					Offers->Price == temp->Price)
				{
					Offers->Quatntity += temp->Quatntity;
					temp = Engine::Execute_nod(*temp);
				}

				temp = temp->next;
			}

			Offers = Offers->next;
		}
	}

	Trade_Data* Engine::Get_best_offer(const std::string& Side, Trade_Data* Order)
	{
		Trade_Data* temp_order = Order->prev;
		Trade_Data* best_offer = Order;
		while (temp_order != NULL)
		{
			if (Side == "B" && temp_order->Side != Side && temp_order->Price <= best_offer->Price)
			{
				best_offer = temp_order;
			}
			if (Side == "S" && temp_order->Side != Side && temp_order->Price >= best_offer->Price)
			{
				best_offer = temp_order;
			}
			temp_order = temp_order->prev;
		}
		if (best_offer == Order) best_offer = NULL;
		return best_offer;
	}

	Trade_Data* Engine::Try_to_Buy(Trade_Data* Order,
		int recursion_depth = 0, Output_Data* Output = NULL)
	{
	
		Trade_Data* best_ofer = Engine::Get_best_offer(Order->Side, Order);
		if (best_ofer == NULL) return Order;
		
		if (Output == NULL) Output = new Output_Data;//
		else Output = Output->Add_nod();
		Output->Geet_Data_from_Traders(Order, best_ofer);//

		if (best_ofer->Quatntity > Order->Quatntity)
		{
			if(recursion_depth == 0)//
				Engine::Print_trade(Order, best_ofer);
			best_ofer->Quatntity -= Order->Quatntity;
			return Engine::Execute_nod(*Order);
		}
		
		if (best_ofer->Quatntity == Order->Quatntity)
		{
			if(recursion_depth == 0)//
				Engine::Print_trade(Order, best_ofer);
			Engine::Execute_nod(*best_ofer);
			return Engine::Execute_nod(*Order);
		}

		if (best_ofer->Quatntity < Order->Quatntity)
		{

			//Engine::Print_trade(Order, best_ofer);
			Order->Quatntity -= best_ofer->Quatntity;
			Engine::Execute_nod(*best_ofer);
			Trade_Data* Output_pointer = Engine::Try_to_Buy(Order, recursion_depth+1, Output);
			if (recursion_depth == 0)//
			{
				if (!Output->Analyse())
					Output->Print();
				else Output->Print_for_recursion();
				Output->Clean_It();
			}//
			return Output_pointer;
		}
	}
	
	void Engine::Match_orders()
	{
		Trade_Data* Order = &Data;
		if (Data.next == NULL || Data.Side == "No" )
		{
			std::cout << "Nothing to match, or first order is empty!\n";
			return;
		}
		while (Order != NULL)
		{
			Order = Engine::Try_to_Buy(Order);
			if(Order != NULL)Order = Order->next;
		}
	}

	void Engine::Print_trade(const Trade_Data* Order, const Trade_Data* best_ofer)
	{
		if (Order->Side == "B")
		{
			std::cout << Order->Trader_Identifier << "+" <<
				std::min(best_ofer->Quatntity, Order->Quatntity)<< "@" << best_ofer->Price << "\t";
			std::cout << best_ofer->Trader_Identifier << "-" <<
				std::min(best_ofer->Quatntity, Order->Quatntity) << "@" << best_ofer->Price << std::endl;
		}
		if (Order->Side == "S")
		{
			std::cout << best_ofer->Trader_Identifier << "+" <<
				std::min(best_ofer->Quatntity, Order->Quatntity) << "@" << best_ofer->Price << "\t";
			std::cout << Order->Trader_Identifier << "-" <<
				std::min(best_ofer->Quatntity, Order->Quatntity) << "@" << best_ofer->Price << std::endl;
		}
	}

	void Engine::Menu()
	{
		std::cout << "Welcome to Trade Matching Engine.\nPlease, leave a comment in my GitHub repositori:\nhttps://github.com/FuckingEstonian/Trade-Matching-Engine\nThank you!\n\n";
		std::cout << "Enter your order in next way '<Trader Identifier> <Side> <Quantity> <Price>'\n";
		std::cout << "To stop input type 'end'\n";
		std::cout << "Enter string: ";

		std::string Input = "nothing";
		std::getline(std::cin, Input);
		Engine::Add_Data_For_Trader(Data, Input);
		
		do {
			while (Input != "end")
			{
				//Engine::Print();
				std::cout << "Enter string: ";
				std::getline(std::cin, Input);
				if (Input == "end")break;
				Engine::Add_Trader(Input);
			}
			system("cls");
			Engine::Print();

			std::cout << "\nMatched Orders:\n";
			Engine::Match_orders();

			std::cout << "\nResting Orders\n";
			Engine::Print();

			//Engine::Combine_Similar_Traders();
			std::cout << "\nAdd more orders? (type 'yes' or 'no'): ";
			std::getline(std::cin,Input);

		} while (Input == "yes");

		Engine::Memory_cleaner();
	}

	void Engine::Memory_cleaner()
	{
		//std::cout << "Cleaner started" << std::endl;
		Trade_Data* Dead_nod = Get_last_nod();
		Trade_Data* temp;
		while (Dead_nod->Number_in_list != 1)
		{
			temp = Dead_nod;
			Dead_nod = Dead_nod->prev;
			//std::cout << temp->Number_in_list << std::endl;

			delete temp;
		}
		std::cout << "Memory cleaned!" << std::endl;
	}
}
