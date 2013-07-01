/*
----------------------------------------------------------------------------------------
	emStream: Static multi-tasked stream library for emdb library (C/C++)
	File: emType.h

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
	emStream is a static multi-tasked stream library for emdb library. It has been developed for
	for being used in the development of the internet of things for AVR processors. For information,
	on its usage, please visit: https://github.com/wolfram77/embd.
*/



#ifndef	_emStream_h_
#define	_emStream_h_



// Requisite headers
#include "embd/emType.h"
#include "embd/emTask.h"



// select shorthanding scheme
#ifndef	emStream_Shorthand
#define	emStream_Shorthand	2
#endif



// Stream Mold format
// 
// Streams can be created with different sizes. emStream_Mold8 has a size of 8 bytes,
// emStream_Mold16 has 16 bytes size, and so on. The range is from 8 to 256 bytes (in
// powers of 2). The default emStream_Mold has a size of 256 bytes. The size of streams
// must always be a power of 2. This fact is used to replace modulus operation, with the
// and operation (which is very fast).
// 
#define	emStream_MoldMake(size)	\
typedef struct _emStream_Mold##size	\
{	\
	byte	Front;	\
	byte	Rear;	\
	byte	Count;	\
	byte	Max;	\
	byte	Data[size];	\
}emStream_Mold##size

emStream_MoldMake(8);

emStream_MoldMake(16);

emStream_MoldMake(32);

emStream_MoldMake(64);

emStream_MoldMake(128);

emStream_MoldMake(256);

#define	emStream_Mold			emStream_Mold256

#if emStream_Shorthand >= 1
#define	stream_Mold8			emStream_Mold8
#define	stream_Mold6			emStream_Mold16
#define	stream_Mold32			emStream_Mold32
#define	stream_Mold64			emStream_Mold64
#define	stream_Mold128			emStream_Mold128
#define	stream_Mold256			emStream_Mold256
#define	stream_Mold				emStream_Mold
#endif

#if	emStream_Shorthand >= 2
#define	stmMold8				emStream_Mold8
#define	stmMold6				emStream_Mold16
#define	stmMold32				emStream_Mold32
#define	stmMold64				emStream_Mold64
#define	stmMold128				emStream_Mold128
#define	stmMold256				emStream_Mold256
#define	stmMold					emStream_Mold
#endif



// Internal Storage variables
byte	emStream_LoopI = 0;




// Function:
// Init(stream, size)
// 
// Initializes a stream before use. The size of stream (size) is required
// to be specified to that the stream can be initialized according to its
// size. When using a pointer to stream, just use Init(*stream, size).
// 
// Parameters:
// stream:	the stream to initialize
// size:	size of the stream to be initialized
// 
// Returns:
// nothing
//
#define	emStream_Init(stream, size)	\
	do{	\
		(stream).Front = 0;	\
		(stream).Rear = 0;	\
		(stream).Count = 0;	\
		(stream).Max = (size) - 1;	\
	}while(0)

#if emStream_Shorthand >= 1
#define	stream_Init				emStream_Init
#endif

#if	emStream_Shorthand >= 2
#define	stmInit					emStream_Init
#endif



// Function:
// Clear(stream)
// 
// Clears a stream of all data. When using a pointer to stream, just use
// Clear(*stream).
// 
// Parameters:
// stream:	the stream to clear
// 
// Returns:
// nothing
//
#define	emStream_Clear(stream)	\
	do{	\
		(stream).Front = 0;	\
		(stream).Rear = 0;	\
		(stream).Count = 0;	\
	}while(0)

#if emStream_Shorthand >= 1
#define	stream_Clear			emStream_Clear
#endif

#if	emStream_Shorthand >= 2
#define	stmClear				emStream_Clear
#endif



// Function:
// GetAvail(stream)
// 
// Gives the number of bytes available in a stream. Can be used to check if
// sufficient number of bytes are available before reading. When using a
// pointer to stream, just use GetAvail(*stream).
// 
// Parameters:
// stream:	the stream whose available bytes are to be known
// 
// Returns:
// bytes_avail:	number of available bytes in stream
//
#define	emStream_GetAvail(stream)	\
	((stream).Count)

#if emStream_Shorthand >= 1
#define	stream_GetAvail			emStream_GetAvail
#endif

#if	emStream_Shorthand >= 2
#define	stmGetAvail				emStream_GetAvail
#endif


 
// Function:
// GetFree(stream)
// 
// Gives the amount of free space in bytes available in a stream. Can be
// used to check if sufficient free space is available before writing.
// When using a pointer to stream, just use GetFree(*stream).
// 
// Parameters:
// stream:	the stream whose amount of free space in bytes are to be known
// 
// Returns:
// bytes_free:	amount of free space in stream (bytes)
//
#define	emStream_GetFree(stream)	\
	(1 + (stream).Max - (stream).Count)

#if emStream_Shorthand >= 1
#define	stream_GetFree			emStream_GetFree
#endif

#if	emStream_Shorthand >= 2
#define	stmGetFree				emStream_GetFree
#endif



