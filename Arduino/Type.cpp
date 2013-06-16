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
// The default value of TYPE_LENGTH_BYTES is 1 (1 byte)
// which should be an appropriate value when the application
// is related to working with low-cost embedded devices,
// with limited SRAM capacity
#ifndef TYPE_LENGTH_BYTES
#define	TYPE_LENGTH_BYTES		1
#endif

// define shorthand datatypes
typedef signed char sbyte;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef char* string;
#ifndef null
#define null ((void*)0)
#endif
