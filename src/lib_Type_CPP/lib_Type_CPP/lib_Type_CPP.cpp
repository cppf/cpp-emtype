// lib_Type_CPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "Embedded_Type.h"


byte buff[] = {0, 0, 0, 0, 4, 5, 6, 7, 8, 9};

int _tmain(int argc, _TCHAR* argv[])
{
	PutBit(0, 16, 1);
	PutBit(1, 0, 0);
	int shortval = GetInt(0);
	printf("The short is: %d\n", shortval);

	// wait for keypress before exit
	system("PAUSE");
	return 0;
}
