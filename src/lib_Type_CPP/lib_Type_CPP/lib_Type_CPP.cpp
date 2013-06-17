// lib_Type_CPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "Embedded_Type.h"


byte buff[] = {0, 0, 0, 0, 4, 5, 6, 7, 8, 9};

int _tmain(int argc, _TCHAR* argv[])
{
	PutFloat(1, 1.1f);
	float shortval = GetFloat(1);
	printf("The short is: %f\n", shortval);

	// wait for keypress before exit
	system("PAUSE");
	return 0;
}
