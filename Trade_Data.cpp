#include "Trade_Data.h"

Output_Data* Output_Data::Add_nod()
{
	Output_Data* temp = new Output_Data;
	this->next = temp;
	temp->prev = this;
	return temp;
}

void Output_Data::Geet_Data_from_Traders(Trade_Data* Order, Trade_Data* best_offer)
{
	this->T1 = Order->Trader_Identifier;
	this->T2 = best_offer->Trader_Identifier;
	
	this->Q1 = Order->Quatntity;
	this->Q2 = best_offer->Quatntity;

	this->Sid = Order->Side;
	this->Pr = best_offer->Price;

}

void Output_Data::Clean_It()
{
	Output_Data* temp = this;
	if (this == NULL) return;
	while (temp->prev != NULL)
	{
		temp = temp->prev;
	}
	while (temp != NULL)
	{
		Output_Data* dead = temp;
		temp = temp->next;
		delete dead;
	}
}

bool Output_Data::Analyse()
{
	if (this->next == NULL)return false;
	Output_Data* pointer1 = this;
	while (pointer1 != NULL)
	{
		Output_Data* pointer2 = pointer1->next;
		while (pointer2 != NULL)
		{
			if (pointer2->T2 == pointer1->T2 && pointer2->Pr == pointer1->Pr)
			{
				pointer1->Q1 += pointer2->Q1;
				pointer1->Q2 += std::min(pointer2->Q1,pointer2->Q2);

				pointer2->prev->next = pointer2->next;
				if (pointer2->next != NULL) pointer2->next->prev = pointer2->prev;
				Output_Data* dead = pointer2;
				pointer2 = pointer2->prev;
				delete dead;
			}
			pointer2 = pointer2->next;
		}
		pointer1 = pointer1->next;
	}
	return true;
}

void Output_Data::Print()
{
	Output_Data* Output = this;
	while (Output != NULL)
	{
		
		if (Output->Sid == "S")
		{
			std::cout << Output->T2 << "+" << Output->Q2 << "@" << Output->Pr << "\t";
			std::cout << Output->T1 << "-" << Output->Q2 << "@" << Output->Pr << "\n";
		}
		else
		{
			std::cout << Output->T1 << "+" << Output->Q2 << "@" << Output->Pr << "\t";
			std::cout << Output->T2 << "-" << Output->Q2 << "@" << Output->Pr << "\n";
		}
		
		Output = Output->next;
	}
}

void Output_Data::Print_for_recursion()
{
	Output_Data* Output = this;
	while (Output != NULL)
	{
		if (Output->Sid == "S")
			std::cout << Output->T2 << "+" << Output->Q2 << "@" << Output->Pr << "\t";
		else
			std::cout << Output->T1 << "+" << Output->Q2 << "@" << Output->Pr << "\t";
		Output = Output->next;
	}
	Output = this;
	while (Output != NULL)
	{
		if (Output->Sid == "S")
			std::cout << Output->T1 << "-" << Output->Q2 << "@" << Output->Pr << "\t";
		else
			std::cout << Output->T2 << "-" << Output->Q2 << "@" << Output->Pr << "\t";
		Output = Output->next;
	}
	std::cout << std::endl;
}