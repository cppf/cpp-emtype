/*
----------------------------------------------------------------------------------------
	Embedded_Type: Library header file for Arudino
	File: Embedded_Type.h

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



/*
	Embedded_Type is a generic type conversion library for Arduino/Libelium Waspmote/Processing/C/C++.
	It has been developed mainly for simplifying the process of writing wireless communication
	programs on Arduino, Waspmote and Processing. To use it (in Arduino), copy the directory, this file
	is in to arduino_root_folder/libraries/. Then restart Arduino, goto Sketch->Add Library->
	Embedded_Type.
*/



#ifndef	_Embedded_Type_h_
#define	_Embedded_Type_h_



// Requisite headers
#include <Arduino.h>



// Simulate macro overloading
// By default, C++ does not support macro overloading, but
// through the use of variable argument macros called variadic
// macros, it is possible to support macro overloading to some
// extent
#ifndef	Macro
#define	Macro(x)	x
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
typedef signed char			sbyte;
typedef unsigned short		ushort;
typedef short				int16;
typedef unsigned short		uint16;
typedef unsigned int		uint;
typedef int					long32;
typedef unsigned int		ulong32;
typedef unsigned long		ulong;
typedef char*				string;
typedef long long			long64;
typedef unsigned long long	ulong64;



// internal buffer format
typedef union _TypeInternalBuffer
{
	byte	Byte[16];
	sbyte	Sbyte[16];
	char	Char[16];
	short	Short[8];
	ushort	Ushort[8];
	int16	Int16[8];
	uint16	Uint16[8];
	int		Int[4];
	uint	Uint[4];
	long32	Long32[4];
	ulong32	Ulong32[4];
	long	Long[2];
	ulong	Ulong[2];
	long64	Long64[2];
	ulong64	Ulong64[2];
	float	Float[4];
	double	Double[2];
}TypeInternalBuffer;



// internal buffer
TypeInternalBuffer	TypeBuffer;



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
#define	GetBitExt(src, off, bit_no)	\
	((*(((byte*)src) + off + (bit_no >> 3)) >> (bit_no & 7)) & 1)

#define	GetBitInt(off, bit_no)	\
	GetBitExt(&TypeBuffer, off, bit_no)

#define GetBit(...)	\
	Macro(Macro3(__VA_ARGS__, GetBitExt, GetBitInt)(__VA_ARGS__))



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
#define	GetNibbleExt(src, off, nibble_no)	\
	((*(((byte*)src) + off + (nibble_no >> 1)) >> ((nibble_no & 1) << 2)) & 0xF)

#define	GetNibbleInt(off, nibble_no)	\
	GetNibbleExt(&TypeBuffer, off, nibble_no)

#define GetNibble(...)	\
	Macro(Macro3(__VA_ARGS__, GetNibbleExt, GetNibbleInt)(__VA_ARGS__))



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
#define	GetStypeExt(type, src, off)	\
	(*(((type*)src) + off))

#define	GetStypeInt(type, off)	\
	GetStypeExt(type, &TypeBuffer, off)

#define GetStype(...)	\
	Macro(Macro3(__VA_ARGS__, GetStypeExt, GetStypeInt)(__VA_ARGS__))

#define	GetTypeExt(type, src, off)	\
	(*((type*)(((byte*)src) + off)))

#define	GetTypeInt(type, off)	\
	GetTypeExt(type, &TypeBuffer, off)

#define	GetType(...) \
	Macro(Macro3(__VA_ARGS__, GetTypeExt, GetTypeInt)(__VA_ARGS__))

#define GetChar(...)	\
	Macro(GetStype(char, __VA_ARGS__))

#define GetByte(...)	\
	Macro(GetStype(byte, __VA_ARGS__))

#define GetBoolean(...)	\
	Macro(((GetByte(__VA_ARGS__) == 0)? FALSE : TRUE))

#define	GetShort(...)	\
	Macro(GetType(short, __VA_ARGS__))

#define	GetUshort(...)	\
	Macro(GetType(ushort, __VA_ARGS__))

#define	GetInt16(...)	\
	Macro(GetType(int16, __VA_ARGS__))

#define	GetUint16(...)	\
	Macro(GetType(uint16, __VA_ARGS__))

