// lib_Type_CPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "Embedded_Type.h"


byte buff[] = {0, 0, 0, 0, 4, 5, 6, 7, 8, 9};

int _tmain(int argc, _TCHAR* argv[])
{
	printf("The short is: %d\n", ToShort(2, 1));

	// wait for keypress before exit
	system("PAUSE");
	return 0;
}
