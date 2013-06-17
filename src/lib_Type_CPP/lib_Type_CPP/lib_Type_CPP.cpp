// lib_Type_CPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "Embedded_Type.h"


byte buff[] = {1, 0, 2, 0, 4, 5, 6, 7, 8, 9};

int _tmain(int argc, _TCHAR* argv[])
{
	TypeBuffer.Byte[2] = 2;
	printf("The short is: %d\n", GetUint16Sum(0, 4));

	// wait for keypress before exit
	system("PAUSE");
	return 0;
}
