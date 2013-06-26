/*
----------------------------------------------------------------------------------------
	emType: Library header file for Arduino
	File: emType.h

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



/*
	emType is a generic type conversion library for Arduino/Waspmote/Processing/C/C++. It has been
	developed mainly for simplifying the process of writing wireless communication programs on Arduino,
	Waspmote and Processing. To use it (in Arduino), copy the file emType.h to your sketch directory and
	include it (emType.h) in the main code.
*/



#ifndef	_emType_h_
#define	_emType_h_



// Requisite headers
#include <Arduino.h>



// Simulate macro overloading
// By default, C++ does not support macro overloading, but
// through the use of variable argument macros called variadic
// macros, it is possible to support macro overloading to some
// extent
#ifndef	Macro
#define	Macro(x)	(x)
#define	Macro2(_1, _2, func, ...)	func
#define	Macro3(_1, _2, _3, func, ...)	func
#define	Macro4(_1, _2, _3, _4, func, ...)	func
#define	Macro5(_1, _2, _3, _4, _5, func, ...)	func
#define	Macro6(_1, _2, _3, _4, _5, _6, func, ...)	func
#define	Macro7(_1, _2, _3, _4, _5, _6, _7, func, ...)	func
#define	Macro8(_1, _2, _3, _4, _5, _6, _7, _8, func, ...)	func
#endif



// shorthand constants
#ifndef null
#define null ((void*)0)
#endif
#ifndef TRUE
#define TRUE	1
#define	FALSE	0
#endif



// shorthand datatypes
typedef unsigned char		byte;
typedef signed char			sbyte;
typedef unsigned short		ushort;
typedef int					int16;
typedef unsigned int		uint16;
typedef unsigned int		uint;
typedef long				long32;
typedef unsigned long		ulong32;
typedef unsigned long		ulong;
typedef char*				string;
typedef long long			long64;
typedef unsigned long long	ulong64;



// internal buffer format
typedef union _emType_Mold
{
	byte	Byte[16];
	sbyte	Sbyte[16];
	char	Char[16];
	short	Short[8];
	ushort	Ushort[8];
	int16	Int16[8];
	uint16	Uint16[8];
	int		Int[8];
	uint	Uint[8];
	long32	Long32[4];
	ulong32	Ulong32[4];
	long	Long[4];
	ulong	Ulong[4];
	long64	Long64[2];
	ulong64	Ulong64[2];
	float	Float[4];
	double	Double[2];
}emType_Mold;

#if emType_Shorthand >= 1
#define	emTypeMold				emType_Mold
#endif

#if	emType_Shorthand >= 2
#define	typMold					emType_Mold
#endif



// internal buffer
emType_Mold	emType;



// Function:
// GetBit(src, off, bit_no)
// GetBit(off, bit_no)
// 
// Returns the value of bit at the specified bit number (bit_no)
// from the specified source address with offset (src + off). If
// source address (src) is not specified, then this library's
// internal buffer is used as the source.
// 
// Parameters:
// src:		the base address of stored data
// off:		offset from which bit index starts
// bit_no:	the index of the bit (starts from 0)
// 
// Returns:
// bit_value:	the value of the specified bit (0 or 1)
// 
#define	emType_GetBitExt(src, off, bit_no)	\
	((*(((byte*)src) + off + (bit_no >> 3)) >> (bit_no & 7)) & 1)

#define	emType_GetBitInt(off, bit_no)	\
	emType_GetBitExt(&emType, off, bit_no)

#define emType_GetBit(...)	\
	Macro(Macro3(__VA_ARGS__, emType_GetBitExt, emType_GetBitInt)(__VA_ARGS__))

#define	emType_GetRegBit(src, bit_no)	\
	((src >> bit_no) & 1)

#if emType_Shorthand >= 1
#define	emTypeGetBit			emType_GetBit
#define	emTypeGetRegBit			emType_GetRegBit
#endif

#if	emType_Shorthand >= 2
#define	typGetBit				emType_GetBit
#define	typGetRegBit			emType_GetRegBit
#endif

#if	emType_Shorthand >= 3
#define	GetBit					emType_GetBit
#define	GetRegBit				emType_GetRegBit
#endif

	

// Function:
// GetNibble(src, off, nibble_no)
// GetNibble(off, nibble_no)
// 
// Returns the value of nibble at the specified nibble number (nibble_no)
// from the specified source address with offset (src + off). If source
// address (src) is not specified, then this library's internal buffer
// is used as the source.
// 
// Parameters:
// src:			the base address of stored data
// off:			offset from which nibble index starts
// nibble_no:	the index of the nibble (starts from 0)
// 
// Returns:
// nibble_value:	the value of the specified nibble (0 to 15 or 0x0 to 0xF)
// 
#define	emType_GetNibbleExt(src, off, nibble_no)	\
	((*(((byte*)src) + off + (nibble_no >> 1)) >> ((nibble_no & 1) << 2)) & 0xF)

#define	emType_GetNibbleInt(off, nibble_no)	\
	emType_GetNibbleExt(&emType, off, nibble_no)

#define emType_GetNibble(...)	\
	Macro(Macro3(__VA_ARGS__, emType_GetNibbleExt, emType_GetNibbleInt)(__VA_ARGS__))

#if emType_Shorthand >= 1
#define	emTypeGetNibble			emType_GetNibble
#endif

#if	emType_Shorthand >= 2
#define	typGetNibble			emType_GetNibble
#endif

#if	emType_Shorthand >= 3
#define	GetNibble				emType_GetNibble
#endif



// Function:
// Get<type>(src, off)
// Get<type>(off)
// 
// Returns the <type> value at the specified source address with 
// offset (src + off). If source address (src) is not specified,
// then this library's internal buffer is used as the source.
// 
// Parameters:
// src:			the base address of stored data
// off:			offset of the <type> value
// 
// Returns:
// <type>_value:	the value of the specified <type>
// 
#define	emType_GetStypeExt(type, src, off)	\
	(*(((type*)src) + off))

#define	emType_GetStypeInt(type, off)	\
	emType_GetStypeExt(type, &emType, off)

