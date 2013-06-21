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
    Embedded_Type is a generic type conversion library for Arduino/Processing/C/C++.
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
  return (byte)((src[off + (bit_no >> 3)] >> (bit_no & 7)) & 1);
}

public byte GetBit(int off, int bit_no)
{
  return GetBit(TypeBuffer, off, bit_no);
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
// src:		the base address of stored data
// off:		offset from which nibble index starts
// nibble_no:	the index of the nibble (starts from 0)
// 
// Returns:
// nibble_value:	the value of the specified nibble (0 to 15 or 0x0 to 0xF)
// 
public byte GetNibble(byte[] src, int off, int nibble_no)
{
  return (byte)((src[off + (nibble_no >> 1)] >> ((nibble_no & 1) << 2)) & 0xF);
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
// src:		the base address of stored data
// off:		offset of the <type> value
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
  return ByteBuffer.wrap(src, off, 4).order(ByteOrder.LITTLE_ENDIAN).getInt();
}

public int GetInt(int off)
{
  return GetInt(TypeBuffer, off);
}

public long GetUint(byte[] src, int off)
{
  long uint = GetInt(src, off);
  return (uint > 0)? uint : (0x100000000L + uint); 
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
  Ulong.Long[0] = GetUint(src, off);
  Ulong.Long[1] = GetUint(src, off+4);
  return Ulong;
}

public ulong GetUlong(int off)
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
// GetString(src, off, opt)
// GetString(off, opt)
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

public String GetString(String dst, int sz, int off, int opt)
{
  return GetString(dst, sz, TypeBuffer, off, opt);
}

public String GetString(byte[] src, int off, int opt)
{
  return GetString(new String(), 1024, src, off, opt);
}

public String GetString(int off, int opt)
{
  return GetString(new String(), 1024, TypeBuffer, off, opt);
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
  dst[indx] = (byte)((dst[indx] & ~(1 << (bit_no & 7))) | (bit_value << (bit_no & 7)));
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
// dst:		  the base address of destination
// off:		  offset from which nibble index starts
// nibble_no:	  the index of the nibble (starts from 0)
// nibble_value:  the value of the specified nibble (0 to 15 or 0x0 to 0xF)
// 
// Returns:
// nothing
// 
public void PutNibble(byte[] dst, int off, int nibble_no, int nibble_value)
{
  int indx = off + (nibble_no >> 1);
  dst[indx] = (byte)((dst[indx] & ~(0xF << ((nibble_no & 1) << 2))) | (nibble_value << ((nibble_no & 1) << 2)));
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

public void PutByte(byte[] dst, int off, int value)
{
  dst[off] = (byte)value;
}

public void PutByte(int off, int value)
{
  TypeBuffer[off] = (byte)value;
}

public void PutBoolean(byte[] dst, int off, boolean value)
{
  dst[off] = (byte)((value)? 1 : 0);
}

public void PutBoolean(int off, boolean value)
{
  TypeBuffer[off] = (byte)((value)? 1 : 0);
}

public void PutShort(byte[] dst, int off, int value)
{
  ByteBuffer b = ByteBuffer.allocate(2).order(ByteOrder.LITTLE_ENDIAN).putShort((short)value);
  b.position(0); b.get(dst, off, 2);
}

public void PutShort(int off, int value)
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

public void PutInt16(byte[] dst, int off, int value)
{
  PutShort(dst, off, value);
}

public void PutInt16(int off, int value)
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
public void PutString(byte[] dst, int off, String value, int opt)
{
  if((opt & TYPE_LENGTH_STRING) > 0)
  {
    dst[off] = (byte)value.length();
    off++;
  }
  byte[] strbytes = value.getBytes();
  arrayCopy(strbytes, 0, dst, off, strbytes.length);
  if((opt & TYPE_LENGTH_STRING) == 0) dst[off + strbytes.length] = 0;
}

public void PutString(int off, String value, int opt)
{
  PutString(TypeBuffer, off, value, opt);
}



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

public byte ToNibble(int bit3, int bit2, int bit1, int bit0)
{
  return (byte)((bit3 << 3) | (bit2 << 2) | (bit1 << 1) | bit0);
}

public byte ToByte(int nibble1, int nibble0)
{
  return (byte)((nibble1 << 4) | nibble0);
}

public byte ToByte(int bit7, int bit6, int bit5, int bit4, int bit3, int bit2, int bit1, int bit0)
{
  return ToByte(ToNibble(bit7, bit6, bit5, bit4), ToNibble(bit3, bit2, bit1, bit0));
}

public char ToChar(int nibble1, int nibble0)
{
  return (char)ToByte(nibble1, nibble0);
}

public char ToChar(int bit7, int bit6, int bit5, int bit4, int bit3, int bit2, int bit1, int bit0)
{
  return (char)ToByte(bit7, bit6, bit5, bit4, bit3, bit2, bit1, bit0);
}

public short ToShort(int byte1, int byte0)
{
  TypeBuffer[0] = (byte)byte0; TypeBuffer[1] = (byte)byte1;
  return GetShort(TypeBuffer, 0);
}

public int ToUshort(int byte1, int byte0)
{
  TypeBuffer[0] = (byte)byte0; TypeBuffer[1] = (byte)byte1;
  return GetUshort(TypeBuffer, 0);
}

public short ToInt16(int byte1, int byte0)
{
  return ToShort(byte1, byte0);
}

public int ToUint16(int byte1, int byte0)
{
  return ToUshort(byte1, byte0);
}

public int ToInt(int ushort1, int ushort0)
{
  PutUshort(TypeBuffer, 0, ushort0); PutUshort(TypeBuffer, 2, ushort1);
  return GetInt(TypeBuffer, 0);
}

public int ToInt(int byte3, int byte2, int byte1, int byte0)
{
  TypeBuffer[0] = (byte)byte0; TypeBuffer[1] = (byte)byte1;
  TypeBuffer[2] = (byte)byte2; TypeBuffer[3] = (byte)byte3;
  return GetInt(TypeBuffer, 0);
}

public long ToUint(int ushort1, int ushort0)
{
  PutUshort(TypeBuffer, 0, ushort0); PutUshort(TypeBuffer, 2, ushort1);
  return GetUint(TypeBuffer, 0);
}

public long ToUint(int byte3, int byte2, int byte1, int byte0)
{
  TypeBuffer[0] = (byte)byte0; TypeBuffer[1] = (byte)byte1;
  TypeBuffer[2] = (byte)byte2; TypeBuffer[3] = (byte)byte3;
  return GetUint(TypeBuffer, 0);
}

public int ToLong32(int ushort1, int ushort0)
{
  return ToInt(ushort1, ushort0);
}

public int ToLong32(int byte3, int byte2, int byte1, int byte0)
{
  return ToInt(byte3, byte2, byte1, byte0);
}

public long ToUlong32(int ushort1, int ushort0)
{
  return ToUint(ushort1, ushort0);
}

public long ToUlong32(int byte3, int byte2, int byte1, int byte0)
{
  return ToUint(byte3, byte2, byte1, byte0);
}

public long ToLong(long uint1, long uint0)
{
  PutUint(TypeBuffer, 0, uint0); PutUint(TypeBuffer, 4, uint1);
  return GetLong(TypeBuffer, 0);
}

public long ToLong(int ushort3, int ushort2, int ushort1, int ushort0)
{
  PutUshort(TypeBuffer, 0, ushort0); PutUshort(TypeBuffer, 2, ushort1);
  PutUshort(TypeBuffer, 4, ushort2); PutUshort(TypeBuffer, 6, ushort3);
  return GetLong(TypeBuffer, 0);
}

public long ToLong(int byte7, int byte6, int byte5, int byte4, int byte3, int byte2, int byte1, int byte0)
{
  TypeBuffer[0] = (byte)byte0; TypeBuffer[1] = (byte)byte1;
  TypeBuffer[2] = (byte)byte2; TypeBuffer[3] = (byte)byte3;
  TypeBuffer[4] = (byte)byte4; TypeBuffer[5] = (byte)byte5;
  TypeBuffer[6] = (byte)byte6; TypeBuffer[7] = (byte)byte7;
  return GetLong(TypeBuffer, 0);
}

public ulong ToUlong(long uint1, long uint0)
{
  PutUint(TypeBuffer, 0, uint0); PutUint(TypeBuffer, 4, uint1);
  return GetUlong(TypeBuffer, 0);
}

public ulong ToUlong(int ushort3, int ushort2, int ushort1, int ushort0)
{
  PutUshort(TypeBuffer, 0, ushort0); PutUshort(TypeBuffer, 2, ushort1);
  PutUshort(TypeBuffer, 4, ushort2); PutUshort(TypeBuffer, 6, ushort3);
  return GetUlong(TypeBuffer, 0);
}

public ulong ToUlong(int byte7, int byte6, int byte5, int byte4, int byte3, int byte2, int byte1, int byte0)
{
  TypeBuffer[0] = (byte)byte0; TypeBuffer[1] = (byte)byte1;
  TypeBuffer[2] = (byte)byte2; TypeBuffer[3] = (byte)byte3;
  TypeBuffer[4] = (byte)byte4; TypeBuffer[5] = (byte)byte5;
  TypeBuffer[6] = (byte)byte6; TypeBuffer[7] = (byte)byte7;
  return GetUlong(TypeBuffer, 0);
}

public long ToLong64(long uint1, long uint0)
{
  return ToLong(uint1, uint0);
}

public long ToLong64(int ushort3, int ushort2, int ushort1, int ushort0)
{
  return ToLong(ushort3, ushort2, ushort1, ushort0);
}

public long ToLong64(int byte7, int byte6, int byte5, int byte4, int byte3, int byte2, int byte1, int byte0)
{
  return ToLong(byte7, byte6, byte5, byte4, byte3, byte2, byte1, byte0);
}

public ulong ToUlong64(long uint1, long uint0)
{
  return ToUlong(uint1, uint0);
}

public ulong ToUlong64(int ushort3, int ushort2, int ushort1, int ushort0)
{
  return ToUlong(ushort3, ushort2, ushort1, ushort0);
}

public ulong ToUlong64(int byte7, int byte6, int byte5, int byte4, int byte3, int byte2, int byte1, int byte0)
{
  return ToUlong(byte7, byte6, byte5, byte4, byte3, byte2, byte1, byte0);
}

public float ToFloat(int ushort1, int ushort0)
{
  PutUshort(TypeBuffer, 0, ushort0); PutUshort(TypeBuffer, 2, ushort1);
  return GetFloat(TypeBuffer, 0);
}

public float ToFloat(int byte3, int byte2, int byte1, int byte0)
{
  TypeBuffer[0] = (byte)byte0; TypeBuffer[1] = (byte)byte1;
  TypeBuffer[2] = (byte)byte2; TypeBuffer[3] = (byte)byte3;
  return GetFloat(TypeBuffer, 0);
}

public double ToDouble(long uint1, long uint0)
{
  PutUint(TypeBuffer, 0, uint0); PutUint(TypeBuffer, 4, uint1);
  return GetDouble(TypeBuffer, 0);
}

public double ToDouble(int ushort3, int ushort2, int ushort1, int ushort0)
{
  PutUshort(TypeBuffer, 0, ushort0); PutUshort(TypeBuffer, 2, ushort1);
  PutUshort(TypeBuffer, 4, ushort2); PutUshort(TypeBuffer, 6, ushort3);
  return GetDouble(TypeBuffer, 0);
}

public double ToDouble(int byte7, int byte6, int byte5, int byte4, int byte3, int byte2, int byte1, int byte0)
{
  TypeBuffer[0] = (byte)byte0; TypeBuffer[1] = (byte)byte1;
  TypeBuffer[2] = (byte)byte2; TypeBuffer[3] = (byte)byte3;
  TypeBuffer[4] = (byte)byte4; TypeBuffer[5] = (byte)byte5;
  TypeBuffer[6] = (byte)byte6; TypeBuffer[7] = (byte)byte7;
  return GetDouble(TypeBuffer, 0);
}



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
void DoReverse(byte[] src, int off, int len)
{
  byte byt;
  int bg, ed;
  for(bg=off, ed=off+len-1; bg<ed; bg++, ed--)
  {
    byt = src[bg];
    src[bg] = src[ed];
    src[ed] = byt;
  }
}

void DoReverse(int off, int len)
{
  DoReverse(TypeBuffer, off, len);
}



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
byte GetByteSum(byte[] src, int off, int len)
{
    byte sum = 0;
    for(; len>0; len--, off++)
    { sum += src[off]; }
    return sum;
}

byte GetByteSum(int off, int len)
{
  return GetByteSum(TypeBuffer, off, len);
}

int GetUshortSum(byte[] src, int off, int len)
{
    int sum = 0;
    len >>= 1;
    for(; len>0; len--, off+=2)
    { sum += GetUshort(src, off); }
    return sum & 0xFFFF;
}

int GetUshortSum(int off, int len)
{
  return GetUshortSum(TypeBuffer, off, len);
}

int GetUint16Sum(byte[] src, int off, int len)
{
  return GetUshortSum(src, off, len);
}

int GetUint16Sum(int off, int len)
{
  return GetUshortSum(TypeBuffer, off, len);
}



// Function:
// GetHexFromBin(dst, sz, src, off, len, opt)
// GetHexFromBin(src, off, len, opt)
// GetHexFromBin(dst, sz, off, len, opt)
// GetHexFromBin(off, len, opt)
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
final int TYPE_NO_SPACE = 0;

final int TYPE_ADD_SPACE = 1;

final int TYPE_HAS_SPACE = 1;

final int TYPE_NO_CHAR = 0;

final int TYPE_ADD_CHAR = 2;

final int TYPE_HAS_CHAR = 2;

final int TYPE_LITTLE_ENDIAN = 0;

final int TYPE_BIG_ENDIAN = 4;

public byte TYPE_HEX_TO_BIN(int ch)
{
  return (byte)((ch <= 0x39)? (ch - 0x30) : (ch - 0x37));
}

public byte TYPE_BIN_TO_HEX(int bn)
{
  return (byte)((bn <= 9)? (bn + 0x30) : (bn + 0x37));
}

String GetHexFromBin(String dst, int sz, byte[] src, int off, int len, int opt)
{
  byte[] xdst = new byte[sz]; int doff = 0;
  int cbin = ((opt & TYPE_BIG_ENDIAN) > 0)? off : (off + len - 1);
  int stp = ((opt & TYPE_BIG_ENDIAN) > 0)? 1 : -1;
  for(int i=0; i<len; i++, cbin+=stp)
  {
    xdst[doff] = TYPE_BIN_TO_HEX(src[cbin] >> 4); doff++;
    xdst[doff] = TYPE_BIN_TO_HEX(src[cbin] & 0xF); doff++;
    if((opt & TYPE_ADD_CHAR) > 0) { xdst[doff] = (byte)((src[cbin] < 32 || src[cbin] > 127)? '.' : src[cbin]); doff++; }
    if((opt & TYPE_ADD_SPACE) > 0) { xdst[doff] = ' '; doff++; }
  }
  dst = new String(xdst, 0, doff);
  return dst;
}

String GetHexFromBin(byte[] src, int off, int len, int opt)
{
  return GetHexFromBin(new String(), 1024, src, off, len, opt);
}

String GetHexFromBin(String dst, int sz, int off, int len, int opt)
{
  return GetHexFromBin(dst, sz, TypeBuffer, off, len, opt);
}

String GetHexFromBin(int off, int len, int opt)
{
  return GetHexFromBin(new String(), 1024, TypeBuffer, off, len, opt);
}



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
byte[] PutBinFromHex(byte[] dst, int off, int len, String src, int opt)
{
  byte[] xsrc = src.getBytes();
  int hsrc = xsrc.length - 1;
  int cbin = ((opt & TYPE_BIG_ENDIAN) > 0)?  (off + len - 1) : off;
  int stp = ((opt & TYPE_BIG_ENDIAN) > 0)? -1 : 1;
  for(int i=0; i<len; i++, cbin+=stp)
  {
    if((opt & TYPE_HAS_SPACE) > 0) hsrc--;
    if((opt & TYPE_HAS_CHAR) > 0) hsrc--;
    dst[cbin] = (hsrc < 0)? 0 : TYPE_HEX_TO_BIN(xsrc[hsrc]); hsrc--;
    dst[cbin] |= (hsrc < 0)? 0 : TYPE_HEX_TO_BIN(xsrc[hsrc]) << 4; hsrc--;
  }
  return dst;
}

byte[] PutBinFromHex(int off, int len, String src, int opt)
{
  return PutBinFromHex(TypeBuffer, off, len, src, opt);
}


