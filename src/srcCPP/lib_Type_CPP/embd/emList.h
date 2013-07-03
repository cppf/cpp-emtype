/*
----------------------------------------------------------------------------------------
	emList: Static key-value pair storage library for emdb library (C/C++)
	File: emList.h

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
	emList is a static key-value pair storage library for emdb library. It has been developed for
	for being used in the development of the internet of things for AVR processors. For information,
	on its usage, please visit: https://github.com/wolfram77/embd.
*/



#ifndef	_emList_h_
#define	_emList_h_



// Requisite headers
#include "embd/emType.h"



// Select shorthand level
// 
// The default shorthand level is 2 i.e., members of this
// library can be accessed as lst<function_name>. The
// shorthand level can be selected in the main header
// file of embd library
#ifndef	emList_Shorthand
#define	emList_Shorthand	2
#endif



// List Mold Making
// 
// List molds (structures) can be created with desired sizes and datatypes. The MoldMake() can be used to
// create such molds. The molds can then be used to create objects as <name>Mold<size> <object>;
// 
#if	emList_Shorthand == 0
#define	emList_MoldMake(name, key, value, size)	\
typedef struct _emList_##name##Mold##size	\
{	\
	byte	Count;	\
	byte	Max;	\
	byte	KeyLen;	\
	byte	ValueLen;	\
	key		Key[size];	\
	value	Value[size];	\
}emList_##name##Mold##size
#elif	emList_Shorthand == 1
#define	emList_MoldMake(name, key, value, size)	\
typedef struct _emList_##name##Mold##size	\
{	\
	byte	Count;	\
	byte	Max;	\
	byte	KeyLen;	\
	byte	ValueLen;	\
	key		Key[size];	\
	value	Value[size];	\
}emList_##name##Mold##size, list_##name##Mold##size
#elif	emList_Shorthand == 2
#define	emList_MoldMake(name, key, value, size)	\
typedef struct _emList_##name##Mold##size	\
{	\
	byte	Count;	\
	byte	Max;	\
	byte	KeyLen;	\
	byte	ValueLen;	\
	int16	ValueOff;	\
	key		Key[size];	\
	value	Value[size];	\
}emList_##name##Mold##size, list_##name##Mold##size, lst##name##Mold##size
#endif

#if emList_Shorthand >= 1
#define	list_MoldMake			emList_MoldMake
#endif

#if	emList_Shorthand >= 2
#define	lstMoldMake				emList_MoldMake
#endif

emList_MoldMake(ByteByte, byte, byte, 256);

#define	emList_ByteByteMold		emList_ByteByteMold256

#if emList_Shorthand >= 1
#define	list_ByteByteMold256	emList_ByteByteMold256
#define	list_ByteByteMold		emList_ByteByteMold
#endif

#if	emList_Shorthand >= 2
#define	lstByteByteMold256		emList_ByteByteMold256
#define	lstByteByteMold			emList_ByteByteMold
#endif



// Function:
// Init(*list, size)
// 
// Initializes a list before use. The size of list (size) is required
// to be specified so that the list can be initialized according to its
// size. When using list variable, just use Init(&list, size).
// 
// Parameters:
// list:	the list to initialize (must be direct pointer to list)
// size:	size of the list to be initialized
// 
// Returns:
// nothing
//
#define	emList_InitLst(list, size)	\
	do{	\
		(*(list)).Count = 0;	\
		(*(list)).Max = (size) - 1;	\
		(*(list)).KeyLen = sizeof((*(list)).Key[0]);	\
		(*(list)).ValueLen = sizeof((*(list)).Value[0]);	\
		(*(list)).ValueOff = (size) * sizeof((*(list)).Key[0]);	\
	}while(0)

#if emList_Shorthand >= 1
#define	list_Init				emList_Init
#endif

#if	emList_Shorthand >= 2
#define	lstInit					emList_Init
#endif