#define	GetInt(...)	\
	Macro(GetType(int, __VA_ARGS__))

#define	GetUint(...)	\
	Macro(GetType(uint, __VA_ARGS__))

#define	GetLong32(...)	\
	Macro(GetType(long32, __VA_ARGS__))

#define	GetUlong32(...)	\
	Macro(GetType(ulong32, __VA_ARGS__))

#define	GetLong(...)	\
	Macro(GetType(long, __VA_ARGS__))

#define	GetUlong(...)	\
	Macro(GetType(ulong, __VA_ARGS__))

#define	GetLong64(...)	\
	Macro(GetType(long64, __VA_ARGS__))

#define	GetUlong64(...)	\
	Macro(GetType(ulong64, __VA_ARGS__))

#define	GetFloat(...)	\
	Macro(GetType(float, __VA_ARGS__))

#define	GetDouble(...)	\
	Macro(GetType(double, __VA_ARGS__))



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
#define	TYPE_ZEROED_STRING			0

#define	TYPE_LENGTH_STRING			1

string GetStringExt(string dst, int sz, void* src, int off, byte opt)
{
	int len;
	char* xsrc = ((char*)src) + off;
	if(opt & TYPE_LENGTH_STRING) len = *xsrc;
	else len = strlen(xsrc);
	len = ((sz - 1) < len)? (sz - 1) : len;
	memcpy(dst, xsrc+1, len);
	dst[len] = '\0';
	return dst;
}

#define	GetStringInt(dst, sz, off, opt)	\
	GetStringExt(dst, sz, &TypeBuffer, off, opt)

#define GetString(...)	\
	Macro(Macro5(__VA_ARGS__, GetStringExt, GetStringInt)(__VA_ARGS__))



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
#define	PutBitExt(dst, off, bit_no, bit_value)	\
	((bit_value == 0)?(*(((byte*)dst) + off + (bit_no >> 3)) &= ~(1 << ((byte)bit_no & (byte)7))) : (*(((byte*)dst) + off + (bit_no >> 3)) |= (1 << ((byte)bit_no & (byte)7))))

#define	PutBitInt(off, bit_no, bit_value)	\
	PutBitExt(&TypeBuffer, off, bit_no, bit_value)

#define PutBit(...)	\
	Macro(Macro4(__VA_ARGS__, PutBitExt, PutBitInt)(__VA_ARGS__))



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
#define	PutNibbleExt(dst, off, nibble_no, nibble_value)	\
	(*(((byte*)dst) + off + (nibble_no >> 1)) = (*(((byte*)dst) + off + (nibble_no >> 1)) & (~(0xF << ((nibble_no & 1) << 2)))) | (nibble_value << ((nibble_no & 1) << 2)))

#define	PutNibbleInt(off, nibble_no, nibble_value)	\
	PutNibbleExt(&TypeBuffer, off, nibble_no, nibble_value)

#define PutNibble(...)	\
	Macro(Macro4(__VA_ARGS__, PutNibbleExt, PutNibbleInt)(__VA_ARGS__))



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
#define	PutStypeExt(type, dst, off, value)	\
	(*(((type*)dst) + off) = value)

#define	PutStypeInt(type, off, value)	\
	PutStypeExt(type, &TypeBuffer, off, value)

#define PutStype(...)	\
	Macro(Macro4(__VA_ARGS__, PutStypeExt, PutStypeInt)(__VA_ARGS__))

#define	PutTypeExt(type, dst, off, value)	\
	(*((type*)(((byte*)dst) + off)) = value)

#define	PutTypeInt(type, off, value)	\
	PutTypeExt(type, &TypeBuffer, off, value)

#define	PutType(...) \
	Macro(Macro4(__VA_ARGS__, PutTypeExt, PutTypeInt)(__VA_ARGS__))

#define PutChar(...)	\
	Macro(PutStype(char, __VA_ARGS__))

#define PutByte(...)	\
	Macro(PutStype(byte, __VA_ARGS__))

#define PutBoolean(...)	\
	Macro(((PutByte(__VA_ARGS__) == 0)? FALSE : TRUE))

#define	PutShort(...)	\
	Macro(PutType(short, __VA_ARGS__))

