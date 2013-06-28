# [emType v0.3](https://github.com/wolfram77/emType) [![Build Status](https://raw.github.com/wolfram77/emType/master/build.png)](https://raw.github.com/wolfram77/emType/master/build.png)

emType is a generic type conversion library for [Arduino](http://arduino.cc/), [Waspmote](http://www.libelium.com/products/waspmote/), [Processing](http://www.processing.org/), C/C++.
It has been developed mainly for simplifying the process of writing wireless communication
programs on Arduino, Waspmote and Processing. Created and maintained by [Subhajit Sahu](https://github.com/wolfram77)



## Functions

emType has 7 types of functions:
(click to jump to)
* [`Get<Type>`](https://github.com/wolfram77/emType/blob/master/README.md#gettype-functions):	obtain a datatype from buffer
* [`Put<Type>`](https://github.com/wolfram77/emType/edit/master/README.md#puttype-functions):	store a datatype onto buffer
* [`To<Type>`](https://github.com/wolfram77/emType/edit/master/README.md#totype-functions):	assemble smaller datatypes to a bigger one
* [`Do<Action>`](https://github.com/wolfram77/emType/edit/master/README.md#doaction-functions): performs an action directly on the buffer (buffer is modified)
* [`Get<Type><Action>`](https://github.com/wolfram77/emType/edit/master/README.md#gettypeaction-functions): obtain the result of action performed on the buffer (buffer remains unchaged)
* [`Get<Type1>From<Type2>`](https://github.com/wolfram77/emType/edit/master/README.md#gettype1fromtype2-functions): obtain a type1 data from another type2 data
* [`Put<Type1>From<Type2>`](https://github.com/wolfram77/emType/edit/master/README.md#puttype1fromtype2-functions): store data of type1 from data of type2


<br\>
<br\>
## `Get<Type>` Functions


### `GetRegBit`

* `GetRegBit(src, bit_no)`

Returns the value of bit at the specified bit number `(bit_no)` from
the specified register `(src)`. This function is not available in Processing.

Parameters:
* `src`: 	the register from which bit is to be fetched
* `bit_no`:		the index of the bit (starts from 0)
 
Returns:
`bit_value`:	the value of the specified bit



<br\>
<br\>
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


### `SetRegBit`

* `SetRegBit(dst, list_of_bit_nos_to_set)`

Sets (to 1) the value of bits at the specified bit numbers, separated
with commas `(list_of_bit_nos_to_set)` to the specified register `(dst)`.
This functions is not available in Processing.

Parameters:
* `dst`: 	the register whose bits are to be set
* `list_of_bit_nos_to_set`:	a set of bit numbers separated with commas (multi-parameters)

Returns:
nothing



<br\>
<br\>
### `ClearRegBit`

* `ClearRegBit(dst, list_of_bit_nos_to_clear)`

Clears (to 0) the value of bits at the specified bit numbers, separated
with commas `(list_of_bit_nos_to_clear)` to the specified register `(dst)`.
This functions is not available in Processing.

Parameters:
* `dst`:  the register whose bits are to be cleared
* `list_of_bit_nos_to_clear`:	a set of bit numbers separated with commas (multi-parameters)

Returns:
nothing



<br\>
<br\>
### `PutRegBit`

* `PutRegBit(dst, bit_no, bit_value)`

Sets (to 0 or 1) the value of a bit as `(bit_value)` at the specified
bit number `(bir_no)` to the specified register `(dst)`. This functions
is not available in Processing.

Parameters:
* `dst`:  the register whose bit is to be set (to 0 or 1)
* `bit_no`: the bit number specifying the bit to be set
* `bit_value`: the value to which the bit is to be set

Returns:
nothing



<br\>
<br\>
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
## `Do<Action>` Functions


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

<h4>emType : Library for Arduino/Waspmote/Processing/C/C++</h4>

<p>
emType is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
</p>

<p>
emType is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
</p>

<p>
You should have received a copy of the GNU General Public License
along with emType.  If not, see <http://www.gnu.org/licenses/>.
</p>
