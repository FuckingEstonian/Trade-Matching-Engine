
#include <iostream>
#include "Engine.h"

int main()
{
	ENG::Engine Aggressor;
	Aggressor.Add_Trader();
	Aggressor.Add_Trader();
	Aggressor.Print();
	Aggressor.Memory_cleaner();
}

