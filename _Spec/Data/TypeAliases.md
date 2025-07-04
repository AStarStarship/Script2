# [SCRIPT Specification](../)

## [ASCII Data Specification](./)

### Type Aliases

Type Aliases are POD types that are remapped to POD Types 0 through 19 are defined by the target implementation so they are remapped to one of the other POD types.

| Type |   Alt Name   |  Width  | Description |
|:----:|:------------:|:-------:|:------------|
| CHN  |   wchar_t    |   2,4   | A 16 or 32-bits wide Unicode character. |
| SIN  |     int      |   2,4   | Signed integer at least 16 bits wide. |
| IUN  | unsigned int |   2,4   | Unsigned integer at least 16 bits wide. |
| ISG  |     SI       |   W/2   | Half-word sized signed integer. |
| IUG  |     UI       |   W/2   | Half-word sized unsigned integer. |
| FPG  |     FP       |    W    | Floating-point number the half the size of the size of the host CPU's FPU. |
| ISW  |   intptr_t   |    W    | Signed integer of the size of the host CPU's ALU. |
| IUW  |  uintptr_t   |    W    | Unsigned integer of the size of the host CPU's ALU. |
| FLW  |  floatptr_t  |    W    | Floating-point number the size of the size of the host CPU's FPU. |
| ISD  |     SI       |   2W    | Double-word sized signed integer. |
| IUD  |     UI       |   2W    | Double-word sized unsigned integer. |
| FLD  |     FP       |   2W    | Floating-point number the twice the size of the size of the host CPU's FPU. |
| PTR  |    void*     |    W    | Word-sized pointer. |
| PTC  | const void*  |    W    | Word-sized const pointer. |
| DTW  |   intptr_t   |    W    | A word-sized ASCII Data Type. |
| CHR  |    char_t    |  1,2,4  | Unicode character at least 8 bits wide. |
| ISR  |    int_t     | 1,2,4,8 | Signed integer at least 8 bits wide. |
| IUR  |    uint_t    | 1,2,4,8 | Unsigned integer at least 8 bits wide. |
| FPR  |   float_t    | 1,2,4,8 | Floating-point number at least 16 bits wide. |
| TMS  |  Timestamp   |   4,8   | Seconds-since-epoch timestamp stored as ISC or ISD. |

#### List of Types Key

| Width | Description |
|:-----:|:------------|
|   x   | The numbers 0, 1, 2, 4, 8, and 16 are the number of bytes in the type. |
|  xW   | Word-aligned word-sized type. |
|  W/2  | Half-word type word-sized type. |

**[<< Previous Section:Text](Text.md) | [Next Section:Value >>](Value.md)**

## License

Copyright Kabuki Starship <<https://github.com/KabukiStarship/Script2>>.