// Function:
// ReadBytes</Int>(stream, dst, len)
// ReadBytes</Int>(stream, len)
// 
// Reads a set of bytes from the stream, if destination address (dst) is
// specified. If destination address (dst) is not specified, then just
// remove specified length (len) of bytes from the stream. If the stream
// does not have sufficient number of bytes available, then the current
// task/thread will be blocked until sufficient bytes are not available.
// This is not allowed inside an interrupt (task switching cannot occur
// from inside  an interrupt). In such a case use ReadBytesInt(), instead
// of ReadBytes(). ReadBytesInt() directly exits if sufficient bytes are
// not available. If waiting in a task is not desirable then GetAvail()
// can be used to check the number of bytes available in stream, and then
// accordingly choose to read or do something else.
// 
// Parameters:
// stream:	the stream from which a set of bytes is to be read
// dst:		the variable to which the read bytes are to be stored
// len:		number of bytes to be read from stream
// 
// Returns:
// nothing
//
#define	emStream_ReadBytesIntDel(stream, len)	\
	do{	\
		if(emStream_GetAvail(stream) < len) break;	\
		(stream).Front = ((stream).Front + len) & (stream).Max;	\
		(stream).Count -= len;	\
	}while(0)

#define	emStream_ReadBytesIntDst(stream, dst, len)	\
	do{	\
		if(emStream_GetAvail(stream) < len) break;	\
		for(emStream_LoopI = 0; emStream_LoopI < (len); emStream_LoopI++)	\
		{	\
			*(((byte*)(&(dst))) + emStream_LoopI) = (stream).Data[(stream).Front];	\
			(stream).Front = ((stream).Front + 1) * (stream).Max;	\
		}	\
		(stream).Count -= len;	\
	}while(0)

#define	emStream_ReadBytesInt(...)	\
	Macro(Macro3(__VA_ARGS__, emStream_ReadBytesIntDst, emStream_ReadBytesIntDel)(__VA_ARGS__))

#define	emStream_ReadBytesDel(stream, len)	\
	do{	\
		for(emStream_LoopI = 0; emStream_LoopI < (len); emStream_LoopI++)	\
		{	\
			emTask_WaitWhile(emStream_GetAvail(stream) < 1, byte, emStream_LoopI);	\
			(stream).Front = ((stream).Front + 1) * (stream).Max;	\
			(stream).Count--;	\
		}	\
	}while(0)

#define	emStream_ReadBytesDst(stream, dst, len)	\
	do{	\
		for(emStream_LoopI = 0; emStream_LoopI < (len); emStream_LoopI++)	\
		{	\
			emTask_WaitWhile(emStream_GetAvail(stream) < 1, byte, emStream_LoopI);	\
			*(((byte*)(&(dst))) + emStream_LoopI) = (stream).Data[(stream).Front];	\
			(stream).Front = ((stream).Front + 1) & (stream).Max;	\
			(stream).Count--;	\
		}	\
	}while(0)

#define	emStream_ReadBytes(...)	\
	Macro(Macro3(__VA_ARGS__, emStream_ReadBytesDst, emStream_ReadBytesDel)(__VA_ARGS__))

#if emStream_Shorthand >= 1
#define	stream_ReadBytesInt		emStream_ReadBytesInt
#define	stream_ReadBytes		emStream_ReadBytes
#endif

#if	emStream_Shorthand >= 2
#define	stmReadBytesInt			emStream_ReadBytesInt
#define	stmReadBytes			emStream_ReadBytes
#endif



// Function:
// Read<Type></Int>(stream)
// Read<Type></Int>(stream, <Type>_var)
// 
// Reads a type data from the stream. If the stream does not have sufficient
// number of bytes available, then the current task/thread will be blocked
// until sufficient bytes are not available. If this is not desirable then
// GetAvail() can be used to check the number of bytes available in stream,
// and then accordingly choose to read or do something else. When reading
// a stream from inside an interrupt, use Read<Type>Int(), instead of
// Read<Type>(). Read<Type>Int() directly exits if sufficient bytes are not
// available in the stream.
// 
// 
// Parameters:
// stream:	the stream from which type data is to be read
// <Type>_var:	variable where type value is stored
// 
// Returns: (if <Type>_var not used)
// <Type>_value:	the value of type data read
//
#define	emStream_ReadByteIntVal(stream, byte_var)	\
	do{	\
		if(emStream_GetAvail(stream) < 1) break;	\
		(byte_var) = (stream).Data[(stream).Front];	\
		(stream).Front = ((stream).Front + 1) & (stream).Max;	\
		(stream).Count--;	\
	}while(0)

#define	emStream_ReadByteIntRet(stream)	\
	({	\
		emStream_ReadByteIntVal(stream, emType.Byte[0]);	\
		emType.Byte[0];	\
	})

#define	emStream_ReadByteInt(...)	\
	Macro(Macro2(__VA_ARGS__, emStream_ReadByteIntVal, emStream_ReadByteIntRet)(__VA_ARGS__))

#define	emStream_ReadSbyteIntVal(stream, sbyte_var)	\
	do{	\
		if(emStream_GetAvail(stream) < 1) break;	\
		(sbyte_var) = (sbyte)(stream).Data[(stream).Front];	\
		(stream).Front = ((stream).Front + 1) & (stream).Max;	\
		(stream).Count--;	\
	}while(0)