#define emType_GetStype(...)	\
	Macro(Macro3(__VA_ARGS__, emType_GetStypeExt, emType_GetStypeInt)(__VA_ARGS__))

#define	emType_GetTypeExt(type, src, off)	\
	(*((type*)(((byte*)src) + off)))

#define	emType_GetTypeInt(type, off)	\
	emType_GetTypeExt(type, &emType, off)

#define	emType_GetType(...) \
	Macro(Macro3(__VA_ARGS__, emType_GetTypeExt, emType_GetTypeInt)(__VA_ARGS__))

#define emType_GetChar(...)	\
	Macro(emType_GetStype(char, __VA_ARGS__))

#define emType_GetByte(...)	\
	Macro(emType_GetStype(byte, __VA_ARGS__))

#define emType_GetBoolean(...)	\
	Macro(((emType_GetByte(__VA_ARGS__) == 0)? FALSE : TRUE))

#define	emType_GetShort(...)	\
	Macro(emType_GetType(short, __VA_ARGS__))

#define	emType_GetUshort(...)	\
	Macro(emType_GetType(ushort, __VA_ARGS__))

#define	emType_GetInt16(...)	\
	Macro(emType_GetType(int16, __VA_ARGS__))

#define	emType_GetUint16(...)	\
	Macro(emType_GetType(uint16, __VA_ARGS__))

#define	emType_GetInt(...)	\
	Macro(emType_GetType(int, __VA_ARGS__))

#define	emType_GetUint(...)	\
	Macro(emType_GetType(uint, __VA_ARGS__))

#define	emType_GetLong32(...)	\
	Macro(emType_GetType(long32, __VA_ARGS__))

#define	emType_GetUlong32(...)	\
	Macro(emType_GetType(ulong32, __VA_ARGS__))

#define	emType_GetLong(...)	\
	Macro(emType_GetType(long, __VA_ARGS__))

#define	emType_GetUlong(...)	\
	Macro(emType_GetType(ulong, __VA_ARGS__))

#define	emType_GetLong64(...)	\
	Macro(emType_GetType(long64, __VA_ARGS__))

#define	emType_GetUlong64(...)	\
	Macro(emType_GetType(ulong64, __VA_ARGS__))

#define	emType_GetFloat(...)	\
	Macro(emType_GetType(float, __VA_ARGS__))

#define	emType_GetDouble(...)	\
	Macro(emType_GetType(double, __VA_ARGS__))

#if emType_Shorthand >= 1
#define	emTypeGetChar			emType_GetChar
#define	emTypeGetByte			emType_GetByte
#define	emTypeGetBoolean		emType_GetBoolean
#define	emTypeGetShort			emType_GetShort
#define	emTypeGetUshort			emType_GetUshort
#define	emTypeGetInt16			emType_GetInt16
#define	emTypeGetUint16			emType_GetUint16
#define	emTypeGetInt			emType_GetInt
#define	emTypeGetUint			emType_GetUint
#define	emTypeGetLong32			emType_GetLong32
#define	emTypeGetUlong32		emType_GetUlong32
#define	emTypeGetLong			emType_GetLong
#define	emTypeGetUlong			emType_GetUlong
#define	emTypeGetLong64			emType_GetLong64
#define	emTypeGetUlong64		emType_GetUlong64
#define	emTypeGetFloat			emType_GetFloat
#define	emTypeGetDouble			emType_GetDouble
#endif

#if	emType_Shorthand >= 2
#define	typGetChar				emType_GetChar
#define	typGetByte				emType_GetByte
#define	typGetBoolean			emType_GetBoolean
#define	typGetShort				emType_GetShort
#define	typGetUshort			emType_GetUshort
#define	typGetInt16				emType_GetInt16
#define	typGetUint16			emType_GetUint16
#define	typGetInt				emType_GetInt
#define	typGetUint				emType_GetUint
#define	typGetLong32			emType_GetLong32
#define	typGetUlong32			emType_GetUlong32
#define	typGetLong				emType_GetLong
#define	typGetUlong				emType_GetUlong
#define	typGetLong64			emType_GetLong64
#define	typGetUlong64			emType_GetUlong64
#define	typGetFloat				emType_GetFloat
#define	typGetDouble			emType_GetDouble
#endif

#if	emType_Shorthand >= 3
#define	GetChar					emType_GetChar
#define	GetByte					emType_GetByte
#define	GetBoolean				emType_GetBoolean
#define	GetShort				emType_GetShort
#define	GetUshort				emType_GetUshort
#define	GetInt16				emType_GetInt16
#define	GetUint16				emType_GetUint16
#define	GetInt					emType_GetInt
#define	GetUint					emType_GetUint
#define	GetLong32				emType_GetLong32
#define	GetUlong32				emType_GetUlong32
#define	GetLong					emType_GetLong
#define	GetUlong				emType_GetUlong
#define	GetLong64				emType_GetLong64
#define	GetUlong64				emType_GetUlong64
#define	GetFloat				emType_GetFloat
#define	GetDouble				emType_GetDouble
#endif



// Function:
// GetString(dst, sz, src, off, opt)
// GetString(dst, sz, off, opt)
// 
// Returns the string from the specified source address with 
// offset (src + off). If source address (src) is not specified,
// then this library's internal buffer is used as the source.
// 
// Parameters:
// dst:      destination buffer for string (it will be fetched here)
// sz:       size of destination in bytes (max. length of string-1)
// src:      the base address of stored string (which will be fetched)
// off:      offset of the stored string
// opt:      options for string fetching (TYPE_ZEROED_STRING, TYPE_LENGTH_STRING)
// 
// Returns:
// string_value:  the fetched string
// 
#define	emType_ZEROED_STRING		0

#define	emType_LENGTH_STRING		1

string emType_GetStringExt(string dst, int sz, void* src, int off, byte opt)
{
	int len;
	char* xsrc = ((char*)src) + off;
	if(opt & emType_LENGTH_STRING) len = *xsrc;
	else len = strlen(xsrc);
	len = ((sz - 1) < len)? (sz - 1) : len;
	memcpy(dst, xsrc+1, len);
	dst[len] = '\0';
	return dst;
}

