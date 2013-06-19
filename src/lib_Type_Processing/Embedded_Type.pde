/*
----------------------------------------------------------------------------------------
    Embedded_Type: Library header file for Ardino
    File: Embedded_Type.pde

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
    Embedded_Type is a generic type conversion library for Arduino/Processing/Java/C/C++.
    It has been developed mainly for simplifying the process of writing wireless communication
    programs on Arduino and Processing. To use it (in Arduino), copy the directory, this file
    is in to arduino_root_folder/libraries/. Then restart Arduino, goto Sketch->Add Library->
    Embedded_Type.
*/


// Requisite classes
import java.nio.*;



// shorthand datatypes
public class ulong
{
  public long[] Long;
  
  public ulong()
  {
    Long = new long[2];
  }
}



// internal buffer
public byte[]	TypeBuffer = new byte[16];



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
public byte GetBit(byte[] src, int off, int bit_no)
{
  return (src[off + (bit_no >> 3)] >> (bit_no & 7)) & 1;
}

public byte GetBit(int off, int bit_no)
{
  GetBit(TypeBuffer, off, bit_no);
}



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
public byte GetNibble(byte[] src, int off, int nibble_no)
{
  return (src[off + (nibble_no >> 1)] >> ((nibble_no & 1) << 2)) & 0xF;
}

public byte GetNibble(int off, int nibble_no)
{
  return GetNibble(TypeBuffer, off, nibble_no);
}



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
public char GetChar(byte[] src, int off)
{
  return (char)src[off];
}

public char GetChar(int off)
{
  return (char)TypeBuffer[off];
}

public byte GetByte(byte[] src, int off)
{
  return src[off];
}

public byte GetByte(int off)
{
  return TypeBuffer[off];
}

public boolean GetBoolean(byte[] src, int off)
{
  return (src[off] != 0);
}

public boolean GetBoolean(int off)
{
  return (TypeBuffer[off] != 0);
}

public short GetShort(byte[] src, int off)
{
  return ByteBuffer.wrap(src, off, 2).order(ByteOrder.LITTLE_ENDIAN).getShort();
}

public short GetShort(int off)
{
  return GetShort(TypeBuffer, off);
}

public int GetUshort(byte[] src, int off)
{
  int ushort = GetShort(src, off);
  return (ushort > 0)? ushort : (0x10000 + ushort); 
}

public int GetUshort(int off)
{
  return GetUshort(TypeBuffer, off);
}

public short GetInt16(byte[] src, int off)
{
  return GetShort(src, off);
}

public short GetInt16(int off)
{
  return GetShort(TypeBuffer, off);
}

public int GetUint16(byte[] src, int off)
{
  return GetUshort(src, off);
}

public int GetUint16(int off)
{
  return GetUshort(TypeBuffer, off);
}

public int GetInt(byte[] src, int off)
{
  return ByteBuffer.wrap(dat, off, 4).order(ByteOrder.LITTLE_ENDIAN).getInt();
}

public int GetInt(int off)
{
  return GetInt(TypeBuffer, off);
}

public long GetUint(byte[] src, int off)
{
  long uint = GetInt(src, off);
  return (uint > 0)? uint : (0x100000000 + uint); 
}

public long GetUint(int off)
{
  return GetUint(TypeBuffer, off);
}

public int GetLong32(byte[] src, int off)
{
  return GetInt(src, off);
}

public int GetLong32(int off)
{
  return GetInt(TypeBuffer, off);
}

public long GetUlong32(byte[] src, int off)
{
  return GetUint(src, off);
}

public long GetUlong32(int off)
{
  return GetUint(TypeBuffer, off);
}

public long GetLong(byte[] src, int off)
{
  return ByteBuffer.wrap(src, off, 8).order(ByteOrder.LITTLE_ENDIAN).getLong();
}

public long GetLong(int off)
{
  return GetLong(TypeBuffer, off);
}

public ulong GetUlong(byte[] src, int off)
{
  ulong Ulong = new ulong();
  ulong.Long[0] = GetUint(src, off);
  ulong.Long[1] = GetUint(src, off+4);
  return ulong;
}

public ulong GetLong(int off)
{
  return GetUlong(TypeBuffer, off);
}

public long GetLong64(byte[] src, int off)
{
  return GetLong(src, off);
}

public long GetLong64(int off)
{
  return GetLong(TypeBuffer, off);
}

public ulong GetUlong64(byte[] src, int off)
{
  return GetUlong(src, off);
}