#define	PutUshort(...)	\
	Macro(PutType(ushort, __VA_ARGS__))

#define	PutInt16(...)	\
	Macro(PutType(int16, __VA_ARGS__))

#define	PutUint16(...)	\
	Macro(PutType(uint16, __VA_ARGS__))

#define	PutInt(...)	\
	Macro(PutType(int, __VA_ARGS__))

#define	PutUint(...)	\
	Macro(PutType(uint, __VA_ARGS__))

#define	PutLong32(...)	\
	Macro(PutType(long32, __VA_ARGS__))

#define	PutUlong32(...)	\
	Macro(PutType(ulong32, __VA_ARGS__))

#define	PutLong(...)	\
	Macro(PutType(long, __VA_ARGS__))

#define	PutUlong(...)	\
	Macro(PutType(ulong, __VA_ARGS__))

#define	PutLong64(...)	\
	Macro(PutType(long64, __VA_ARGS__))

#define	PutUlong64(...)	\
	Macro(PutType(ulong64, __VA_ARGS__))

#define	PutFloat(...)	\
	Macro(PutType(float, __VA_ARGS__))

#define	PutDouble(...)	\
	Macro(PutType(double, __VA_ARGS__))



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
void PutStringExt(void* dst, int off, string value, byte opt)
{
	char* xdst = ((char*)dst) + off;
	int len = strlen(value);
	if(opt & TYPE_LENGTH_STRING) {*xdst = (char)len; xdst++;}
	else len++;
	memcpy(xdst, value, len);
}

#define	PutStringInt(off, value, opt)	\
	PutStringExt(&TypeBuffer, off, value, opt)

#define	PutString(...)	\
	Macro(Macro4(__VA_ARGS__, PutStringExt, PutStringInt)(__VA_ARGS__))



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
#define	ToNibble(bit3, bit2, bit1, bit0)	\
	((bit3 << 3) | (bit2 << 2) | (bit1 << 1) | bit0)

#define ToByteNib(nibble1, nibble0)	\
	((nibble1 << 4) | nibble0)

#define	ToByteBit(bit7, bit6, bit5, bit4, bit3, bit2, bit1, bit0)	\
	ToByteNib(ToNibble(bit7, bit6, bit5, bit4), ToNibble(bit3, bit2, bit1, bit0))

#define ToByte(...)	\
	Macro(Macro8(__VA_ARGS__, ToByteBit, _7, _6, _5, _4, _3, ToByteNib)(__VA_ARGS__))

#define	ToChar			ToByte	

#define	ToType2(var, ret, rtype, dat1, dat0)	\
	(((TypeBuffer.var[0] = dat0) & (TypeBuffer.var[1] = dat1) & 0)? (rtype)0 : TypeBuffer.ret[0])

#define	ToType4(var, ret, rtype, dat3, dat2, dat1, dat0)	\
	(((TypeBuffer.var[0] = dat0) & (TypeBuffer.var[1] = dat1) & (TypeBuffer.var[2] = dat2) & (TypeBuffer.var[3] = dat3) & 0)? (rtype)0 : TypeBuffer.ret[0])

#define ToType8(var, ret, rtype, dat7, dat6, dat5, dat4, dat3, dat2, dat1, dat0)	\
	(((TypeBuffer.var[0] = dat0) & (TypeBuffer.var[1] = dat1) & (TypeBuffer.var[2] = dat2) & (TypeBuffer.var[3] = dat3) & (TypeBuffer.var[4] = dat4) & (TypeBuffer.var[5] = dat5) & (TypeBuffer.var[6] = dat6) & (TypeBuffer.var[7] = dat7) & 0)? (rtype)0 : TypeBuffer.ret[0])

#define	ToShort(byte1, byte0)	\
	ToType2(Byte, Short, short, byte1, byte0)

#define	ToUshort(byte0, byte1)	\
	ToType2(Byte, Short, short, byte1, byte0)

#define	ToInt16			ToShort

#define	ToUint16		ToUshort

#define	ToIntSrt(ushort1, ushort0)	\
	ToType2(Ushort, Int, int, ushort1, ushort0)

#define	ToIntByt(byte3, byte2, byte1, byte0)	\
	ToType4(Byte, Int, int, byte3, byte2, byte1, byte0)