#define	emType_GetStringInt(dst, sz, off, opt)	\
	emType_GetStringExt(dst, sz, &emType, off, opt)

#define emType_GetString(...)	\
	Macro(Macro5(__VA_ARGS__, emType_GetStringExt, emType_GetStringInt)(__VA_ARGS__))

#if emType_Shorthand >= 1
#define	emTypeZEROED_STRING		emType_ZEROED_STRING
#define	emTypeLENGTH_STRING		emType_LENGTH_STRING
#define	emTypeGetString			emType_GetString
#endif

#if	emType_Shorthand >= 2
#define	typZEROED_STRING		emType_ZEROED_STRING
#define	typLENGTH_STRING		emType_LENGTH_STRING
#define	typGetString			emType_GetString
#endif

#if	emType_Shorthand >= 3
#define	ZEROED_STRING			emType_ZEROED_STRING
#define	LENGTH_STRING			emType_LENGTH_STRING
#define	GetString				emType_GetString
#endif



// Function:
// PutBit(dst, off, bit_no, bit_value)
// PutBit(off, bit_no, bit_value)
// 
// Stores the value of bit at the specified bit number (bit_no)
// to the specified destination address with offset (dst + off).
// If destination address (dst) is not specified, then this
// library's internal buffer is used as the destination.
// 
// Parameters:
// dst:		the base address of destination
// off:		offset from which bit index starts
// bit_no:	the index of the bit (starts from 0)
// bit_value:	the value of the specified bit (0 or 1)
// 
// Returns:
// nothing
// 
#define	emType_PutBitExt(dst, off, bit_no, bit_value)	\
	((bit_value == 0)?(*(((byte*)dst) + off + (bit_no >> 3)) &= ~(1 << ((byte)bit_no & (byte)7))) : (*(((byte*)dst) + off + (bit_no >> 3)) |= (1 << ((byte)bit_no & (byte)7))))

#define	emType_PutBitInt(off, bit_no, bit_value)	\
	emType_PutBitExt(&emType, off, bit_no, bit_value)

#define emType_PutBit(...)	\
	Macro(Macro4(__VA_ARGS__, emType_PutBitExt, emType_PutBitInt)(__VA_ARGS__))

#define	emType_SetRegBit1(dst, bit_no)	\
	(dst |= (1 << bit_no))

#define	emType_SetRegBit2(dst, bit_no1, bit_no0)	\
	(dst |= (1 << bit_no1) | (1 << bit_no0))

#define	emType_SetRegBit3(dst, bit_no2, bit_no1, bit_no0)	\
	(dst |= (1 << bit_no2) | (1 << bit_no1) | (1 << bit_no0))

#define	emType_SetRegBit4(dst, bit_no3, bit_no2, bit_no1, bit_no0)	\
	(dst |= (1 << bit_no3) | (1 << bit_no2) | (1 << bit_no1) | (1 << bit_no0))

#define	emType_SetRegBit5(dst, bit_no4, bit_no3, bit_no2, bit_no1, bit_no0)	\
	(dst |= (1 << bit_no4) | (1 << bit_no3) | (1 << bit_no2) | (1 << bit_no1) | (1 << bit_no0))

#define	emType_SetRegBit6(dst, bit_no5, bit_no4, bit_no3, bit_no2, bit_no1, bit_no0)	\
	(dst |= (1 << bit_no5) | (1 << bit_no4) | (1 << bit_no3) | (1 << bit_no2) | (1 << bit_no1) | (1 << bit_no0))

#define	emType_SetRegBit7(dst, bit_no6, bit_no5, bit_no4, bit_no3, bit_no2, bit_no1, bit_no0)	\
	(dst |= (1 << bit_no6) | (1 << bit_no5) | (1 << bit_no4) | (1 << bit_no3) | (1 << bit_no2) | (1 << bit_no1) | (1 << bit_no0))

#define	emType_SetRegBit(...)	\
	Macro(Macro8(__VA_ARGS__, emType_SetRegBit7, emType_SetRegBit6, emType_SetRegBit5, emType_SetRegBit4, emType_SetRegBit3, emType_SetRegBit2, emType_SetRegBit1)(__VA_ARGS__))

#define	emType_ClearRegBit1(dst, bit_no)	\
	(dst &= ~(1 << bit_no))

#define	emType_ClearRegBit2(dst, bit_no1, bit_no0)	\
	(dst &= ~(1 << bit_no1) | (1 << bit_no0))

#define	emType_ClearRegBit3(dst, bit_no2, bit_no1, bit_no0)	\
	(dst &= ~(1 << bit_no2) | (1 << bit_no1) | (1 << bit_no0))

#define	emType_ClearRegBit4(dst, bit_no3, bit_no2, bit_no1, bit_no0)	\
	(dst &= ~(1 << bit_no3) | (1 << bit_no2) | (1 << bit_no1) | (1 << bit_no0))

#define	emType_ClearRegBit5(dst, bit_no4, bit_no3, bit_no2, bit_no1, bit_no0)	\
	(dst &= ~(1 << bit_no4) | (1 << bit_no3) | (1 << bit_no2) | (1 << bit_no1) | (1 << bit_no0))

#define	emType_ClearRegBit6(dst, bit_no5, bit_no4, bit_no3, bit_no2, bit_no1, bit_no0)	\
	(dst &= ~(1 << bit_no5) | (1 << bit_no4) | (1 << bit_no3) | (1 << bit_no2) | (1 << bit_no1) | (1 << bit_no0))

#define	emType_ClearRegBit7(dst, bit_no6, bit_no5, bit_no4, bit_no3, bit_no2, bit_no1, bit_no0)	\
	(dst &= ~(1 << bit_no6) | (1 << bit_no5) | (1 << bit_no4) | (1 << bit_no3) | (1 << bit_no2) | (1 << bit_no1) | (1 << bit_no0))

#define	emType_ClearRegBit(...)	\
	Macro(Macro8(__VA_ARGS__, emType_ClearRegBit7, emType_ClearRegBit6, emType_ClearRegBit5, emType_ClearRegBit4, emType_ClearRegBit3, emType_ClearRegBit2, emType_ClearRegBit1)(__VA_ARGS__))