public ulong GetUlong64(int off)
{
  return GetUlong(TypeBuffer, off);
}

public float GetFloat(byte[] src, int off)
{
  return ByteBuffer.wrap(src, off, 4).order(ByteOrder.LITTLE_ENDIAN).getFloat();
}

public float GetFloat(int off)
{
  return GetFloat(TypeBuffer, off);
}

public double GetDouble(byte[] src, int off)
{
  return ByteBuffer.wrap(src, off, 8).order(ByteOrder.LITTLE_ENDIAN).getDouble();
}

public double GetDouble(int off)
{
  return GetDouble(TypeBuffer, off);
}



// Function:
// GetString(dst, sz, src, off, opt)
// GetString(dst, sz, off, opt)
// 
// Returns the string at the specified source address with 
// offset (src + off). If source address (src) is not specified,
// then this library's internal buffer is used as the source.
// 
// Parameters:
// dst:      destination address where the string is stored
// sz:       size of destination in bytes (max. length of string-1)
// src:      the base address of stored data
// off:      offset of the stored string
// opt:      options for string fetching (TYPE_ZEROED_STRING, TYPE_LENGTH_STRING)
// 
// Returns:
// <type>_value:  the value of the specified <type>
// 
final static int TYPE_ZEROED_STRING = 0;

final static int TYPE_LENGTH_STRING = 1;

public String GetString(String dst, int sz, byte[] src, int off, int opt)
{
  int i, len;
  if(opt == TYPE_LENGTH_STRING)
  {
    len = src[off];
    off++;
  }
  else
  {
    for(i=off; i<src.length && src[i] != 0; i++);
    len = i - off;
  }
  len = (len <= sz)? len : sz;
  dst = new String(src, off, len);
  return dst;
}



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
public void PutBit(byte[] dst, int off, int bit_no, int bit_value)
{
  int indx = off + (bit_no >> 3);
  dst[indx] = (dst[indx] & ~(1 << (bit_no & 7))) | (bit_value << (bit_no & 7));
}

public void PutBit(int off, int bit_no, int bit_value)
{
  PutBit(TypeBuffer, off, bit_no, bit_value);
}



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
public void PutNibble(byte[] dst, int off, int nibble_no, int nibble_value)
{
  int indx = off + (nibble_no >> 1);
  dst[indx] = (dst[indx] & ~(0xF << ((nibble_no & 1) << 2))) | (nibble_value << ((nibble_no & 1) << 2));
}

public void PutNibble(int off, int nibble_no, int nibble_value)
{
  PutNibble(TypeBuffer, off, nibble_no, nibble_value);
}



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
public void PutChar(byte[] dst, int off, char value)
{
  dst[off] = (byte)value;
}

public void PutChar(int off, char value)
{
  TypeBuffer[off] = (byte)value;
}

public void PutByte(byte[] dst, int off, byte value)
{
  dst[off] = value;
}

public void PutByte(int off, byte value)
{
  TypeBuffer[off] = value;
}

public void PutBoolean(byte[] dst, int off, boolean value)
{
  dst[off] = (value)? 1 : 0;
}

public void PutBoolean(int off, boolean value)
{
  TypeBuffer[off] = (value)? 1 : 0;
}

public void PutShort(byte[] dst, int off, short value)
{
  ByteBuffer b = ByteBuffer.allocate(2).order(ByteOrder.LITTLE_ENDIAN).putShort(value);
  b.position(0); b.get(dst, off, 2);
}

public void PutShort(int off, short value)
{
  PutShort(TypeBuffer, off, value);
}

public void PutUshort(byte[] dst, int off, int value)
{
  ByteBuffer b = ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN).putInt(value);
  b.position(0); b.get(dst, off, 2);
}

public void PutUshort(int off, int value)
{
  PutUshort(TypeBuffer, off, value);
}

public void PutInt16(byte[] dst, int off, short value)
{
  PutShort(dst, off, value);
}

public void PutInt16(int off, short value)
{
  PutShort(TypeBuffer, off, value);
}

public void PutUint16(byte[] dst, int off, int value)
{
  PutUshort(dst, off, value);
}

public void PutUint16(int off, int value)
{
  PutUshort(TypeBuffer, off, value);
}

public void PutInt(byte[] dst, int off, int value)
{
  ByteBuffer b = ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN).putInt(value);
  b.position(0); b.get(dst, off, 4);
}

public void PutInt(int off, int value)
{
  PutInt(TypeBuffer, off, value);
}

