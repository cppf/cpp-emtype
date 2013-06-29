/*
----------------------------------------------------------------------------------------
	embd: Embedded Application development library for AVR processors (C/C++)
	File: embd.h

	This file is part of embd. For more details, go through
	Readme.txt. For copyright information, go through copyright.txt.

	embd is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	embd is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with embd.  If not, see <http://www.gnu.org/licenses/>.
----------------------------------------------------------------------------------------
*/



/*
	embd is an embedded application development library for AVR processors. It has been developed for
	for being used in the development of the internet of things for AVR processors. To use it, modify
	the appropriate definitions in this header file. This header should already include all te requisite
	header files (including those which are which are part of this library). For any information, please
	visit: https://github.com/wolfram77/embd.
*/



#ifndef	_embd_h_
#define	_embd_h_



// Platform:
// 
// Select the platform under use, here (which is always AVR)
// 
// For PC:		Set emdb_Platform to embd_PlatformPC
// For AVR:		Set embd_Platform to embd_PlatformAVR
//
#define	emdb_PlatformPC			0
#define	embd_PlatformAVR		1
#define	emdb_Platform			embd_PlatformPC



// Requisite headers
#if emdb_Platform == emdb_PlatformAVR
#include <Arduino.h>
#endif



// Library shorthand options
// 
// 0 -	No shorthanding
//		All functions and variables can only be accessed as <lib_name>_<function_name>
//		e.g- "emType" library's "GetInt" function can be accessed as "emType_GetInt"
// 
// 1 -	Level 1 shorthanding
//		All functions and variables can also be accessed as <lib_shortname>_<function_name>
//		e.g- "emType" library's "GetInt" function can be accessed as "type_GetInt"
// 
// 2 -	Level 2 shorthanding
//		All functions and variables can also be accessed as <3_char_lib_name><function_name>
//		e.g- "emType" library's "GetInt" function can be accessed as "typGetInt"
// 
// 3 -	Level 3 shorthanding
//		All functions and variables can also be accessed as <function_name> (only emType allows this)
//		e.g- "emType" library's "GetInt" function can be accessed as "GetInt"
#define	emType_Shorthand		3
#define	emList_Shorthand		2
#define	emTask_Shorthand		2
#define	emStream_Shorthand		2



// Include Library headers
#include "emdb/emType.h"



#endif