#define	emType_PutRegBit(dst, bit_no, bit_value)	\
	((dst &= ~(1 << bit_no)) |= (bit_value << bit_no))

#if emType_Shorthand >= 1
#define	emTypePutBit			emType_PutBit
#define	emTypeSetRegBit			emType_SetRegBit
#define	emTypeClearRegBit		emType_ClearRegBit
#define	emTypePutRegBit			emType_PutRegBit
#endif

#if	emType_Shorthand >= 2
#define	typPutBit				emType_PutBit
#define	typSetRegBit			emType_SetRegBit
#define	typClearRegBit			emType_ClearRegBit
#define	typPutRegBit			emType_PutRegBit
#endif

#if	emType_Shorthand >= 3
#define	PutBit					emType_PutBit
#define	SetRegBit				emType_SetRegBit
#define	ClearRegBit				emType_ClearRegBit
#define	PutRegBit				emType_PutRegBit
#endif



// Function:
// PutNibble(dst, off, nibble_no, nibble_value)
// PutNibble(off, nibble_no, nibble_value)
// 
// Stores the value of nibble at the specified nibble number
// (nibble_no) to the specified destination address with
// offset (dst + off). If destination address (dst) is not
// specified, then this library's internal buffer is used
// as the destination.
// 
// Parameters:
// dst:		the base address of destination
// off:		offset from which nibble index starts
// nibble_no:	the index of the nibble (starts from 0)
// nibble_value:	the value of the specified nibble (0 to 15 or 0x0 to 0xF)
// 
// Returns:
// nothing
// 
#define	emType_PutNibbleExt(dst, off, nibble_no, nibble_value)	\
	(*(((byte*)dst) + off + (nibble_no >> 1)) = (*(((byte*)dst) + off + (nibble_no >> 1)) & (~(0xF << ((nibble_no & 1) << 2)))) | (nibble_value << ((nibble_no & 1) << 2)))

#define	emType_PutNibbleInt(off, nibble_no, nibble_value)	\
	emType_PutNibbleExt(&emType, off, nibble_no, nibble_value)

#define emType_PutNibble(...)	\
	Macro(Macro4(__VA_ARGS__, emType_PutNibbleExt, emType_PutNibbleInt)(__VA_ARGS__))

#if emType_Shorthand >= 1
#define	emTypePutNibble			emType_PutNibble
#endif

#if	emType_Shorthand >= 2
#define	typPutNibble			emType_PutNibble
#endif

#if	emType_Shorthand >= 3
#define	PutNibble				emType_PutNibble
#endif



// Function:
// Put<type>(dst, off, value)
// Put<type>(off, value)
// 
// Stores the value of <type> at the specified destination
// address with offset (dst + off). If destination address
// (dst) is not specified, then this library's internal
// buffer is used as the destination.
// 
// Parameters:
// dst:		the base address of destination
// off:		offset where <type> value is stored
// value:	the value of <type> to be stored
// 
// Returns:
// nothing
// 
#define	emType_PutStypeExt(type, dst, off, value)	\
	(*(((type*)dst) + off) = value)

#define	emType_PutStypeInt(type, off, value)	\
	emType_PutStypeExt(type, &emType, off, value)

#define emType_PutStype(...)	\
	Macro(Macro4(__VA_ARGS__, emType_PutStypeExt, emType_PutStypeInt)(__VA_ARGS__))

#define	emType_PutTypeExt(type, dst, off, value)	\
	(*((type*)(((byte*)dst) + off)) = value)

#define	emType_PutTypeInt(type, off, value)	\
	emType_PutTypeExt(type, &emType, off, value)

#define	emType_PutType(...) \
	Macro(Macro4(__VA_ARGS__, emType_PutTypeExt, emType_PutTypeInt)(__VA_ARGS__))

#define emType_PutChar(...)	\
	Macro(emType_PutStype(char, __VA_ARGS__))

#define emType_PutByte(...)	\
	Macro(emType_PutStype(byte, __VA_ARGS__))

#define emType_PutBoolean(...)	\
	Macro(((emType_PutByte(__VA_ARGS__) == 0)? FALSE : TRUE))

#define	emType_PutShort(...)	\
	Macro(emType_PutType(short, __VA_ARGS__))

#define	emType_PutUshort(...)	\
	Macro(emType_PutType(ushort, __VA_ARGS__))

#define	emType_PutInt16(...)	\
	Macro(emType_PutType(int16, __VA_ARGS__))

#define	emType_PutUint16(...)	\
	Macro(emType_PutType(uint16, __VA_ARGS__))

#define	emType_PutInt(...)	\
	Macro(emType_PutType(int, __VA_ARGS__))

#define	emType_PutUint(...)	\
	Macro(emType_PutType(uint, __VA_ARGS__))

#define	emType_PutLong32(...)	\
	Macro(emType_PutType(long32, __VA_ARGS__))

#define	emType_PutUlong32(...)	\
	Macro(emType_PutType(ulong32, __VA_ARGS__))

#define	emType_PutLong(...)	\
	Macro(emType_PutType(long, __VA_ARGS__))

#define	emType_PutUlong(...)	\
	Macro(emType_PutType(ulong, __VA_ARGS__))

#define	emType_PutLong64(...)	\
	Macro(emType_PutType(long64, __VA_ARGS__))

#define	emType_PutUlong64(...)	\
	Macro(emType_PutType(ulong64, __VA_ARGS__))

#define	emType_PutFloat(...)	\
	Macro(emType_PutType(float, __VA_ARGS__))

#define	emType_PutDouble(...)	\
	Macro(emType_PutType(double, __VA_ARGS__))