public void PutUint(byte[] dst, int off, long value)
{
  ByteBuffer b = ByteBuffer.allocate(8).order(ByteOrder.LITTLE_ENDIAN).putLong(value);
  b.position(0); b.get(dst, off, 4);
}

public void PutUint(int off, int value)
{
  PutUint(TypeBuffer, off, value);
}

public void PutLong32(byte[] dst, int off, int value)
{
  PutInt(dst, off, value);
}

public void PutLong32(int off, int value)
{
  PutInt(TypeBuffer, off, value);
}

public void PutUlong32(byte[] dst, int off, long value)
{
  PutUint(dst, off, value);
}

public void PutUlong32(int off, long value)
{
  PutUlong32(TypeBuffer, off, value);
}

public void PutLong(byte[] dst, int off, long value)
{
  ByteBuffer b = ByteBuffer.allocate(8).order(ByteOrder.LITTLE_ENDIAN).putLong(value);
  b.position(0); b.get(dst, off, 8);
}

public void PutLong(int off, long value)
{
  PutLong(TypeBuffer, off, value);
}

public void PutUlong(byte[] dst, int off, ulong value)
{
  PutUint(dst, off, value.Long[0]);
  PutUint(dst, off+4, value.Long[1]);
}

public void PutUlong(int off, ulong value)
{
  PutUlong(TypeBuffer, off, value);
}

public void PutLong64(byte[] dst, int off, long value)
{
  PutLong(dst, off, value);
}

public void PutLong64(int off, long value)
{
  PutLong(TypeBuffer, off, value);
}

public void PutUlong64(byte[] dst, int off, ulong value)
{
  PutUlong(dst, off, value);
}

public void PutUlong64(int off, ulong value)
{
  PutUlong(TypeBuffer, off, value);
}

public void PutFloat(byte[] dst, int off, float value)
{
  ByteBuffer b = ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN).putFloat(value);
  b.position(0); b.get(dst, off, 4);
}

public void PutFloat(int off, float value)
{
  PutFloat(TypeBuffer, off, value);
}

public void PutDouble(byte[] dst, int off, double value)
{
  ByteBuffer b = ByteBuffer.allocate(8).order(ByteOrder.LITTLE_ENDIAN).putDouble(value);
  b.position(0); b.get(dst, off, 8);
}

public void PutDouble(int off, double value)
{
  PutDouble(TypeBuffer, off, value);
}

public void PutString(byte[] dst, int off, String value, int opt)
{
}

#define	PutString(...)	\
	Macro(PutType(string, __VA_ARGS__))



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

// ToString?


// Function:
// DoReverse(src, off, len)
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
// <type>_value:	the value of the (bigger) assembled data type
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
// <type>_value:	the summed value
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

#define	GetUintSum			GetUshortSum



// Function:
// PutHexFromBin(dst, dst_off, src, src_off, len, opt)
// 
// Stores hexadecimal string of the soure binary data (src + src_off)
// of specified length (len) at the destination address (dst + dst_off).
// The options (opt) specify how the conversion is to be performed,
// and it takes as input a set of flags. If source base address is
// not specified, this library's internal buffer is assumed as the
// source base address. Destination address (dst + dst_off) is to be
// specified always, which is where the converted hex string will be
// stored.
// 
// Parameters:
// dst:		the base address of destination
// dst_off:	the destination offset where the hex string will be stored (dst + dst_off)
// src:		the base address of source binary data
// src_off:	offset to the binary data to be converted (src + src_off)
// len:		length of data to be converted
// opt:		conversion options (TYPE_ADD_SPACE, TYPE_ADD_CHAR, TYPE_BIG_ENDIAN)
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
// PutBinFromHex(dst, dst_off, len, src, src_off, opt)
// 
// Stores hexadecimal string of the soure binary data (src + src_off)
// of specified length (len) at the destination address (dst + dst_off).
// The options (opt) specify how the conversion is to be performed, and
// it takes as input a set of flags. If destination base address is not 
// specified, this library's internal buffer is assumed as the destination 
// base address. Source address (src + src_off) is to be specified always, 
// which is where the original hex string is stored.
// 
// Parameters:
// dst:		the base address of destination
// dst_off:	the destination offset where the hex string will be stored (dst + dst_off)
// src:		the base address of source binary data
// src_off:	offset to the binary data to be converted (src + src_off)
// len:		length of data to be converted
// opt:		conversion options (TYPE_HAS_SPACE, TYPE_HAS_CHAR, TYPE_BIG_ENDIAN)
//
// Returns:
// nothing
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