#define	ToInt(...)	\
	Macro(Macro4(__VA_ARGS__, ToIntByt, _3, ToIntSrt)(__VA_ARGS__))

#define	ToUintSrt(ushort1, ushort0)	\
	ToType2(Ushort, Uint, uint, ushort1, ushort0)

#define	ToUintByt(byte3, byte2, byte1, byte0)	\
	ToType4(Byte, Uint, uint, byte3, byte2, byte1, byte0)

#define	ToUint(...)	\
	Macro(Macro4(__VA_ARGS__, ToUintByt, _3, ToUintSrt)(__VA_ARGS__))

#define	ToLong32		ToInt

#define	ToUlong32		ToUint

#define	ToLong			ToInt

#define	ToUlong			ToUint

#define	ToLong64Int(uint1, uint0)	\
	ToType2(Uint, Long64, long64, uint1, uint0)

#define	ToLong64Srt(ushort3, ushort2, ushort1, ushort0)	\
	ToType4(Ushort, Long64, long64, ushort3, ushort2, ushort1, ushort0)

#define	ToLong64Byt(byte7, byte6, byte5, byte4, byte3, byte2, byte1, byte0)	\
	ToType8(Byte, Long64, long64, byte7, byte6, byte5, byte4, byte3, byte2, byte1, byte0)

#define	ToLong64(...)	\
	Macro(Macro8(__VA_ARGS__, ToLong64Byt, _7, _6, _5, ToLong64Srt, _3, ToLong64Int)(__VA_ARGS__))

#define	ToUlong64Int(uint1, uint0)	\
	ToType2(Uint, Ulong64, ulong64, uint1, uint0)

#define	ToUlong64Srt(ushort3, ushort2, ushort1, ushort0)	\
	ToType4(Ushort, Ulong64, ulong64, ushort3, ushort2, ushort1, ushort0)

#define	ToUlong64Byt(byte7, byte6, byte5, byte4, byte3, byte2, byte1, byte0)	\
	ToType8(Byte, Ulong64, ulong64, byte7, byte6, byte5, byte4, byte3, byte2, byte1, byte0)

#define	ToUlong64(...)	\
	Macro(Macro8(__VA_ARGS__, ToUlong64Byt, _7, _6, _5, ToUlong64Srt, _3, ToUlong64Int)(__VA_ARGS__))

#define	ToFloatSrt(ushort1, ushort0)	\
	ToType2(Ushort, Float, float, ushort1, ushort0)

#define	ToFloatByt(byte3, byte2, byte1, byte0)	\
	ToType4(Byte, Float, float, byte3, byte2, byte1, byte0)

#define	ToFloat(...)	\
	Macro(Macro4(__VA_ARGS__, ToFloatByt, _3, ToFloatSrt)(__VA_ARGS__))

#define	ToDoubleInt(uint1, uint0)	\
	ToType2(Uint, Double, double, uint1, uint0)

#define	ToDoubleSrt(ushort3, ushort2, ushort1, ushort0)	\
	ToType4(Ushort, Double, double, ushort3, ushort2, ushort1, ushort0)

#define	ToDoubleByt(byte7, byte6, byte5, byte4, byte3, byte2, byte1, byte0)	\
	ToType8(Byte, Double, double, byte7, byte6, byte5, byte4, byte3, byte2, byte1, byte0)

#define	ToDouble(...)	\
	Macro(Macro8(__VA_ARGS__, ToDoubleByt, _7, _6, _5, ToDoubleSrt, _3, ToDoubleInt)(__VA_ARGS__))



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
void DoReverseExt(void* src, int off, int len)
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

#define	DoReverseInt(off, len)	\
	DoReverseExt(&TypeBuffer, off, len)

#define	DoReverse(...)	\
	Macro(Macro3(__VA_ARGS__, DoReverseExt, DoReverseInt)(__VA_ARGS__))



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
byte GetByteSumExt(void* src, int off, int len)
{
    byte sum = 0;
    byte* bsrc = ((byte*)src) + off;
    for(; len>0; len--, bsrc++)
    { sum += *bsrc; }
    return sum;
}