// Function:
// Clear(*list)
// 
// Clears a list of all data. When using list variable, just use
// Clear(&list).
// 
// Parameters:
// list:	the list to clear
// 
// Returns:
// nothing
//
#define	emList_ClearLst(list)	\
		((*(list)).Count = 0)

#define	emList_Clear(list)	\
	emList_ClearLst((emList_ByteByteMold*)list)

#if emList_Shorthand >= 1
#define	list_Clear				emList_Clear
#endif

#if	emList_Shorthand >= 2
#define	lstClear				emList_Clear
#endif



// Function:
// GetAvail(*list)
// 
// Gives the number of pairs available in a list. When using
// list variable, just use GetAvail(&list).
// 
// Parameters:
// list:	the list whose available pairs are to be known
// 
// Returns:
// pairs_avail:	number of available pairs in list
//
#define	emList_GetAvailLst(list)	\
	((*(list)).Count)

#define	emList_GetAvail(list)	\
	emList_GetAvail((emList_ByteByteMold*)list)

#if emList_Shorthand >= 1
#define	list_GetAvail			emList_GetAvail
#endif

#if	emList_Shorthand >= 2
#define	lstGetAvail				emList_GetAvail
#endif



// Function:
// GetFree(*list)
// 
// Gives the number of free cells (space to store a pair) available in a list.
// When using list variable, just use GetFree(&list).
// 
// Parameters:
// list:	the list whose number of free cells are to be known
// 
// Returns:
// cells_free:	number of free cells in list
//
#define	emList_GetFreeLst(list)	\
	(1 + (*(list)).Max - (*(list)).Count)

#define	emList_GetFree(list)	\
	emList_GetFreeLst((emList_ByteByteMold*)list)

#if emList_Shorthand >= 1
#define	list_GetFree			emList_GetFree
#endif

#if	emList_Shorthand >= 2
#define	lstGetFree				emList_GetFree
#endif



// Function:
// GetIndexFrom<Key/Value>(*list, *<key/value>)
// 
// Get the index of a <key/value> from the list.
// 
// Parameters:
// list:	the list from which index of <key/value> is required
// <key/value>:	the <key/value>, whose index in the list is required
// 
// Returns: (nothing if index is provided as parameter)
// index:	index of <key/value> (0xFF for not found)
//
byte emList_GetIndexFromElemFn(void* list, void* list_elements, byte elem_size, void* element)
{
	byte index = 0xFF;
	byte *elems = (byte*)list_elements, *elem = (byte*)element;
	byte i, j, mtch, count = ((emList_ByteByteMold256*)list)->Count;
	for(i=0; i<count; i++)
	{
		mtch = 0;
		for(j=0; j<elem_size; j++, elems++)
		{
			if(elem[j] == *elems) mtch++;
		}
		if(mtch == elem_size) {index = i; break;}
	}
	return index;
}

#define	emList_GetIndexFromKeyLst(list, key)	\
	emList_GetIndexFromElemFn(list, (*(list)).Key, (*(list)).KeyLen, key)

#define	emList_GetIndexFromKey(list, key)	\
	emList_GetIndexFromKeyLst((emList_ByteByteMold*)list, key)

#define	emList_GetIndexFromValueLst(list, value)	\
	emList_GetIndexFromElemFn(list, (*(list)).Value, (*(list)).ValueLen, value)

#define	emList_GetIndexFromValue(list, value)	\
	emList_GetIndexFromValueLst((emList_ByteByteMold*)list, key)

#if emList_Shorthand >= 1
#define	list_GetIndexFromKey	emList_GetIndexFromKey
#define	list_GetIndexFromValue	emList_GetIndexFromValue
#endif

#if	emList_Shorthand >= 2
#define	lstGetIndexFromKey		emList_GetIndexFromKey
#define	lstGetIndexFromValue	emList_GetIndexFromValue
#endif



