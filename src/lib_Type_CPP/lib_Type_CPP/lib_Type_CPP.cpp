// lib_Type_CPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "Embedded_Type.h"


byte buff[] = {1, 0, 2, 0, 4, 5, 6, 7, 8, 9};

int _tmain(int argc, _TCHAR* argv[])
{
	char str[128];
	TypeBuffer.Byte[1] = 1;
	PutHexFromBin(str, 0, 0, 10, TYPE_LITTLE_ENDIAN | TYPE_ADD_SPACE | TYPE_ADD_CHAR);
	printf("The short is: %s\n", str);

	// wait for keypress before exit
	system("PAUSE");
	return 0;
}