#define	emStream_ReadSbyteIntRet(stream)	\
	({	\
		emStream_ReadSbyteIntVal(stream, emType.Sbyte[0]);	\
		emType.Sbyte[0];	\
	})

#define	emStream_ReadSbyteInt(...)	\
	Macro(Macro2(__VA_ARGS__, emStream_ReadSbyteIntVal, emStream_ReadSbyteIntRet)(__VA_ARGS__))

#define	emStream_ReadShortIntRet(stream)	\
	({	\
		emStream_ReadBytesInt(stream, emType.Short[0], 2);	\
		emType.Short[0];	\
	})

#define	emStream_ReadShortIntVal(stream, short_var)	\
	emStream_ReadBytesInt(stream, short_var, 2)

#define	emStream_ReadShortInt(...)	\
	Macro(Macro2(__VA_ARGS__, emStream_ReadShortIntVal, emStream_ReadShortIntRet)(__VA_ARGS__))

#define	emStream_ReadUshortIntRet(stream)	\
	({	\
		emStream_ReadBytesInt(stream, emType.Ushort[0], 2);	\
		emType.Ushort[0];	\
	})

#define	emStream_ReadUshortIntVal(stream, ushort_var)	\
	emStream_ReadBytesInt(stream, ushort_var, 2)

#define	emStream_ReadUshortInt(...)	\
	Macro(Macro2(__VA_ARGS__, emStream_ReadUshortIntVal, emStream_ReadUshortIntRet)(__VA_ARGS__))

#define	emStream_ReadLongIntRet(stream)	\
	({	\
		emStream_ReadBytesInt(stream, emType.Long[0], 4);	\
		emType.Long[0];	\
	})

#define	emStream_ReadLongIntVal(stream, long_var)	\
	emStream_ReadBytesInt(stream, long_var, 4)

#define	emStream_ReadLongInt(...)	\
	Macro(Macro2(__VA_ARGS__, emStream_ReadLongIntVal, emStream_ReadLongIntRet)(__VA_ARGS__))

#define	emStream_ReadUlongIntRet(stream)	\
	({	\
		emStream_ReadBytesInt(stream, emType.Ulong[0], 4);	\
		emType.Ulong[0];	\
	})

#define	emStream_ReadUlongIntVal(stream, ulong_var)	\
	emStream_ReadBytesInt(stream, ulong_var, 4)

#define	emStream_ReadUlongInt(...)	\
	Macro(Macro2(__VA_ARGS__, emStream_ReadUlongIntVal, emStream_ReadUlongIntRet)(__VA_ARGS__))

#define	emStream_ReadCharInt	\
	emStream_ReadByteInt

#define	emStream_ReadInt8Int	\
	emStream_ReadSbyteInt

#define	emStream_ReadUint8Int	\
	emStream_ReadByteInt

#define	emStream_ReadInt16Int	\
	emStream_ReadShortInt

#define	emStream_ReadUint16Int	\
	emStream_ReadUshortInt

#define	emStream_ReadInt32Int	\
	emStream_ReadLongInt

#define	emStream_ReadUint32Int	\
	emStream_ReadUlongInt

#if embd_Platform == emdb_PlatformPC
#define	emStream_ReadIntInt	\
	emStream_ReadLongInt

#define	emStream_ReadUintInt	\
	emStream_ReadUlongInt
#else
#define	emStream_ReadIntInt	\
	emStream_ReadShortInt

#define	emStream_ReadUintInt	\
	emStream_ReadUshortInt
#endif

#define	emStream_ReadInt64IntRet(stream)	\
	({	\
		emStream_ReadBytesInt(stream, emType.Int64[0], 8);	\
		emType.Int64[0];	\
	})

#define	emStream_ReadInt64IntVal(stream, int64_var)	\
	emStream_ReadBytesInt(stream, int64_var, 8)

#define	emStream_ReadInt64Int(...)	\
	Macro(Macro2(__VA_ARGS__, emStream_ReadInt64IntVal, emStream_ReadInt64IntRet)(__VA_ARGS__))

#define	emStream_ReadUint64IntRet(stream)	\
	({	\
		emStream_ReadBytesInt(stream, emType.Uint64[0], 8);	\
		emType.Uint64[0];	\
	})

#define	emStream_ReadUint64IntVal(stream, uint64_var)	\
	emStream_ReadBytesInt(stream, uint64_var, 8)

#define	emStream_ReadUint64Int(...)	\
	Macro(Macro2(__VA_ARGS__, emStream_ReadUint64IntVal, emStream_ReadUint64IntRet)(__VA_ARGS__))

#define	emStream_ReadFloatIntRet(stream)	\
	({	\
		emStream_ReadBytesInt(stream, emType.Float[0], 4);	\
		emType.Float[0];	\
	})

#define	emStream_ReadFloatIntVal(stream, float_var)	\
	emStream_ReadBytesInt(stream, float_var, 4)

#define	emStream_ReadFloatInt(...)	\
	Macro(Macro2(__VA_ARGS__, emStream_ReadFloatIntVal, emStream_ReadFloatIntRet)(__VA_ARGS__))

