# [Embedded_Type v0.1](https://github.com/wolfram77/Embedded_Type) [![Build Status](https://raw.github.com/wolfram77/Embedded_Type/master/build.png)](https://raw.github.com/wolfram77/Embedded_Type/master/build.png)

Embedded_Type is a generic type conversion library for Arduino/Processing/C/C++.
It has been developed mainly for simplifying the process of writing wireless communication
programs on Arduino and Processing. Created and maintained by [Subhajit Sahu](https://github.com/wolfram77)



## Getting started

* [Download the latest release](https://github.com/wolfram77/Embedded_Type/archive/master.zip)
* For C/C++, directly include the header file lib_CPP/Embedded_Type.h in your C/C++ program.
* For Arduino, copy the directory lib_Arduino/Embedded_Type to arduino_root_directory/libraries/
* For Processing, copy the file lib_Processing/Embedded_Type.pde to your sketch.



## Using it

### Constants

* `null`			Null Pointer
* `TRUE`			boolean true
* `FALSE`			boolean false


### Datatypes

* `bool` | `boolean`		8bits boolean
* `sbyte` | `byte`		8bits byte
* `short` | `ushort`		16bits short
* `int16` | `uint16`		16bits int
* `int` | `uint`		platform dependent int
* `long32` | `ulong32`		32bits long
* `long` | `ulong`		platform dependent long
* `long64` | `ulong64`		64bits long
* `string`			string (use String in Processing)



## Internal Buffer

Embedded_Type has an internal buffer used by it for type conversions.
It can also be used as:

`TypeBuffer.<Type>[<index>]`

where, `Type` is the name of a datatype, but starts with a capital character
as `Int` for `int` datatype.



## Functions

Embedded_Type has 7 types of functions:
(click to jump to)
* [`Get<Type>`](https://github.com/wolfram77/Embedded_Type/blob/master/README.md#gettype-functions):	obtain a datatype from buffer
* [`Put<Type>`](https://github.com/wolfram77/Embedded_Type/edit/master/README.md#puttype-functions):	store a datatype onto buffer
* [`To<Type>`](https://github.com/wolfram77/Embedded_Type/edit/master/README.md#totype-functions):	assemble smaller datatypes to a bigger one
* [`Do<Action>`](https://github.com/wolfram77/Embedded_Type/edit/master/README.md#doaction-functions): performs an action directly on the buffer (buffer is modified)
* [`Get<Type><Action>`](https://github.com/wolfram77/Embedded_Type/edit/master/README.md#gettypeaction-functions): obtain the result of action performed on the buffer (buffer remains unchaged)
* [`Get<Type1>From<Type2>`](https://github.com/wolfram77/Embedded_Type/edit/master/README.md#gettype1fromtype2-functions): obtain a type1 data from another type2 data
* [`Put<Type1>From<Type2>`](https://github.com/wolfram77/Embedded_Type/edit/master/README.md#puttype1fromtype2-functions): store data of type1 from data of type2


<br\>
<br\>
## `Get<Type>` Functions


### `Get<Bit/Nibble>`

* `Get<Bit/Nibble>(src, off, <bit/nibble>_no)`
* `Get<Bit/Nibble>(off, <bit/nibble>_no)`

Returns the value of type at the specified type number
`<bit/nibble>_no` from the specified source address with
offset `(src + off)`. If source address `(src)` is not specified,
then this library's internal buffer is used as the source.

Parameters:
* `src`:		the base address of stored data
* `off`:		offset from which type index starts
* `<bit/nibble>_no`:		the index of the type (starts from 0)
 
Returns:
`<bit/nibble>_value`:	the value of the specified type



<br\>
<br\>
### `Get<Type>`

* `Get<Type>(src, off)`
* `Get<Type>(off)`

Returns the `<Type>` value at the specified source address with 
offset `(src + off)`. If source address `(src)` is not specified,
then this library's internal buffer is used as the source.

Parameters:
* `src`:		the base address of stored data
* `off`:		offset of the `<Type>` value

Returns:
`<type>_value`:	the value of the specified `<Type>`



<br\>
<br\>
### `GetString`

* `GetString(dst, sz, src, off, opt)`
* `GetString(dst, sz, off, opt)`
 
Returns the string from the specified source address with 
offset `(src + off)`. If source address `(src)` is not specified,
then this library's internal buffer is used as the source.

Parameters:
* `dst`:      destination buffer for string (it will be fetched here)
* `sz`:       size of destination in bytes (max. length of string-1)
* `src`:      the base address of stored string (which will be fetched)
* `off`:      offset of the stored string
* `opt`:      options for string fetching (`TYPE_ZEROED_STRING`, `TYPE_LENGTH_STRING`)

Returns:
`string_value`:  the fetched string


<br\>
<br\>
## `Put<Type>` Functions


### `Put<Bit/Nibble>`

* `Put<Bit/Nibble>(dst, off, <bit/nibble>_no, <bit/nibble>_value)`
* `Put<Bit/Nibble>(off, <bit/nibble>_no, <bit/nibble>_value)`

Stores the value of type at the specified type number `(<bit/nibble>_no)`
to the specified destination address with offset `(dst + off)`.
If destination address `(dst)` is not specified, then this
library's internal buffer is used as the destination.

Parameters:
* `dst`:		the base address of destination
* `off`:		offset from which bit index starts
* `bit_no`:	the index of the bit (starts from 0)
* `bit_value`:	the value of the specified bit (0 or 1)

Returns:
nothing



<br\>
<br\>
### `Put<Type>`

* `Put<type>(dst, off, value)`
* `Put<type>(off, value)`

Stores the value of `<Type>` at the specified destination
address with offset `(dst + off)`. If destination address
`(dst)` is not specified, then this library's internal
buffer is used as the destination.

Parameters:
* `dst`:		the base address of destination
* `off`:		offset where `<Type>` value is stored
* `value`:	the value of `<Type>` to be stored

Returns:
nothing



<br\>
<br\>
### `PutString`

* `PutString(dst, off, value, opt)`
* `PutString(off, value, opt)`

Stores the string at the specified destination address with 
offset `(dst + off)`. If destination address `(dst)` is not specified,
then this library's internal buffer is used as the destination.

Parameters:
* `dst`:      destination base address where the string is to be stored
* `off`:      offset to destination from where the stored string will start
* `value`:    the string that is to be stored
* `opt`:      options for string writing (`TYPE_ZEROED_STRING`, `TYPE_LENGTH_STRING`)

Returns:
nothing



<br\>
<br\>
## `To<Type>` Functions


### `To<Type>`

* `To<type>(smaller_data_types)`

Assembles smaller data types to a bigger data type. The
assembling is done in little endian format, which means
that the smaller data representing the least significant
part should come first, and the smaller data representing
the most significant part should come last.

Parameters:
* `smaller_data_types`:	list of bytes, shorts, ints, etc.

Returns:
`<type>_value`:	the value of the (bigger) assembled data type


<br\>
<br\>
## `DoAction` Functions


### `DoReverse`

* `DoReverse(src, off, len)`
* `DoReverse(off, len)`

Reverses the data stored at the source address `(src + off)`
of specified length `(len)`. The data at the source is directly
reversed, and hence if the original data is required, then
it is suggested to make a copy of it. If source base address
is not specified, this library's internal buffer is assumed
as the source base address.

Parameters:
* `src`:		the base address of source data
* `off`:		offset to the actual data to be reversed `(src + off)`
* `len`:		length of data to be reversed

Returns:
nothing



<br\>
<br\>
## `Get<Type><Action>` Functions


### `Get<Byte/Ushort/Uint16>Sum`

* `Get<Byte/Ushort/Uint16>Sum(src, off, len)`
* `Get<Byte/Ushort/Uint16>Sum(off, len)`

Finds the sum of all bytes/ushorts at the specified source
address `(src + off)` of the specified length `(len)`. If source
base address is not specified, this library's internal buffer
is assumed as the source base address. This can be used to
calculate checksums.

Parameters:
* `src`:		the base address of source data
* `off`:		offset to the data to be summed `(src + off)`
* `len`:		length of data to be summed

Returns:
`<type>_value`:  the summed value



<br\>
<br\>
## `Get<Type1>From<Type2>` Functions


### `GetHexFromBin`

* `GetHexFromBin(dst, sz, src, off, len, opt)`
* `GetHexFromBin(dst, sz, off, len, opt)`

Get hexadecimal string `(dst)` of maximum specified size `(sz)` of
the soure binary data `(src + off)` of specified length `(len)`. The
options `(opt)` specify how the conversion is to be performed, and
it takes as input a set of flags. If source base address is not
specified, this library's internal buffer is assumed as the source
base address.

Parameters:
* `dst`:	      the destination string where hex string will be stored
* `sz`:        the maximum possible size of the hex string (buffer size)
* `src`:	      the base address of source binary data
* `off`:	      offset to the binary data to be converted `(src + off)`
* `len`:	      length of data to be converted
* `opt`:	      conversion options (`TYPE_ADD_SPACE`, `TYPE_ADD_CHAR`, `TYPE_BIG_ENDIAN`)

Returns:
nothing



<br\>
<br\>
## `Put<Type1>From<Type2>` Functions


## `PutBinFromHex`

* `PutBinFromHex(dst, off, len, src, opt)`
* `PutBinFromHex(off, len, src, opt)`

Puts binary data from the source hex string `(src)` to the destination
address `(dst + off)` of specified length len. The options `(opt)` specify
how the conversion is to be performed, and it takes as input a set of
flags. If destination base address is not specified, this library's
internal buffer is assumed as the destination base address.

Parameters:
* `dst`:	      the base address of destination
* `off`:	      the destination offset where the binary data will be stored `(dst + off)`
* `len`:       length of data at destination
* `src`:	      the hex string to be converted
* `opt`:	      conversion options (`TYPE_HAS_SPACE`, `TYPE_HAS_CHAR`, `TYPE_BIG_ENDIAN`)

Returns:
the converted data `(dst)`


<br\>
<br\>
## Copyright and License

Embedded_Type : Library header file for C/C+/Arduino/Processing

Embedded_Type is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Embedded_Type is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Embedded_Type.  If not, see <http://www.gnu.org/licenses/>.