#if emType_Shorthand >= 1
#define	emTypePutChar			emType_PutChar
#define	emTypePutByte			emType_PutByte
#define	emTypePutBoolean		emType_PutBoolean
#define	emTypePutShort			emType_PutShort
#define	emTypePutUshort			emType_PutUshort
#define	emTypePutInt16			emType_PutInt16
#define	emTypePutUint16			emType_PutUint16
#define	emTypePutInt			emType_PutInt
#define	emTypePutUint			emType_PutUint
#define	emTypePutLong32			emType_PutLong32
#define	emTypePutUlong32		emType_PutUlong32
#define	emTypePutLong			emType_PutLong
#define	emTypePutUlong			emType_PutUlong
#define	emTypePutLong64			emType_PutLong64
#define	emTypePutUlong64		emType_PutUlong64
#define	emTypePutFloat			emType_PutFloat
#define	emTypePutDouble			emType_PutDouble
#endif

#if	emType_Shorthand >= 2
#define	typPutChar				emType_PutChar
#define	typPutByte				emType_PutByte
#define	typPutBoolean			emType_PutBoolean
#define	typPutShort				emType_PutShort
#define	typPutUshort			emType_PutUshort
#define	typPutInt16				emType_PutInt16
#define	typPutUint16			emType_PutUint16
#define	typPutInt				emType_PutInt
#define	typPutUint				emType_PutUint
#define	typPutLong32			emType_PutLong32
#define	typPutUlong32			emType_PutUlong32
#define	typPutLong				emType_PutLong
#define	typPutUlong				emType_PutUlong
#define	typPutLong64			emType_PutLong64
#define	typPutUlong64			emType_PutUlong64
#define	typPutFloat				emType_PutFloat
#define	typPutDouble			emType_PutDouble
#endif

#if	emType_Shorthand >= 3
#define	PutChar					emType_PutChar
#define	PutByte					emType_PutByte
#define	PutBoolean				emType_PutBoolean
#define	PutShort				emType_PutShort
#define	PutUshort				emType_PutUshort
#define	PutInt16				emType_PutInt16
#define	PutUint16				emType_PutUint16
#define	PutInt					emType_PutInt
#define	PutUint					emType_PutUint
#define	PutLong32				emType_PutLong32
#define	PutUlong32				emType_PutUlong32
#define	PutLong					emType_PutLong
#define	PutUlong				emType_PutUlong
#define	PutLong64				emType_PutLong64
#define	PutUlong64				emType_PutUlong64
#define	PutFloat				emType_PutFloat
#define	PutDouble				emType_PutDouble
#endif



// Function:
// PutString(dst, off, value, opt)
// PutString(off, value, opt)
// 
// Stores the string at the specified destination address with 
// offset (dst + off). If destination address (dst) is not specified,
// then this library's internal buffer is used as the destination.
// 
// Parameters:
// dst:      destination base address where the string is to be stored
// off:      offset to destination from where the stored string will start
// value:    the string that is to be stored
// opt:      options for string writing (TYPE_ZEROED_STRING, TYPE_LENGTH_STRING)
// 
// Returns:
// nothing
// 
void emType_PutStringExt(void* dst, int off, string value, byte opt)
{
	char* xdst = ((char*)dst) + off;
	int len = strlen(value);
	if(opt & emType_LENGTH_STRING) {*xdst = (char)len; xdst++;}
	else len++;
	memcpy(xdst, value, len);
}

#define	emType_PutStringInt(off, value, opt)	\
	emType_PutStringExt(&emType, off, value, opt)

#define	emType_PutString(...)	\
	Macro(Macro4(__VA_ARGS__, emType_PutStringExt, emType_PutStringInt)(__VA_ARGS__))

#if emType_Shorthand >= 1
#define	emTypePutString			emType_PutString
#endif

#if	emType_Shorthand >= 2
#define	typPutString			emType_PutString
#endif

#if	emType_Shorthand >= 3
#define	PutString				emType_PutString
#endif



// Function:
// To<type>(smaller_data_types)
// 
// Assembles smaller data types to a bigger data type. The
// assembling is done in little endian format, which means
// that the smaller data representing the least significant
// part should come first, and the smaller data representing
// the most significant part should come last.
// 
// Parameters:
// smaller_data_types:	list of bytes, shorts, ints, etc.
// 
// Returns:
// <type>_value:	the value of the (bigger) assembled data type
// 
#define	emType_ToNibble(bit3, bit2, bit1, bit0)	\
	((bit3 << 3) | (bit2 << 2) | (bit1 << 1) | bit0)

#define emType_ToByteNib(nibble1, nibble0)	\
	((nibble1 << 4) | nibble0)

#define	emType_ToByteBit(bit7, bit6, bit5, bit4, bit3, bit2, bit1, bit0)	\
	emType_ToByteNib(emType_ToNibble(bit7, bit6, bit5, bit4), emType_ToNibble(bit3, bit2, bit1, bit0))

#define emType_ToByte(...)	\
	Macro(Macro8(__VA_ARGS__, emType_ToByteBit, _7, _6, _5, _4, _3, emType_ToByteNib)(__VA_ARGS__))

#define	emType_ToChar	\
	emType_ToByte	

#define	emType_ToType2(var, ret, rtype, dat1, dat0)	\
	(((emType.var[0] = dat0) & (emType.var[1] = dat1) & 0)? (rtype)0 : emType.ret[0])

#define	emType_ToType4(var, ret, rtype, dat3, dat2, dat1, dat0)	\
	(((emType.var[0] = dat0) & (emType.var[1] = dat1) & (emType.var[2] = dat2) & (emType.var[3] = dat3) & 0)? (rtype)0 : emType.ret[0])

#define emType_ToType8(var, ret, rtype, dat7, dat6, dat5, dat4, dat3, dat2, dat1, dat0)	\
	(((emType.var[0] = dat0) & (emType.var[1] = dat1) & (emType.var[2] = dat2) & (emType.var[3] = dat3) & (emType.var[4] = dat4) & (emType.var[5] = dat5) & (emType.var[6] = dat6) & (emType.var[7] = dat7) & 0)? (rtype)0 : emType.ret[0])

#define	emType_ToShort(byte1, byte0)	\
	emType_ToType2(Byte, Short, short, byte1, byte0)

#define	emType_ToUshort(byte0, byte1)	\
	emType_ToType2(Byte, Short, short, byte1, byte0)

#define	emType_ToInt16	\
	emType_ToShort