#define	emStream_ReadDoubleIntRet(stream)	\
	({	\
		emStream_ReadBytesInt(stream, emType.Double[0], 8);	\
		emType.Double[0];	\
	})

#define	emStream_ReadDoubleIntVal(stream, double_var)	\
	emStream_ReadBytesInt(stream, double_var, 8)

#define	emStream_ReadDoubleInt(...)	\
	Macro(Macro2(__VA_ARGS__, emStream_ReadDoubleIntVal, emStream_ReadDoubleIntRet)(__VA_ARGS__))

#define	emStream_ReadByteVal(stream, byte_var)	\
	do{	\
		emTask_WaitWhile(emStream_GetAvail(stream) < 1);	\
		(byte_var) = (stream).Data[(stream).Front];	\
		(stream).Front = ((stream).Front + 1) & (stream).Max;	\
		(stream).Count--;	\
	}while(0)

#define	emStream_ReadByteRet(stream)	\
	({	\
		emStream_ReadByteVal(stream, emType.Byte[0]);	\
		emType.Byte[0];	\
	})

#define	emStream_ReadByte(...)	\
	Macro(Macro2(__VA_ARGS__, emStream_ReadByteVal, emStream_ReadByteRet)(__VA_ARGS__))

#define	emStream_ReadSbyteVal(stream, sbyte_var)	\
	do{	\
		emTask_WaitWhile(emStream_GetAvail(stream) < 1);	\
		(sbyte_var) = (sbyte)((stream).Data[(stream).Front]);	\
		(stream).Front = ((stream).Front + 1) & (stream).Max;	\
		(stream).Count--;	\
	}while(0)

#define	emStream_ReadSbyteRet(stream)	\
	({	\
		emStream_ReadByteVal(stream, emType.Sbyte[0]);	\
		emType.Sbyte[0];	\
	})

#define	emStream_ReadSbyte(...)	\
	Macro(Macro2(__VA_ARGS__, emStream_ReadSbyteVal, emStream_ReadSbyteRet)(__VA_ARGS__))

#define	emStream_ReadShortRet(stream)	\
	({	\
		emStream_ReadBytes(stream, emType.Short[0], 2);	\
		emType.Short[0];	\
	})

#define	emStream_ReadShortVal(stream, short_var)	\
	emStream_ReadBytes(stream, short_var, 2)

#define	emStream_ReadShort(...)	\
	Macro(Macro2(__VA_ARGS__, emStream_ReadShortVal, emStream_ReadShortRet)(__VA_ARGS__))

#define	emStream_ReadUshortRet(stream)	\
	({	\
		emStream_ReadBytes(stream, emType.Ushort[0], 2);	\
		emType.Ushort[0];	\
	})

#define	emStream_ReadUshortVal(stream, ushort_var)	\
	emStream_ReadBytes(stream, ushort_var, 2)

#define	emStream_ReadUshort(...)	\
	Macro(Macro2(__VA_ARGS__, emStream_ReadUshortVal, emStream_ReadUshortRet)(__VA_ARGS__))

#define	emStream_ReadLongRet(stream)	\
	({	\
		emStream_ReadBytes(stream, emType.Long[0], 4);	\
		emType.Long[0];	\
	})

#define	emStream_ReadLongVal(stream, long_var)	\
	emStream_ReadBytes(stream, long_var, 4)

#define	emStream_ReadLong(...)	\
	Macro(Macro2(__VA_ARGS__, emStream_ReadLongVal, emStream_ReadLongRet)(__VA_ARGS__))

#define	emStream_ReadUlongRet(stream)	\
	({	\
		emStream_ReadBytes(stream, emType.Ulong[0], 4);	\
		emType.Ulong[0];	\
	})

#define	emStream_ReadUlongVal(stream, ulong_var)	\
	emStream_ReadBytes(stream, ulong_var, 4)

#define	emStream_ReadUlong(...)	\
	Macro(Macro2(__VA_ARGS__, emStream_ReadUlongVal, emStream_ReadUlongRet)(__VA_ARGS__))

#define	emStream_ReadChar	\
	emStream_ReadByte

#define	emStream_ReadInt8	\
	emStream_ReadSbyte

#define	emStream_ReadUint8	\
	emStream_ReadByte

#define	emStream_ReadInt16	\
	emStream_ReadShort

#define	emStream_ReadUint16	\
	emStream_ReadUshort

#define	emStream_ReadInt32	\
	emStream_ReadLong

#define	emStream_ReadUint32	\
	emStream_ReadUlong

#if embd_Platform == emdb_PlatformPC
#define	emStream_ReadInt	\
	emStream_ReadLong

#define	emStream_ReadUint	\
	emStream_ReadUlong
#else
#define	emStream_ReadInt	\
	emStream_ReadShort

#define	emStream_ReadUint	\
	emStream_ReadUshort
#endif

#define	emStream_ReadInt64Ret(stream)	\
	({	\
		emStream_ReadBytes(stream, emType.Int64[0], 8);	\
		emType.Int64[0];	\
	})

#define	emStream_ReadInt64Val(stream, int64_var)	\
	emStream_ReadBytes(stream, int64_var, 8)

#define	emStream_ReadInt64(...)	\
	Macro(Macro2(__VA_ARGS__, emStream_ReadInt64Val, emStream_ReadInt64Ret)(__VA_ARGS__))

