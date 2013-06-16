// lib_Type_CPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "Embedded_Type.h"


byte buff[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

int _tmain(int argc, _TCHAR* argv[])
{
	TypeBuffer.Byte[3] = 65;
	char charval = GetChar(buff, 3);
	printf("The byte is: %c\n", charval);

	// wait for keypress before exit
	system("PAUSE");
	return 0;
}
