# Numbers

There are two ways to create numbers in ASCII Data, Value Numbers or Void Numbers. All 3-letter void ASCII type codes end with a lowercase `d` because they are 16-bit. Void Numbers store the value in the type and not the Value section. Value Types are stored in the Value section of the data type, such as a dictionary of key-value pairs.

Void Numbers are created by setting the MOD (Modifier) bits to `0b01` for a FPd (13-bit Void Float), `0b10` for a CHd (13-bit Void unsigned Unicode character), or `0b11` for a ISd (13-bit Void signed integer).

## Integers

Script supports both traditional 8, 16, 32, and 64-bit, and n-byte signed 2's complement integers and uncomplemented unsigned integers.

### 2.2.a Valid Integers Examples

```C++
ISA 0
IUA 255
ISB -32,000
ISC 0xFFFF
ISd 0x1FFF //< The largest 13-bit Void signed integer.
```

### 2.2.b Invalid Integer Examples

```IMUL
ISA 256       //< Too big for size
ISB 0xFFFFF   //< Too big for size
ISd 0x2FFF    //< 14-bit Void signed integer can't fit in 13-bits.<
```

### 2.2.c Unsigned Not-a-Numbers

Unsigned Not-a-Number (U-NaN) is the bit pattern with all ones as in the following example:

```C++
template<typename IU = IUW>
inline IU NaNUnsigned () {
  IU nan = 0;
  return ~nan;
}
```

### 2.2.d Signed Not-a-Numbers

Unsigned Not-a-Number (S-NaN) is the bit pattern with only the Most Significant bit asserted as in the following example:

```C++
template<typename IS, typename IU>
inline IS NaNSigned () {
  IU nan = 1;
  return (IS)(nan << (sizeof (IU) * 8 - 1));
}
```

### 2.2.e Varints

Variants are MSb variant are compressed using Negative MSB-variant encoded signed and unsigned 1-to-9-byte variable-length integers. Varints C0 code prefix is VS for Varint Signed and VU for Varint Unsigned. There are no 8-bit varints so there are VSB, VSC, VSD, VUB, VUC, and VUD.

Varints use the MSb of each byte to determine if another byte is to be loaded. This allows values less than 128 to be sent using only one byte, 14-bit values in two bytes, 21-bit values in three bytes and so on.

Varints are converted from least to most significant bits in groups of 7. If any of the more significant bits left to pack or unpack are asserted, you multiply the 7-bit nibble by -1 to get the encoding for that nibble with the exception of the last nibble.

```C++
VUB 128 // = 0b0000_0001_1000_0000
VUC 255 // = 0b0000_0001_1111_1111
VSA -64 // = 0b1100_0001
```

### 2.2.f BigNum

Unsigned Integer BigNum (IUB) is between 2 and 2048 bytes wide where the 5 LSb of the type are always 0. The width of the unsigned integer is found by shifting the type over 5 bits to the right and adding one[9].

### Example

```C++
IUB_1 //< 1-byte IUB data type in Hex is 0x20.
IUB_255 //< 1-byte IUB data type in Hex is 0x2000.
IUB_2048 //< 2048-byte IUB data type in Hex is 0xFFE0.
```

## Boolean

Booleans in Script are stored as signed integer types where the false value is stored as the number zero and labeled false, and asserted values is represented as the number one labeled true or a non-zero integer value.

### Boolean Examples

```C++
// All values less then 127 and greater than -127
BOL true   //< Translates to the number 1
BOL false  //< Translates to the number 0
BOL 0
BOL 1
BOL -129   //< Will require 2 bytes to transceive.
```

### Floating Point

Script supports 8, 16, 32, 64, and 128-bit floating-point numbers as defined, also called half, float, and double, and quadruple precision float-point numbers, as defined in the IEEE754 specification.

13-bit Void floats are in the 16-bit float format with seven mantissa bits and five exponent bits.

```C++
FPB 0.0     // Use a HLF to save memory and bandwidth!
FPC 0.1     // Wastes a lot of space!
FPD - 0.1;  // Wastes a whole lot of space!
FPE 1.0     // Wastes a TRUCK TON of space but best for repeated addition.
```

**[<< Previous Section: Extended Types](ExtendedTypes.md) | [Next Section: Timestamps >>](Timestamps.md)**

## Requirements

[1] ./

## License

Copyright Kabuki Starship <<https://github.com/KabukiStarship/Script2>>.