#define	emType_ToUint16	\
	emType_ToUshort

#define	emType_ToInt	\
	emType_ToShort

#define	emType_ToUint	\
	emType_ToUshort

#define	emType_ToLong32Srt(ushort1, ushort0)	\
	emType_ToType2(Ushort, Long32, long32, ushort1, ushort0)

#define	emType_ToLong32Byt(byte3, byte2, byte1, byte0)	\
	emType_ToType4(Byte, Long32, long32, byte3, byte2, byte1, byte0)

#define	emType_ToLong32(...)	\
	Macro(Macro4(__VA_ARGS__, emType_ToLong32Byt, _3, emType_ToLong32Srt)(__VA_ARGS__))

#define	emType_ToUlong32Srt(ushort1, ushort0)	\
	emType_ToType2(Ushort, Ulong32, ulong32, ushort1, ushort0)

#define	emType_ToUlong32Byt(byte3, byte2, byte1, byte0)	\
	emType_ToType4(Byte, Ulong32, ulong32, byte3, byte2, byte1, byte0)

#define	emType_ToUlong32(...)	\
	Macro(Macro4(__VA_ARGS__, emType_ToUlong32Byt, _3, emType_ToUlong32Srt)(__VA_ARGS__))

#define	emType_ToLong	\
	emType_ToLong32

#define	emType_ToUlong	\
	emType_ToUlong32

#define	emType_ToLong64Ulong32(ulong32_1, ulong32_0)	\
	emType_ToType2(Uint, Long64, long64, ulong32_1, ulong32_0)

#define	emType_ToLong64Srt(ushort3, ushort2, ushort1, ushort0)	\
	emType_ToType4(Ushort, Long64, long64, ushort3, ushort2, ushort1, ushort0)

#define	emType_ToLong64Byt(byte7, byte6, byte5, byte4, byte3, byte2, byte1, byte0)	\
	emType_ToType8(Byte, Long64, long64, byte7, byte6, byte5, byte4, byte3, byte2, byte1, byte0)

#define	emType_ToLong64(...)	\
	Macro(Macro8(__VA_ARGS__, emType_ToLong64Byt, _7, _6, _5, emType_ToLong64Srt, _3, emType_ToLong64Ulong32)(__VA_ARGS__))

#define	emType_ToUlong64Ulong32(ulong32_1, ulong32_0)	\
	emType_ToType2(Uint, Ulong64, ulong64, ulong32_1, ulong32_0)

#define	emType_ToUlong64Srt(ushort3, ushort2, ushort1, ushort0)	\
	emType_ToType4(Ushort, Ulong64, ulong64, ushort3, ushort2, ushort1, ushort0)

#define	emType_ToUlong64Byt(byte7, byte6, byte5, byte4, byte3, byte2, byte1, byte0)	\
	emType_ToType8(Byte, Ulong64, ulong64, byte7, byte6, byte5, byte4, byte3, byte2, byte1, byte0)

#define	emType_ToUlong64(...)	\
	Macro(Macro8(__VA_ARGS__, emType_ToUlong64Byt, _7, _6, _5, emType_ToUlong64Srt, _3, emType_ToUlong64Ulong32)(__VA_ARGS__))

#define	emType_ToFloatSrt(ushort1, ushort0)	\
	emType_ToType2(Ushort, Float, float, ushort1, ushort0)

#define	emType_ToFloatByt(byte3, byte2, byte1, byte0)	\
	emType_ToType4(Byte, Float, float, byte3, byte2, byte1, byte0)

#define	emType_ToFloat(...)	\
	Macro(Macro4(__VA_ARGS__, emType_ToFloatByt, _3, emType_ToFloatSrt)(__VA_ARGS__))

#define	emType_ToDoubleUlong32(ulong32_1, ulong32_0)	\
	emType_ToType2(Uint, Double, double, ulong32_1, ulong32_0)

#define	emType_ToDoubleSrt(ushort3, ushort2, ushort1, ushort0)	\
	emType_ToType4(Ushort, Double, double, ushort3, ushort2, ushort1, ushort0)

#define	emType_ToDoubleByt(byte7, byte6, byte5, byte4, byte3, byte2, byte1, byte0)	\
	emType_ToType8(Byte, Double, double, byte7, byte6, byte5, byte4, byte3, byte2, byte1, byte0)

#define	emType_ToDouble(...)	\
	Macro(Macro8(__VA_ARGS__, emType_ToDoubleByt, _7, _6, _5, emType_ToDoubleSrt, _3, emType_ToDoubleUlong32)(__VA_ARGS__))

#if emType_Shorthand >= 1
#define	emTypeToNibble			emType_ToNibble
#define	emTypeToByte			emType_ToByte
#define	emTypeToChar			emType_ToChar
#define	emTypeToShort			emType_ToShort
#define	emTypeToUshort			emType_ToUshort
#define	emTypeToInt16			emType_ToInt16
#define	emTypeToUint16			emType_ToUint16
#define	emTypeToInt				emType_ToInt
#define	emTypeToUint			emType_ToUint
#define	emTypeToLong32			emType_ToLong32
#define	emTypeToUlong32			emType_ToUlong32
#define	emTypeToLong			emType_ToLong
#define	emTypeToUlong			emType_ToUlong
#define	emTypeToLong64			emType_ToLong64
#define	emTypeToUlong64			emType_ToUlong64
#define	emTypeToFloat			emType_ToFloat
#define	emTypeToDouble			emType_ToDouble
#endif

#if	emType_Shorthand >= 2
#define	typToNibble				emType_ToNibble
#define	typToByte				emType_ToByte
#define	typToChar				emType_ToChar
#define	typToShort				emType_ToShort
#define	typToUshort				emType_ToUshort
#define	typToInt16				emType_ToInt16
#define	typToUint16				emType_ToUint16
#define	typToInt				emType_ToInt
#define	typToUint				emType_ToUint
#define	typToLong32				emType_ToLong32
#define	typToUlong32			emType_ToUlong32
#define	typToLong				emType_ToLong
#define	typToUlong				emType_ToUlong
#define	typToLong64				emType_ToLong64
#define	typToUlong64			emType_ToUlong64
#define	typToFloat				emType_ToFloat
#define	typToDouble				emType_ToDouble
#endif