// Function:
// Add(*list, *key, *value)
// 
// Add a key-value pair to the list. If another key-value pair exists with
// the same key, then it will be overwritten. If sufficient space is not
// available, then the key-value pair will not be added.
// 
// Parameters:
// list:	the list to the key-value pair is to be added
// key:		the key to be added (expected to be unique)
// value:	the value to be added to list along with key
// 
// Returns:
// status:	0 for success, 0xFF for full
//
byte emList_Add(void* list, void* key, void* value)
{
	byte *ukey, *uval, *dst, i, indx;
	emList_ByteByteMold256* lst = (emList_ByteByteMold256*)list;
	if((*lst).Count > (*lst).Max) return 0xFF;	// list is full
	ukey = (byte*)key;
	uval = (byte*)value;
	indx = emList_GetIndexFromKey(lst, key);
	if(indx == 0xFF) {indx = (*(lst)).Count; (*(lst)).Count++; }
	dst = (byte*)((*lst).Key) + ((*lst).KeyLen * indx);
	for(i=0; i<(*lst).KeyLen; i++)
		dst[i] = ukey[i];
	dst = (byte*)((*lst).Key) + ((*lst).ValueOff) + ((*lst).ValueLen * indx);
	for(i=0; i<(*lst).ValueLen; i++)
		dst[i] = uval[i];
	return 0;
}

#if emList_Shorthand >= 1
#define	list_Add				emList_Add
#endif

#if	emList_Shorthand >= 2
#define	lstAdd					emList_Add
#endif



// Function:
// RemoveAt(*list, index)
// 
// Removes a key-value pair at specified index of list (index). If specified
// index is empty the removal cannot be done (status will be -1)
// 
// Parameters:
// list:	the list from which a key-value pair is to be removed
// index:	index of the key-value pair to be removed
// 
// Returns:
// status:	0 for success, 0xFF for empty
//
byte emList_RemoveAtFn(void* list, void* list_keys, void* list_values, byte key_size, byte value_size, byte index)
{
	emList_ByteByteMold256* lst = (emList_ByteByteMold256*)list;
	if(index >= (lst->Count)) return 0xFF;	// empty
	byte *keys = (byte*)list_keys, *values = (byte*)list_values;
	byte *src, *dst;
	int i, len;
	dst = keys + (key_size * index);
	src = dst + key_size;
	len = (lst->Count - index - 1) * key_size;
	for(i=0; i<len; i++)
		dst[i] = src[i];
	dst = values + (value_size * index);
	src = dst + value_size;
	len = (lst->Count - index - 1) * value_size;
	for(i=0; i<len; i++)
		dst[i] = src[i];
	lst->Count--;
	return 0;
}

#define	emList_RemoveAt(list, index)	\
	emList_RemoveAtFn(list, (*(list)).Key, (*(list)).Value, sizeof((*(list)).Key[0]), sizeof((*(list)).Value[0]), index)

#if emList_Shorthand >= 1
#define	list_RemoveAt			emList_RemoveAt
#endif

#if	emList_Shorthand >= 2
#define	lstRemoveAt				emList_RemoveAt
#endif



// Function:
// Remove(*list, *key)
// 
// Removes a key-value pair having specified key (key). If specified
// key is not present the removal cannot be done (status will be -1)
// 
// Parameters:
// list:	the list from which a key-value pair is to be removed
// key:		key of the key-value pair to be removed
// 
// Returns:
// status:	0 for success, 0xFF for unavailable
//
byte emList_RemoveFn(void* list, void* list_keys, void* list_values, byte key_size, byte value_size, void* key)
{
	byte index = emList_GetIndexFromElemFn(list, list_keys, key_size, key);
	if(index == 0xFF) return 0xFF;
	return emList_RemoveAtFn(list, list_keys, list_values, key_size, value_size, index);
}

#define	emList_Remove(list, key)	\
	emList_RemoveFn(list, (*(list)).Key, (*(list)).Value, sizeof((*(list)).Key[0]), sizeof((*(list)).Value[0]), key)

#if emList_Shorthand >= 1
#define	list_Remove				emList_Remove
#endif

#if	emList_Shorthand >= 2
#define	lstRemove				emList_Remove
#endif



#endif