#define	emStream_ReadUint64Ret(stream)	\
	({	\
		emStream_ReadBytes(stream, emType.Uint64[0], 8);	\
		emType.Uint64[0];	\
	})

#define	emStream_ReadUint64Val(stream, uint64_var)	\
	emStream_ReadBytes(stream, uint64_var, 8)

#define	emStream_ReadUint64(...)	\
	Macro(Macro2(__VA_ARGS__, emStream_ReadUint64Val, emStream_ReadUint64Ret)(__VA_ARGS__))

#define	emStream_ReadFloatRet(stream)	\
	({	\
		emStream_ReadBytes(stream, emType.Float[0], 4);	\
		emType.Float[0];	\
	})

#define	emStream_ReadFloatVal(stream, float_var)	\
	emStream_ReadBytes(stream, float_var, 4)

#define	emStream_ReadFloat(...)	\
	Macro(Macro2(__VA_ARGS__, emStream_ReadFloatVal, emStream_ReadFloatRet)(__VA_ARGS__))

#define	emStream_ReadDoubleRet(stream)	\
	({	\
		emStream_ReadBytes(stream, emType.Double[0], 8);	\
		emType.Double[0];	\
	})

#define	emStream_ReadDoubleVal(stream, double_var)	\
	emStream_ReadBytes(stream, double_var, 8)

#define	emStream_ReadDouble(...)	\
	Macro(Macro2(__VA_ARGS__, emStream_ReadDoubleVal, emStream_ReadDoubleRet)(__VA_ARGS__))

#if emStream_Shorthand >= 1
#define	stream_ReadByteInt		emStream_ReadByteInt
#define	stream_ReadSbyteInt		emStream_ReadSbyteInt
#define	stream_ReadShortInt		emStream_ReadShortInt
#define	stream_ReadUshortInt	emStream_ReadUshortInt
#define	stream_ReadLongInt		emStream_ReadLongInt
#define	stream_ReadUlongInt		emStream_ReadUlongInt
#define	stream_ReadCharInt		emStream_ReadCharInt
#define	stream_ReadInt8Int		emStream_ReadInt8Int
#define	stream_ReadUint8Int		emStream_ReadUint8Int
#define	stream_ReadInt16Int		emStream_ReadInt16Int
#define	stream_ReadUint16Int	emStream_ReadUint16Int
#define	stream_ReadInt32Int		emStream_ReadInt32Int
#define	stream_ReadUint32Int	emStream_ReadUint32Int
#define	stream_ReadIntInt		emStream_ReadIntInt
#define	stream_ReadUintInt		emStream_ReadUintInt
#define	stream_ReadInt64Int		emStream_ReadInt64Int
#define	stream_ReadUint64Int	emStream_ReadUint64Int
#define	stream_ReadFloatInt		emStream_ReadFloatInt
#define	stream_ReadDoubleInt	emStream_ReadDoubleInt
#define	stream_ReadByte			emStream_ReadByte
#define	stream_ReadSbyte		emStream_ReadSbyte
#define	stream_ReadShort		emStream_ReadShort
#define	stream_ReadUshort		emStream_ReadUshort
#define	stream_ReadLong			emStream_ReadLong
#define	stream_ReadUlong		emStream_ReadUlong
#define	stream_ReadChar			emStream_ReadChar
#define	stream_ReadInt8			emStream_ReadInt8
#define	stream_ReadUint8		emStream_ReadUint8
#define	stream_ReadInt16		emStream_ReadInt16
#define	stream_ReadUint16		emStream_ReadUint16
#define	stream_ReadInt32		emStream_ReadInt32
#define	stream_ReadUint32		emStream_ReadUint32
#define	stream_ReadInt			emStream_ReadInt
#define	stream_ReadUint			emStream_ReadUint
#define	stream_ReadInt64		emStream_ReadInt64
#define	stream_ReadUint64		emStream_ReadUint64
#define	stream_ReadFloat		emStream_ReadFloat
#define	stream_ReadDouble		emStream_ReadDouble
#endif

