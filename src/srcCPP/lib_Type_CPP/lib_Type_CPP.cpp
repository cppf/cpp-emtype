/*
----------------------------------------------------------------------------------------
	emType: Testing and debugging source code (Visual Studio)
	File: lib_Type_CPP.cpp

    This file is part of emType. For more details, go through
	Readme.txt. For copyright information, go through copyright.txt.

    emType is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    emType is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with emType.  If not, see <http://www.gnu.org/licenses/>.
----------------------------------------------------------------------------------------
*/



#include "stdafx.h"
#include <stdlib.h>
#include "emType.h"



byte buff[] = {1, 0, 2, 0, 4, 5, 6, 7, 8, 9};



int _tmain(int argc, _TCHAR* argv[])
{
	char str[128];
	emType.Byte[1] = 65;
	GetHexFromBin(str, 10, &emType, 0, 2, LITTLE_ENDIAN | ADD_SPACE | ADD_CHAR);
	printf("str = %s\n", str);
	strcpy(str, "103");
	PutBinFromHex(0, 4, str, LITTLE_ENDIAN);
	printf("The short is: %d\n", GetShort(0));

	// wait for keypress before exit
	system("PAUSE");
	return 0;
}
