// lib_Type_CPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "Embedded_Type.h"


byte buff[] = {0, 0, 0, 0, 4, 5, 6, 7, 8, 9};

int _tmain(int argc, _TCHAR* argv[])
{
	double x = ToDouble(2, 8);
	long64 y = GetLong64(&x, 0);
	printf("The short is: %f\n", ToDouble(1000, 25));

	// wait for keypress before exit
	system("PAUSE");
	return 0;
}