#if	emStream_Shorthand >= 2
#define	stmReadByteInt			emStream_ReadByteInt
#define	stmReadSbyteInt			emStream_ReadSbyteInt
#define	stmReadShortInt			emStream_ReadShortInt
#define	stmReadUshortInt		emStream_ReadUshortInt
#define	stmReadLongInt			emStream_ReadLongInt
#define	stmReadUlongInt			emStream_ReadUlongInt
#define	stmReadCharInt			emStream_ReadCharInt
#define	stmReadInt8Int			emStream_ReadInt8Int
#define	stmReadUint8Int			emStream_ReadUint8Int
#define	stmReadInt16Int			emStream_ReadInt16Int
#define	stmReadUint16Int		emStream_ReadUint16Int
#define	stmReadInt32Int			emStream_ReadInt32Int
#define	stmReadUint32Int		emStream_ReadUint32Int
#define	stmReadIntInt			emStream_ReadIntInt
#define	stmReadUintInt			emStream_ReadUintInt
#define	stmReadInt64Int			emStream_ReadInt64Int
#define	stmReadUint64Int		emStream_ReadUint64Int
#define	stmReadFloatInt			emStream_ReadFloatInt
#define	stmReadDoubleInt		emStream_ReadDoubleInt
#define	stmReadByte				emStream_ReadByte
#define	stmReadSbyte			emStream_ReadSbyte
#define	stmReadShort			emStream_ReadShort
#define	stmReadUshort			emStream_ReadUshort
#define	stmReadLong				emStream_ReadLong
#define	stmReadUlong			emStream_ReadUlong
#define	stmReadChar				emStream_ReadChar
#define	stmReadInt8				emStream_ReadInt8
#define	stmReadUint8			emStream_ReadUint8
#define	stmReadInt16			emStream_ReadInt16
#define	stmReadUint16			emStream_ReadUint16
#define	stmReadInt32			emStream_ReadInt32
#define	stmReadUint32			emStream_ReadUint32
#define	stmReadInt				emStream_ReadInt
#define	stmReadUint				emStream_ReadUint
#define	stmReadInt64			emStream_ReadInt64
#define	stmReadUint64			emStream_ReadUint64
#define	stmReadFloat			emStream_ReadFloat
#define	stmReadDouble			emStream_ReadDouble
#endif



// Function:
// ReadString(stream, dst, len)
// 
// Reads a string of specified length (len) from the stream. If the stream does
// not have sufficient number of bytes available, then the current task/thread
// will be blocked until sufficient bytes are not available. If this is not
// desirable then GetAvail() can be used to check the number of bytes available
// in stream, and then accordingly choose to read or do something else. When
// reading a stream from inside an interrupt, use ReadStringInt(), instead of
// ReadString(). ReadStringInt() directly exits if sufficient bytes are not
// available in the stream.
// 
// Parameters:
// stream:	the stream from which a set of bytes is to be read
// dst:		the variable to which the string is to be stored
// len:		size of string to be read from stream
// 
// Returns:
// nothing
//
#define	emStream_ReadStringInt(stream, dst, len)	\
	do{	\
		emStream_ReadBytesInt(stream, dst, len);	\
		*(((byte*)(&(dst))) + len) = 0;	\
	}while(0)

#define	emStream_ReadString(stream, dst, len)	\
	do{	\
		emStream_ReadBytes(stream, dst, len);	\
		*(((byte*)(&(dst))) + len) = 0;	\
	}while(0)

#if emStream_Shorthand >= 1
#define	stream_ReadStringInt	emStream_ReadStringInt
#define	stream_ReadString		emStream_ReadString
#endif

#if	emStream_Shorthand >= 2
#define	stmReadStringInt		emStream_ReadStringInt
#define	stmReadString			emStream_ReadString
#endif



// Function:
// WriteBytes</Int>(stream, src, len)
// 
// Writes a set of bytes to the stream. If the stream does not have sufficient free
// space available, then the current task/thread will be blocked until sufficient
// free space is available. If this is not desirable then GetFree() can be used to
// check the amount of free space in bytes available in stream, and then accordingly
// choose to write or do something else. When writing to a stream from inside an
// interrupt, use WriteBytesInt(), instead of WriteBytes(). WriteBytesInt() directly
// exits if sufficient bytes are not free in the stream.
// 
// Parameters:
// stream:	the stream to which a set of bytes is to be written
// src:		the variable from which the bytes are to be written to stream
// len:		number of bytes to be written from stream from source (src)
// 
// Returns:
// nothing
//
#define	emStream_WriteBytesInt(stream, src, len)	\
	do{	\
		if(emStream_GetFree(stream) < (len)) break;	\
		for(emStream_LoopI = 0; emStream_LoopI < (len); emStream_LoopI++)	\
		{	\
			(stream).Data[(stream).Rear] = *(((byte*)(&(src))) + emStream_LoopI);	\
			(stream).Rear = ((stream).Rear + 1) & (stream).Max;	\
		}	\
		(stream).Count += (len);	\
	}while(0)

#define	emStream_WriteBytes(stream, src, len)	\
	do{	\
		for(emStream_LoopI = 0; emStream_LoopI < (len); emStream_LoopI++)	\
		{	\
			emTask_WaitWhile(emStream_GetFree(stream) < 1, byte, emStream_LoopI);	\
			(stream).Data[(stream).Rear] = *(((byte*)(&(src))) + emStream_LoopI);	\
			(stream).Rear = ((stream).Rear + 1) & (stream).Max;	\
			(stream).Count++;	\
		}	\
	}while(0)

#if emStream_Shorthand >= 1
#define	stream_WriteBytesInt	emStream_WriteBytesInt
#define	stream_WriteBytes		emStream_WriteBytes
#endif

#if	emStream_Shorthand >= 2
#define	stmWriteBytesInt		emStream_WriteBytesInt
#define	stmWriteBytes			emStream_WriteBytes
#endif



