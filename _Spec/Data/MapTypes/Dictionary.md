# [SCRIPT Specification](../../)

## [ASCII Data Specification](../)

### [Map Types](./map_types)

#### Dictionaries

Dictionaries are key-type-value sets with a hash table of unique keys. Hash sizes my be 16-bit with up to 120 members, 32-bit with up to 2^24 items, or 64-bit with up to 256 * 10^6 items; these numbers are dictated by the statistical chance of hash algorism collisions. ASCII Dictionaries are created from a List with a Table in element 0.

Dictionaries have slower insert times than ASCII Books but faster lookup.

##### Dictionary Memory Layout

```AsciiArt
+====================================+
|_______   Buffer                    |
|_______ ^ List Value N              |
|_______ | List Value 1              |
|        | Keys Table (Value 0)      |
|------------------------------------|
|_______   Buffer                    |
|_______ ^ List Value N Type         |
|_______ | List Value 1 Type         |
|        | Table Type (Type 0)       |
|------------------------------------|
|_______   Buffer                    |
|_______   Offset to Value N         |
|_______ ^ Offset to Value 1         |
|        | Offset to Keys (Offset 0) |
+====================================+  ^ Up in
|          TList Struct              |  |
+====================================+  + 0xN
```

##### Book Memory Overhead

| #Bytes | Index | Offset | Hash  | Total | Overhead Per index |
|:------:|:-----:|:------:|:-----:|:-----:|:-------------------|
|    2   |   1   |    2   |   2   |   8   |  8 + 3  per index + buffer.|
|    4   |   2   |    4   |   4   |   16  | 16 + 4  per index + buffer.|
|    8   |   4   |    8   |   8   |   32  | 24 + 16 per index + buffer.|

| DIC  | Max Values | % Collisions (p) |           Overhead |
|:----:|:----------:|:----------------:|:------------------------------:|
|  2   |     255    |    0.0001        | Ceiling (0.02*p*2^8)  = 2      |
|  4   |     2^13   |      0.1         | Ceiling (0.04*p*2^13) = 327.68 |
|  8   |     2^29   |    10^-16        | Ceiling (0.04*p*2^29) = 327.68 |

**[<< Previous Section: Table](./Table.md) | [Next Section: SCRIPT Specification >>](../../)**

## Requirements

[1] ./

## License

Copyright Kabuki Starship <<https://github.com/KabukiStarship/Script2>>.
