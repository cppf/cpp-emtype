/*
 * Embedded_Type Library
 *
 * This library converts data from one type
 * to another
 */



#ifndef	_Embedded_Type_h_
#define	_Embedded_Type_h_



// Requisite headers
#include <stdio.h>



// When arrays are used with this library, their length
// is indicated with a length field before any array
// data. The size of this length field in bytes can be
// controlled by defining the TYPE_LENGTH_BYTES constant
// before including this library (or by changing it in
// the header file itself).
// 
// The default value of TYPE_LENGTH_BYTES is 1 (1 byte)
// which should be an appropriate value when the application
// is related to working with low-cost embedded devices,
// with limited SRAM capacity
// 
#ifndef TYPE_LENGTH_BYTES
#define	TYPE_LENGTH_BYTES		1
#endif


// When "getting" or "putting" values without specifying
// a source or destination, causes this library to make
// use of its internal buffer for fetching or storing data.
//
// "putting" more data than this internal buffer size may
// cause the operation to fail, or even may cause running
// application to crash. When "getting", in addition to the
// above problems, it could also be possible to get garbage
// data.
//
// To avoid all these circumstances, define the value of
// TYPE_BUFFER_SIZE to the maximum utilized size in the
// application (before including this library)
// 
#ifndef	TYPE_BUFFER_SIZE
#define	TYPE_BUFFER_SIZE		32
#endif



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


// shorthand datatypes
typedef unsigned char byte;
typedef signed char	sbyte;
typedef int int16;
typedef unsigned int uint;
typedef unsigned int uint16;
typedef long long32;
typedef unsigned long ulong;
typedef unsigned long ulong32;
typedef char* string;
#ifndef null
#define null ((void*)0)
#endif
typedef struct _long64
{
	long Long[2];
}long64;
typedef struct _ulong64
{
	ulong Ulong[2];
}ulong64;



// internal buffer format
typedef union _TypeInternalBuffer
{
	byte	Data[TYPE_BUFFER_SIZE];
	byte	Byte[16];
	sbyte	Sbyte[16];
	char	Char[16];
	int		Int[8];
	uint	Uint[8];
	int16	Int16[8];
	uint16	Uint16[8];
	long	Long[4];
	ulong	Ulong[4];
	long32	Long32[4];
	ulong32	Ulong32[4];
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
// internal buffer is used as the source
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
// from the specified source address with offset (src + off). if source
// address (src) is not specified, then this library's internal buffer
// is used as the source
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
// GetBit(off, nibble_no)
// 
// Returns the value of nibble at the specified nibble number (nibble_no)
// from this library's internal buffer with offset (TypeBuffer + off)
// 
// Parameters:
// off:			offset from which nibble index starts
// nibble_no:	the index of the nibble (starts from 0)
// 
// Returns:
// nibble_value:	the value of the specified nibble (0 to 15 or 0x0 to 0xF)
// 



#endif