// Function:
// Write<Type></Int>(stream, <Type>_value)
// 
// Writes a type data to the stream. If the stream does not have sufficient free
// space (bytes) available, then the current task/thread will be blocked until
// sufficient free space is available. If this is not desirable then GetFree()
// can be used to check the amount of free space in bytes in the stream, and
// then accordingly choose to write or do something else. When writing to a
// stream from inside an interrupt, use Write<Type>Int(), instead of Write<Type>().
// Write<Type>Int() directly exits if sufficient bytes are not free in the stream.
// 
// Parameters:
// stream:	the stream to which type data will be written
// <Type>_value:	value of type data to be written
// 
// Returns:
// nothing
//
#define	emStream_WriteByteInt(stream, byte_value)	\
	do{	\
		if(emStream_GetFree(stream) < 1) break;	\
		(stream).Data[(stream).Rear] = (byte_value);	\
		(stream).Rear = ((stream).Rear + 1) & (stream).Max;	\
		(stream).Count++;	\
	}while(0)

#define	emStream_WriteSbyteInt(stream, sbyte_value)	\
	do{	\
		if(emStream_GetFree(stream) < 1) break;	\
		(stream).Data[(stream).Rear] = (byte)(sbyte_value);	\
		(stream).Rear = ((stream).Rear + 1) & (stream).Max;	\
		(stream).Count++;	\
	}while(0)

#define	emStream_WriteShortInt(stream, short_value)	\
	emStream_WriteBytesInt(stream, short_value, 2)

#define	emStream_WriteUshortInt(stream, ushort_value)	\
	emStream_WriteBytesInt(stream, ushort_value, 2)

#define	emStream_WriteLongInt(stream, long_value)	\
	emStream_WriteBytesInt(stream, long_value, 4)

#define	emStream_WriteUlongInt(stream, ulong_value)	\
	emStream_WriteBytesInt(stream, ulong_value, 2)

#define	emStream_WriteCharInt	\
	emStream_WriteByteInt

#define	emStream_WriteInt8Int	\
	emStream_WriteSbyteInt

#define	emStream_WriteUint8Int	\
	emStream_WriteByteInt

#define	emStream_WriteInt16Int	\
	emStream_WriteShortInt

#define	emStream_WriteUint16Int	\
	emStream_WriteUshortInt

#define	emStream_WriteInt32Int	\
	emStream_WriteLongInt

#define	emStream_WriteUint32Int	\
	emStream_WriteUlongInt

#if embd_Platform == embd_PlatformPC
#define	emStream_WriteIntInt	\
	emStream_WriteLongInt

#define	emStream_WriteUintInt	\
	emStream_WriteUlongInt
#else
#define	emStream_WriteIntInt	\
	emStream_WriteShortInt

#define	emStream_WriteUintInt	\
	emStream_WriteUshortInt
#endif

#define	emStream_WriteInt64Int(stream, int64_value)	\
	emStream_WriteBytesInt(stream, int64_value, 8)

#define	emStream_WriteUint64Int(stream, uint64_value)	\
	emStream_WriteBytesInt(stream, uint64_value, 8)

#define	emStream_WriteFloatInt(stream, float_value)	\
	emStream_WriteBytesInt(stream, float_value, 4)

#define	emStream_WriteDoubleInt(stream, double_value)	\
	emStream_WriteBytesInt(stream, double_value, 8)

#define	emStream_WriteByte(stream, byte_value)	\
	do{	\
		emTask_WaitWhile(emStream_GetFree(stream) < 1);	\
		(stream).Data[(stream).Rear] = (byte_value);	\
		(stream).Rear = ((stream).Rear + 1) & (stream).Max;	\
		(stream).Count++;	\
	}while(0)

#define	emStream_WriteSbyte(stream, sbyte_value)	\
	do{	\
		emTask_WaitWhile(emStream_GetFree(stream) < 1);	\
		(stream).Data[(stream).Rear] = (byte)(sbyte_value);	\
		(stream).Rear = ((stream).Rear + 1) & (stream).Max;	\
		(stream).Count++;	\
	}while(0)

#define	emStream_WriteShort(stream, short_value)	\
	emStream_WriteBytes(stream, short_value, 2)

#define	emStream_WriteUshort(stream, ushort_value)	\
	emStream_WriteBytes(stream, ushort_value, 2)

#define	emStream_WriteLong(stream, long_value)	\
	emStream_WriteBytes(stream, long_value, 4)

#define	emStream_WriteUlong(stream, ulong_value)	\
	emStream_WriteBytes(stream, ulong_value, 2)

#define	emStream_WriteChar	\
	emStream_WriteByte

#define	emStream_WriteInt8	\
	emStream_WriteSbyte

#define	emStream_WriteUint8	\
	emStream_WriteByte

#define	emStream_WriteInt16	\
	emStream_WriteShort

#define	emStream_WriteUint16	\
	emStream_WriteUshort

#define	emStream_WriteInt32	\
	emStream_WriteLong

#define	emStream_WriteUint32	\
	emStream_WriteUlong

#if embd_Platform == embd_PlatformPC
#define	emStream_WriteInt	\
	emStream_WriteLong

#define	emStream_WriteUint	\
	emStream_WriteUlong
#else
#define	emStream_WriteInt	\
	emStream_WriteShort

#define	emStream_WriteUint	\
	emStream_WriteUshort
#endif

#define	emStream_WriteInt64(stream, int64_value)	\
	emStream_WriteBytes(stream, int64_value, 8)

