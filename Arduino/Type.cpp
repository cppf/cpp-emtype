/*
 * Type Library
 *
 * This library converts data from one type
 * to another
 */

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



// shorthand datatypes
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



// internal buffer
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