#if	emType_Shorthand >= 3
#define	ToNibble				emType_ToNibble
#define	ToByte					emType_ToByte
#define	ToChar					emType_ToChar
#define	ToShort					emType_ToShort
#define	ToUshort				emType_ToUshort
#define	ToInt16					emType_ToInt16
#define	ToUint16				emType_ToUint16
#define	ToInt					emType_ToInt
#define	ToUint					emType_ToUint
#define	ToLong32				emType_ToLong32
#define	ToUlong32				emType_ToUlong32
#define	ToLong					emType_ToLong
#define	ToUlong					emType_ToUlong
#define	ToLong64				emType_ToLong64
#define	ToUlong64				emType_ToUlong64
#define	ToFloat					emType_ToFloat
#define	ToDouble				emType_ToDouble
#endif



// Function:
// DoReverse(src, off, len)
// DoReverse(off, len)
// 
// Reverses the data stored at the source address (src + off)
// of specified length (len). The data at the source is directly
// reversed, and hence if the original data is required, then
// it is suggested to make a copy of it. If source base address
// is not specified, this library's internal buffer is assumed
// as the source base address.
// 
// Parameters:
// src:		the base address of source data
// off:		offset to the actual data to be reversed (src + off)
// len:		length of data to be reversed
// 
// Returns:
// nothing
// 
void emType_DoReverseExt(void* src, int off, int len)
{
	char byt;
	char *bg, *ed;
	for(bg=(char*)src, ed=bg+len-1; bg<ed; bg++, ed--)
	{
		byt = *bg;
		*bg = *ed;
		*ed = byt;
	}
}

#define	emType_DoReverseInt(off, len)	\
	emType_DoReverseExt(&emType, off, len)

#define	emType_DoReverse(...)	\
	Macro(Macro3(__VA_ARGS__, emType_DoReverseExt, emType_DoReverseInt)(__VA_ARGS__))

#if emType_Shorthand >= 1
#define	emTypeDoReverse			emType_DoReverse
#endif

#if	emType_Shorthand >= 2
#define	typDoReverse			emType_DoReverse
#endif

#if	emType_Shorthand >= 3
#define	DoReverse				emType_DoReverse
#endif



// Function:
// Get<Byte/Ushort/Uint16>Sum(src, off, len)
// Get<Byte/Ushort/Uint16>Sum(off, len)
// 
// Finds the sum of all bytes/ushorts at the specified source
// address (src + off) of the specified length (len). If source
// base address is not specified, this library's internal buffer
// is assumed as the source base address. This can be used to
// calculate checksums.
// 
// Parameters:
// src:		the base address of source data
// off:		offset to the data to be summed (src + off)
// len:		length of data to be summed
// 
// Returns:
// <type>_value:  the summed value
// 
byte emType_GetByteSumExt(void* src, int off, int len)
{
    byte sum = 0;
    byte* bsrc = ((byte*)src) + off;
    for(; len>0; len--, bsrc++)
    { sum += *bsrc; }
    return sum;
}

#define	emType_GetByteSumInt(off, len)	\
	emType_GetByteSumExt(&emType, off, len)

#define	emType_GetByteSum(...)	\
	Macro(Macro3(__VA_ARGS__, emType_GetByteSumExt, emType_GetByteSumInt)(__VA_ARGS__))

ushort emType_GetUshortSumExt(void* src, int off, int len)
{
    ushort sum = 0;
    ushort* bsrc = ((ushort*)src) + off;
	len >>= 1;
    for(; len>0; len--, bsrc++)
    { sum += *bsrc; }
    return sum;
}

#define	emType_GetUshortSumInt(off, len)	\
	emType_GetUshortSumExt(&emType, off, len)

#define	emType_GetUshortSum(...)	\
	Macro(Macro3(__VA_ARGS__, emType_GetUshortSumExt, emType_GetUshortSumInt)(__VA_ARGS__))

#define	emType_GetUint16Sum		emType_GetUshortSum

#if emType_Shorthand >= 1
#define	emTypeGetByteSum		emType_GetByteSum
#define	emTypeGetUshortSum		emType_GetUshortSum
#define	emTypeGetUint16Sum		emType_GetUint16Sum
#endif

#if	emType_Shorthand >= 2
#define	typGetByteSum			emType_GetByteSum
#define	typGetUshortSum			emType_GetUshortSum
#define	typGetUint16Sum			emType_GetUint16Sum
#endif

#if	emType_Shorthand >= 3
#define	GetByteSum				emType_GetByteSum
#define	GetUshortSum			emType_GetUshortSum
#define	GetUint16Sum			emType_GetUint16Sum
#endif



// Function:
// GetHexFromBin(dst, sz, src, off, len, opt)
// GetHexFromBin(dst, sz, off, len, opt)
// 
// Get hexadecimal string (dst) of maximum specified size (sz) of
// the soure binary data (src + off) of specified length (len). The
// options (opt) specify how the conversion is to be performed, and
// it takes as input a set of flags. If source base address is not
// specified, this library's internal buffer is assumed as the source
// base address.
// 
// Parameters:
// dst:	      the destination string where hex string will be stored
// sz:        the maximum possible size of the hex string (buffer size)
// src:	      the base address of source binary data
// off:	      offset to the binary data to be converted (src + off)
// len:	      length of data to be converted
// opt:	      conversion options (TYPE_ADD_SPACE, TYPE_ADD_CHAR, TYPE_BIG_ENDIAN)
// 
// Returns:
// nothing
// 
#define emType_HEX_TO_BIN(ch)		(((ch) <= '9')? (ch)-'0' : (ch)-'7')

#define emType_BIN_TO_HEX(bn)		(((bn) <= 9)? (bn)+'0' : (bn)+'7' )

#define	emType_NO_SPACE				0

#define emType_ADD_SPACE			1

#define	emType_HAS_SPACE			1

#define	emType_NO_CHAR				0

#define emType_ADD_CHAR				2

