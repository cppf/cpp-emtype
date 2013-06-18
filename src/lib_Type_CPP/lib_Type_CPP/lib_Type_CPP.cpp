/*
----------------------------------------------------------------------------------------
	Embedded_Type: Testing and debugging source code (Visual Studio)
	File: lib_Type_CPP.cpp

    This file is part of Embedded_Type. For more details, go through
	Readme.txt. For copyright information, go through copyright.txt.

    Embedded_Type is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Embedded_Type is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
----------------------------------------------------------------------------------------
*/



#include "stdafx.h"
#include <stdlib.h>
#include "Embedded_Type.h"



byte buff[] = {1, 0, 2, 0, 4, 5, 6, 7, 8, 9};



int _tmain(int argc, _TCHAR* argv[])
{
	char str[128];
	TypeBuffer.Byte[1] = 65;
	PutHexFromBin(str, 0, 0, 2, TYPE_LITTLE_ENDIAN | TYPE_ADD_SPACE | TYPE_ADD_CHAR);
	strcpy(str, "103");
	PutBinFromHex(buff, 0, 4, str, 0, TYPE_LITTLE_ENDIAN);
	printf("The short is: %s\n", str);

	// wait for keypress before exit
	system("PAUSE");
	return 0;
}