#define	GetByteSumInt(off, len)	\
	GetByteSumExt(&TypeBuffer, off, len)

#define	GetByteSum(...)	\
	Macro(Macro3(__VA_ARGS__, GetByteSumExt, GetByteSumInt)(__VA_ARGS__))

ushort GetUshortSumExt(void* src, int off, int len)
{
    ushort sum = 0;
    ushort* bsrc = ((ushort*)src) + off;
	len >>= 1;
    for(; len>0; len--, bsrc++)
    { sum += *bsrc; }
    return sum;
}

#define	GetUshortSumInt(off, len)	\
	GetUshortSumExt(&TypeBuffer, off, len)

#define	GetUshortSum(...)	\
	Macro(Macro3(__VA_ARGS__, GetUshortSumExt, GetUshortSumInt)(__VA_ARGS__))

#define	GetUint16Sum		GetUshortSum



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
#define TYPE_HEX_TO_BIN(ch)		(((ch) <= '9')? (ch)-'0' : (ch)-'7')

#define TYPE_BIN_TO_HEX(bn)		(((bn) <= 9)? (bn)+'0' : (bn)+'7' )

#define	TYPE_NO_SPACE			0

#define TYPE_ADD_SPACE			1

#define	TYPE_HAS_SPACE			1

#define	TYPE_NO_CHAR			0

#define TYPE_ADD_CHAR			2

#define	TYPE_HAS_CHAR			2

#define	TYPE_LITTLE_ENDIAN		0

#define TYPE_BIG_ENDIAN			4

void PutHexFromBinExt(string dst, int dst_off, void* src, int src_off, int len, byte opt)
{
	byte* cbin = (opt & TYPE_BIG_ENDIAN)? (byte*)src : ((byte*)src)+len-1;
	dst += dst_off; cbin += src_off;
	int stp = (opt & TYPE_BIG_ENDIAN)? 1 : -1;
	for(int i=0; i<len; i++, cbin+=stp)
	{
		*dst = TYPE_BIN_TO_HEX(*cbin >> 4); dst++;
		*dst = TYPE_BIN_TO_HEX(*cbin & 0xF); dst++;
		if(opt & TYPE_ADD_CHAR) { *dst = (*cbin < 32 || *cbin > 127)? '.' : *cbin; dst++; }
		if(opt & TYPE_ADD_SPACE) { *dst = ' '; dst++; }
	}
	*dst = '\0';
}

#define	PutHexFromBinInt(dst, dst_off, src_off, len, opt)	\
	PutHexFromBinExt(dst, dst_off, &TypeBuffer, src_off, len, opt)

#define	PutHexFromBin(...)	\
	Macro(Macro6(__VA_ARGS__, PutHexFromBinExt, PutHexFromBinInt)(__VA_ARGS__))



// Function:
// PutBinFromHex(dst, off, len, src, opt)
// PutBinFromHex(off, len, src, opt)
// 
// Putts binary data from the source hex string (src) to the destination
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
void PutBinFromHexExt(void* dst, int dst_off, int len, string src, int src_off, byte opt)
{
	char* hsrt = src + src_off;
	char* hsrc = hsrt + strlen(src) - 1;
	byte* cbin = dst_off + ((opt & TYPE_BIG_ENDIAN)?  ((byte*)dst)+len-1: (byte*)dst);
	int stp = (opt & TYPE_BIG_ENDIAN)? -1 : 1;
	for(int i=0; i<len; i++, cbin+=stp)
	{
		if(opt & TYPE_HAS_SPACE) hsrc--;
		if(opt & TYPE_HAS_CHAR) hsrc--;
		*cbin = (hsrc < hsrt)? 0 : TYPE_HEX_TO_BIN(*hsrc); hsrc--;
		*cbin |= (hsrc < hsrt)? 0 : TYPE_HEX_TO_BIN(*hsrc) << 4; hsrc--;
	}
}

#define	PutBinFromHexInt(dst_off, len, src, src_off, opt)	\
	PutBinFromHexExt(&TypeBuffer, dst_off, len, src, src_off, opt)

#define	PutBinFromHex(...)	\
	Macro(Macro6(__VA_ARGS__, PutBinFromHexExt, PutBinFromHexInt)(__VA_ARGS__))



#endif