#define	emType_HAS_CHAR				2

#define	emType_LITTLE_ENDIAN		0

#define emType_BIG_ENDIAN			4

string emType_GetHexFromBinExt(string dst, int sz, void* src, int off, int len, byte opt)
{
	char* dend = dst + sz - 1;
	byte* cbin = ((byte*)src) + ((opt & emType_BIG_ENDIAN)? off : (off+len-1));
	int stp = (opt & emType_BIG_ENDIAN)? 1 : -1;
	for(int i=0; i<len; i++, cbin+=stp)
	{
		*dst = emType_BIN_TO_HEX(*cbin >> 4); dst++; if(dst >= dend) break;
		*dst = emType_BIN_TO_HEX(*cbin & 0xF); dst++; if(dst >= dend) break;
		if(opt & emType_ADD_CHAR) { *dst = (*cbin < 32 || *cbin > 127)? '.' : *cbin; dst++; if(dst >= dend) break;}
		if(opt & emType_ADD_SPACE) { *dst = ' '; dst++; if(dst >= dend) break;}
	}
	*dst = '\0';
	return dst;
}

#define	emType_GetHexFromBinInt(dst, sz, off, len, opt)	\
	emType_GetHexFromBinExt(dst, sz, &emType, off, len, opt)

#define	emType_GetHexFromBin(...)	\
	Macro(Macro6(__VA_ARGS__, emType_GetHexFromBinExt, emType_GetHexFromBinInt)(__VA_ARGS__))

#if emType_Shorthand >= 1
#define	emTypeHEX_TO_BIN		emType_HEX_TO_BIN
#define	emTypeBIN_TO_HEX		emType_BIN_TO_HEX
#define	emTypeNO_SPACE			emType_NO_SPACE
#define	emTypeADD_SPACE			emType_ADD_SPACE
#define	emTypeHAS_SPACE			emType_HAS_SPACE
#define	emTypeNO_CHAR			emType_NO_CHAR
#define	emTypeADD_CHAR			emType_ADD_CHAR
#define	emTypeHAS_CHAR			emType_HAS_CHAR
#define	emTypeLITTLE_ENDIAN		emType_LITTLE_ENDIAN
#define	emTypeBIG_ENDIAN		emType_BIG_ENDIAN
#define	emTypeGetHexFromBin		emType_GetHexFromBin
#endif

#if	emType_Shorthand >= 2
#define	typHEX_TO_BIN			emType_HEX_TO_BIN
#define	typBIN_TO_HEX			emType_BIN_TO_HEX
#define	typNO_SPACE				emType_NO_SPACE
#define	typADD_SPACE			emType_ADD_SPACE
#define	typHAS_SPACE			emType_HAS_SPACE
#define	typNO_CHAR				emType_NO_CHAR
#define	typADD_CHAR				emType_ADD_CHAR
#define	typHAS_CHAR				emType_HAS_CHAR
#define	typLITTLE_ENDIAN		emType_LITTLE_ENDIAN
#define	typBIG_ENDIAN			emType_BIG_ENDIAN
#define	typGetHexFromBin		emType_GetHexFromBin
#endif

#if	emType_Shorthand >= 3
#define	HEX_TO_BIN				emType_HEX_TO_BIN
#define	BIN_TO_HEX				emType_BIN_TO_HEX
#define	NO_SPACE				emType_NO_SPACE
#define	ADD_SPACE				emType_ADD_SPACE
#define	HAS_SPACE				emType_HAS_SPACE
#define	NO_CHAR					emType_NO_CHAR
#define	ADD_CHAR				emType_ADD_CHAR
#define	HAS_CHAR				emType_HAS_CHAR
#define	LITTLE_ENDIAN			emType_LITTLE_ENDIAN
#define	BIG_ENDIAN				emType_BIG_ENDIAN
#define	GetHexFromBin			emType_GetHexFromBin
#endif



// Function:
// PutBinFromHex(dst, off, len, src, opt)
// PutBinFromHex(off, len, src, opt)
// 
// Puts binary data from the source hex string (src) to the destination
// address (dst + off) of specified length len. The options (opt) specify
// how the conversion is to be performed, and it takes as input a set of
// flags. If destination base address is not specified, this library's
// internal buffer is assumed as the destination base address.
// 
// Parameters:
// dst:	      the base address of destination
// off:	      the destination offset where the binary data will be stored (dst + off)
// len:       length of data at destination
// src:	      the hex string to be converted
// opt:	      conversion options (TYPE_HAS_SPACE, TYPE_HAS_CHAR, TYPE_BIG_ENDIAN)
//
// Returns:
// the converted data (dst)
// 
void emType_PutBinFromHexExt(void* dst, int off, int len, string src, byte opt)
{
	char* hsrc = src + strlen(src) - 1;
	byte* cbin = ((byte*)dst) + ((opt & emType_BIG_ENDIAN)? (off+len-1) : off);
	int stp = (opt & emType_BIG_ENDIAN)? -1 : 1;
	for(int i=0; i<len; i++, cbin+=stp)
	{
		if(opt & emType_HAS_SPACE) hsrc--;
		if(opt & emType_HAS_CHAR) hsrc--;
		*cbin = (hsrc < src)? 0 : emType_HEX_TO_BIN(*hsrc); hsrc--;
		*cbin |= (hsrc < src)? 0 : emType_HEX_TO_BIN(*hsrc) << 4; hsrc--;
	}
}

#define	emType_PutBinFromHexInt(off, len, src, opt)	\
	emType_PutBinFromHexExt(&emType, off, len, src, opt)

#define	emType_PutBinFromHex(...)	\
	Macro(Macro5(__VA_ARGS__, emType_PutBinFromHexExt, emType_PutBinFromHexInt)(__VA_ARGS__))

#if emType_Shorthand >= 1
#define	emTypePutBinFromHex		emType_PutBinFromHex
#endif

#if	emType_Shorthand >= 2
#define	typPutBinFromHex		emType_PutBinFromHex
#endif

#if	emType_Shorthand >= 3
#define	PutBinFromHex			emType_PutBinFromHex
#endif



#endif
