// lib_Type_CPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "Embedded_Type.h"

/*
byte buff[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

int _tmain(int argc, _TCHAR* argv[])
{
	int bit = GetBit(buff, 1, 0);
	printf("The bit is: %d\n", bit);
	// wait for keypress before exit
	system("PAUSE");
	return 0;
}
*/
// variadic_macros.cpp
#include <stdio.h>
#define EMPTY

#define CHECK1(x, ...) if (!(x)) { printf(__VA_ARGS__); }
#define CHECK2(x, ...) if ((x)) { printf(__VA_ARGS__); }
#define CHECK3(...) { printf(__VA_ARGS__); }
#define MACRO(s, ...) printf(s, __VA_ARGS__)

int main() {
   CHECK1(0, "here %s %s %s", "are", "some", "varargs1(1)\n");
   CHECK1(1, "here %s %s %s", "are", "some", "varargs1(2)\n");   // won't print

   CHECK2(0, "here %s %s %s", "are", "some", "varargs2(3)\n");   // won't print
   CHECK2(1, "here %s %s %s", "are", "some", "varargs2(4)\n");

   // always invokes printf in the macro
   CHECK3("here %s %s %s", "are", "some", "varargs3(5)\n");

   MACRO("hello, world\n");
   // MACRO("error\n", EMPTY);   would cause C2059
   system("PAUSE");
}