#define	emStream_WriteUint64(stream, uint64_value)	\
	emStream_WriteBytes(stream, uint64_value, 8)

#define	emStream_WriteFloat(stream, float_value)	\
	emStream_WriteBytes(stream, float_value, 4)

#define	emStream_WriteDouble(stream, double_value)	\
	emStream_WriteBytes(stream, double_value, 8)

#if emStream_Shorthand >= 1
#define	stream_WriteByteInt		emStream_WriteByteInt
#define	stream_WriteSbyteInt	emStream_WriteSbyteInt
#define	stream_WriteShortInt	emStream_WriteShortInt
#define	stream_WriteUshortInt	emStream_WriteUshortInt
#define	stream_WriteLongInt		emStream_WriteLongInt
#define	stream_WriteUlongInt	emStream_WriteUlongInt
#define	stream_WriteCharInt		emStream_WriteCharInt
#define	stream_WriteInt8Int		emStream_WriteInt8Int
#define	stream_WriteUint8Int	emStream_WriteUint8Int
#define	stream_WriteInt16Int	emStream_WriteInt16Int
#define	stream_WriteUint16Int	emStream_WriteUint16Int
#define	stream_WriteInt32Int	emStream_WriteInt32Int
#define	stream_WriteUint32Int	emStream_WriteUint32Int
#define	stream_WriteIntInt		emStream_WriteIntInt
#define	stream_WriteUintInt		emStream_WriteUintInt
#define	stream_WriteInt64Int	emStream_WriteInt64Int
#define	stream_WriteUint64Int	emStream_WriteUint64Int
#define	stream_WriteFloatInt	emStream_WriteFloatInt
#define	stream_WriteDoubleInt	emStream_WriteDoubleInt
#define	stream_WriteByte		emStream_WriteByte
#define	stream_WriteSbyte		emStream_WriteSbyte
#define	stream_WriteShort		emStream_WriteShort
#define	stream_WriteUshort		emStream_WriteUshort
#define	stream_WriteLong		emStream_WriteLong
#define	stream_WriteUlong		emStream_WriteUlong
#define	stream_WriteChar		emStream_WriteChar
#define	stream_WriteInt8		emStream_WriteInt8
#define	stream_WriteUint8		emStream_WriteUint8
#define	stream_WriteInt16		emStream_WriteInt16
#define	stream_WriteUint16		emStream_WriteUint16
#define	stream_WriteInt32		emStream_WriteInt32
#define	stream_WriteUint32		emStream_WriteUint32
#define	stream_WriteInt			emStream_WriteInt
#define	stream_WriteUint		emStream_WriteUint
#define	stream_WriteInt64		emStream_WriteInt64
#define	stream_WriteUint64		emStream_WriteUint64
#define	stream_WriteFloat		emStream_WriteFloat
#define	stream_WriteDouble		emStream_WriteDouble
#endif

#if	emStream_Shorthand >= 2
#define	stmWriteByteInt			emStream_WriteByteInt
#define	stmWriteSbyteInt		emStream_WriteSbyteInt
#define	stmWriteShortInt		emStream_WriteShortInt
#define	stmWriteUshortInt		emStream_WriteUshortInt
#define	stmWriteLongInt			emStream_WriteLongInt
#define	stmWriteUlongInt		emStream_WriteUlongInt
#define	stmWriteCharInt			emStream_WriteCharInt
#define	stmWriteInt8Int			emStream_WriteInt8Int
#define	stmWriteUint8Int		emStream_WriteUint8Int
#define	stmWriteInt16Int		emStream_WriteInt16Int
#define	stmWriteUint16Int		emStream_WriteUint16Int
#define	stmWriteInt32Int		emStream_WriteInt32Int
#define	stmWriteUint32Int		emStream_WriteUint32Int
#define	stmWriteIntInt			emStream_WriteIntInt
#define	stmWriteUintInt			emStream_WriteUintInt
#define	stmWriteInt64Int		emStream_WriteInt64Int
#define	stmWriteUint64Int		emStream_WriteUint64Int
#define	stmWriteFloatInt		emStream_WriteFloatInt
#define	stmWriteDoubleInt		emStream_WriteDoubleInt
#define	stmWriteByte			emStream_WriteByte
#define	stmWriteSbyte			emStream_WriteSbyte
#define	stmWriteShort			emStream_WriteShort
#define	stmWriteUshort			emStream_WriteUshort
#define	stmWriteLong			emStream_WriteLong
#define	stmWriteUlong			emStream_WriteUlong
#define	stmWriteChar			emStream_WriteChar
#define	stmWriteInt8			emStream_WriteInt8
#define	stmWriteUint8			emStream_WriteUint8
#define	stmWriteInt16			emStream_WriteInt16
#define	stmWriteUint16			emStream_WriteUint16
#define	stmWriteInt32			emStream_WriteInt32
#define	stmWriteUint32			emStream_WriteUint32
#define	stmWriteInt				emStream_WriteInt
#define	stmWriteUint			emStream_WriteUint
#define	stmWriteInt64			emStream_WriteInt64
#define	stmWriteUint64			emStream_WriteUint64
#define	stmWriteFloat			emStream_WriteFloat
#define	stmWriteDouble			emStream_WriteDouble
#endif



#endif
