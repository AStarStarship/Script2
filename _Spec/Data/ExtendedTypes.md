# Extended Types

There are two sets of Extended Types, EM (Extended Mappable) Types and ES (Extended Standard) Types. In ES Types 0 through 511, there are a total of 52 Illegal Types that are not memory aligned on any system along with 15 NIL Vector types that are remapped to create EM Types. EM Types are created by setting MOD Bits `0b00`. Extended Standard Type 0 is the ANY wildcard type that can be any time.

## Extended Mappable Types

| ID |  Type   |    Name    | Description |
|:--:|:-------:|:----------:|:------------|
| 00 |   INV   |  Invalid   | Invalid.    |
| 01 |   WLD   | Type-Value | A Wildcard type-value tuple. |
| 02 |   PTC   |  Pointer   | 4-byte pointer. |
| 03 |   PTD   |  Pointer   | 8-byte pointer. |
| 04 |   OBA   |   Object   | 1-byte size-width contiguous object. |
| 05 |   OBB   |   Object   | 2-byte size-width contiguous object. |
| 06 |   OBC   |   Object   | 4-byte size-width contiguous object. |
| 07 |   OBD   |   Object   | 8-byte size-width contiguous object. |
| 08 |   BSA   |    BSQ     | 1-byte size-width B-Sequence. |
| 09 |   BSB   |    BSQ     | 2-byte size-width B-Sequence. |
| 10 |   BSC   |    BSQ     | 4-byte size-width B-Sequence. |
| 11 |   BSD   |    BSQ     | 8-byte size-width B-Sequence. |
| 12 |   TB0   |   Table    | TTable<ISC, ISB, IUC>. |
| 13 |   TB1   |   Table    | TTable<ISD, ISC, IUC>. |
| 14 |   TB2   |   Table    | TTable<ISC, ISB, IUD>. |
| 15 |   TB3   |   Table    | TTable<ISD, ISC, IUD>. |
| 16 |   FAL   |    False   | Boolean false. |
| 17 |   TRU   |    True    | Boolean true. |
| 18 |   R02   |  Reserved  | Reserved. |
| 19 |   R03   |  Reserved  | Reserved. |
| 20 |   DTA   | Data Type  | 1-byte ASCII Data Type. |
| 21 |   DTB   | Data Type  | 2-byte ASCII Data Type. |
| 22 |   DTC   | Data Type  | 4-byte ASCII Data Type. |
| 23 |   DTD   | Data Type  | 8-byte ASCII Data Type. |
| 24 |   SQC   |  Big SInt  | A 32-bit n-bit signed bigint. |
| 25 |   UQC   |  Big UInt  | A 32-bit n-bit unsigned bigint. |
| 26 |   SQD   |  Big SInt  | A 64-bit n-bit signed bigint. |
| 27 |   UQD   |  Big UInt  | A 64-bit n-bit unsigned bigint. |
| 28 |   R05   |  Reserved  | Reserved. |
| 29 |   R06   |  Reserved  | Reserved. |
| 30 |   BOB   |  Boolean   | 2-byte BOL value. |
| 31 |   BOC   |  Boolean   | 4-byte BOL value. |
| 32 |   BO0   |    Book    | TBook<CHA, ISB, ISA, DTB>. |
| 33 |   BO1   |    Book    | TBook<CHA, ISC, ISB, DTB>. |
| 34 |   BO2   |    Book    | TBook<CHA, ISD, ISC, DTB>. |
| 35 |   BO3   |    Book    | TBook<CHB, ISB, ISA, DTB>. |
| 36 |   BO4   |    Book    | TBook<CHB, ISC, ISB, DTB>. |
| 37 |   BO5   |    Book    | TBook<CHB, ISD, ISC, DTB>. |
| 38 |   BO6   |    Book    | TBook<CHC, ISB, ISA, DTB>. |
| 39 |   BO7   |    Book    | TBook<CHC, ISC, ISB, DTB>. |
| 40 |   BO8   |    Book    | TBook<CHC, ISD, ISC, DTB>. |
| 41 |   DI0   | Dictionary | TDic<CHA, ISC, ISB, IUC, DTB>. |
| 42 |   DI1   | Dictionary | TDic<CHA, ISD, ISC, IUD, DTB>. |
| 43 |   DI2   | Dictionary | TDic<CHB, ISC, ISB, IUC, DTB>. |
| 44 |   DI3   | Dictionary | TDic<CHB, ISD, ISC, IUD, DTB>. |
| 45 |   DI4   | Dictionary | TDic<CHC, ISC, ISB, IUC, DTB>. |
| 46 |   DI5   | Dictionary | TDic<CHC, ISD, ISC, IUD, DTB>. |
| 47 |   R07   |  Reserved  | Reserved. |
| 48 |   LS0   |    List    | TList<ISB, ISA, DTB>. |
| 49 |   LS1   |    List    | TList<ISC, ISB, DTB>. |
| 50 |   LS2   |    List    | TList<ISD, ISC, DTB>. |
| 52 |   R11   |  Reserved  | Reserved. |
| 53 |   R12   |  Reserved  | Reserved. |
| 54 |   R13   |  Reserved  | Reserved. |
| 55 |   R10   |  Reserved  | Reserved. |
| 56 |   R11   |  Reserved  | Reserved. |
| 57 |   R12   |  Reserved  | Reserved. |
| 58 |   R13   |  Reserved  | Reserved. |
| 59 |   R11   |  Reserved  | Reserved. |
| 60 |   R12   |  Reserved  | Reserved. |
| 61 |   R13   |  Reserved  | Reserved. |
| 62 |   R14   |  Reserved  | Reserved. |
| 63 |   R15   |  Reserved  | Reserved. |
| 64 |   R16   |  Reserved  | Reserved. |
| 65 |   R17   |  Reserved  | Reserved. |
| 66 |   R18   |  Reserved  | Reserved. |
| 67 |   R19   |  Reserved  | Reserved. |

| ID |  Type   |    Name    | Description |
|:--:|:-------:|:----------:|:------------|
| 01 |   WLD   | Type-Value | A Wildcard type-value tuple. |
| 02 |   PTC   |  Pointer   | 4-byte pointer. |
| 03 |   PTD   |  Pointer   | 8-byte pointer. |
| 04 |   OBA   |   Object   | 1-byte size-width contiguous object. |
| 05 |   OBB   |   Object   | 2-byte size-width contiguous object. |
| 06 |   OBC   |   Object   | 4-byte size-width contiguous object. |
| 07 |   OBD   |   Object   | 8-byte size-width contiguous object. |
| 08 |   BSA   |    BSQ     | 1-byte size-width B-Sequence. |
| 09 |   BSB   |    BSQ     | 2-byte size-width B-Sequence. |
| 10 |   BSC   |    BSQ     | 4-byte size-width B-Sequence. |
| 11 |   BSD   |    BSQ     | 8-byte size-width B-Sequence. |
| 12 |   DTA   | Data Type  | 1-byte ASCII Data Type. |
| 13 |   DTB   | Data Type  | 2-byte ASCII Data Type. |
| 14 |   DTC   | Data Type  | 4-byte ASCII Data Type. |
| 15 |   DTD   | Data Type  | 8-byte ASCII Data Type. |

| 16 |   TB0   |   Table    | TTable<ISC, ISB, IUC>. |
| 17 |   TB1   |   Table    | TTable<ISD, ISC, IUC>. |
| 18 |   TB2   |   Table    | TTable<ISC, ISB, IUD>. |
| 19 |   TB3   |   Table    | TTable<ISD, ISC, IUD>. |
| 20 |   BO0   |    Book    | TBook<CHA, ISB, ISA, DTB>. |
| 21 |   BO3   |    Book    | TBook<CHB, ISB, ISA, DTB>. |
| 22 |   BO6   |    Book    | TBook<CHC, ISB, ISA, DTB>. |
| 23 |   LS0   |    List    | TList<ISB, ISA, DTB>. |
| 24 |   DI0   | Dictionary | TDic<CHA, ISC, ISB, IUC, DTB>. |
| 25 |   DI2   | Dictionary | TDic<CHB, ISC, ISB, IUC, DTB>. |
| 26 |   DI4   | Dictionary | TDic<CHC, ISC, ISB, IUC, DTB>. |
| 27 |   R06   |  Reserved  | Reserved. |
| 28 |   BO1   |    Book    | TBook<CHA, ISC, ISB, DTB>. |
| 29 |   BO4   |    Book    | TBook<CHB, ISC, ISB, DTB>. |
| 30 |   BO7   |    Book    | TBook<CHC, ISC, ISB, DTB>. |
| 31 |   LS1   |    List    | TList<ISC, ISB, DTB>. |
| 33 |   DI1   | Dictionary | TDic<CHA, ISD, ISC, IUD, DTB>. |
| 34 |   DI3   | Dictionary | TDic<CHB, ISD, ISC, IUD, DTB>. |
| 35 |   DI5   | Dictionary | TDic<CHC, ISD, ISC, IUD, DTB>. |
| 36 |   R06   |  Reserved  | Reserved. |
| 37 |   BO2   |    Book    | TBook<CHA, ISD, ISC, DTB>. |
| 38 |   BO5   |    Book    | TBook<CHB, ISD, ISC, DTB>. |
| 39 |   BO8   |    Book    | TBook<CHC, ISD, ISC, DTB>. |
| 40 |   LS2   |    List    | TList<ISD, ISC, DTB>. |

| 41 |   BO0   |    Book    | TBook<CHA, ISB, ISA, DTC>. |
| 21 |   BO3   |    Book    | TBook<CHB, ISB, ISA, DTC>. |
| 22 |   BO6   |    Book    | TBook<CHC, ISB, ISA, DTC>. |
| 23 |   LS0   |    List    | TList<ISB, ISA, DTC>. |
| 24 |   DI0   | Dictionary | TDic<CHA, ISC, ISB, IUC, DTC>. |
| 25 |   DI2   | Dictionary | TDic<CHB, ISC, ISB, IUC, DTC>. |
| 26 |   DI4   | Dictionary | TDic<CHC, ISC, ISB, IUC, DTC>. |
| 27 |   R06   |  Reserved  | Reserved. |
| 28 |   BO1   |    Book    | TBook<CHA, ISC, ISB, DTC>. |
| 29 |   BO4   |    Book    | TBook<CHB, ISC, ISB, DTC>. |
| 30 |   BO7   |    Book    | TBook<CHC, ISC, ISB, DTC>. |
| 31 |   LS1   |    List    | TList<ISC, ISB, DTC>. |
| 33 |   DI1   | Dictionary | TDic<CHA, ISD, ISC, IUD, DTC>. |
| 34 |   DI3   | Dictionary | TDic<CHB, ISD, ISC, IUD, DTC>. |
| 35 |   DI5   | Dictionary | TDic<CHC, ISD, ISC, IUD, DTC>. |
| 36 |   R06   |  Reserved  | Reserved. |
| 37 |   BO2   |    Book    | TBook<CHA, ISD, ISC, DTC>. |
| 38 |   BO5   |    Book    | TBook<CHB, ISD, ISC, DTC>. |
| 39 |   BO8   |    Book    | TBook<CHC, ISD, ISC, DTC>. |
| 27 |   R06   |  Reserved  | Reserved. |

| 20 |   BO0   |    Book    | TBook<CHA, ISB, ISA, DTD>. |
| 21 |   BO3   |    Book    | TBook<CHB, ISB, ISA, DTD>. |
| 22 |   BO6   |    Book    | TBook<CHC, ISB, ISA, DTD>. |
| 27 |   R06   |  Reserved  | Reserved. |
| 24 |   DI0   | Dictionary | TDic<CHA, ISC, ISB, IUC, DTD>. |
| 25 |   DI2   | Dictionary | TDic<CHB, ISC, ISB, IUC, DTD>. |
| 26 |   DI4   | Dictionary | TDic<CHC, ISC, ISB, IUC, DTD>. |
| 27 |   R06   |  Reserved  | Reserved. |
| 28 |   BO1   |    Book    | TBook<CHA, ISC, ISB, DTD>. |
| 29 |   BO4   |    Book    | TBook<CHB, ISC, ISB, DTD>. |
| 30 |   BO7   |    Book    | TBook<CHC, ISC, ISB, DTD>. |
| 27 |   R06   |  Reserved  | Reserved. |
| 33 |   DI1   | Dictionary | TDic<CHA, ISD, ISC, IUD, DTD>. |
| 34 |   DI3   | Dictionary | TDic<CHB, ISD, ISC, IUD, DTD>. |
| 35 |   DI5   | Dictionary | TDic<CHC, ISD, ISC, IUD, DTD>. |
| 36 |   R06   |  Reserved  | Reserved. |
| 37 |   BO2   |    Book    | TBook<CHA, ISD, ISC, DTD>. |
| 38 |   BO5   |    Book    | TBook<CHB, ISD, ISC, DTD>. |
| 39 |   BO8   |    Book    | TBook<CHC, ISD, ISC, DTD>. |
| 63 |   R06   |  Reserved  | Reserved. |

| 64 |   SQC   |  Big SInt  | A 32-bit n-bit signed bigint. |
| 65 |   UQC   |  Big UInt  | A 32-bit n-bit unsigned bigint. |
| 66 |   SQD   |  Big SInt  | A 64-bit n-bit signed bigint. |
| 67 |   UQD   |  Big UInt  | A 64-bit n-bit unsigned bigint. |

All ASCII Data Types **shall** be memory aligned on 32-bit systems, leaving 32 types that that are not aligned 64-bit systems, and these types are illegal on 64-bit systems. Due to memory space constraints, 16-bit memory space processors (i.e. 8-bit microcontrollers with only 64KB RAM or less) do not support Context and Extended Types.

Remapping 14-bit ASCII Data Type bit pattern to the Extended Types **shall** be fast as possible. For this reason all Plain Context Types **shall** be sorted by memory alignment in descending order such that PCa is of the largest and PCl is of the smallest type. Plain Context Types PCa through PCl are not defined at this level, they may or may not be remapped to legal types depending on the Context. PC types remapped to illegal types are Extended Context Types.

## Remapping

```AsciiArt
| Vector | POD 0-31   1=Valid, 0=Invalid, 4=Valid on 32-bit CPU, ?=Unknown  |
| Type   | N I I C F I I C F I I C T I I F  F I I T P P P P P P P P P P P P |
| SW:VT  | I U S H P U S H P U S H M U S P  P U S M C C C C C C C C C C C C |
| b8:b5  | L A A A B B B B C C C C D D D D  E E E E a b c d e f g h i j k l |
+--------+------------------------------------------------------------------|
|  8_VH1 | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
|  8_ARY | 0 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0  0 0 0 0 ? ? ? ? ? ? ? ? ? ? ? ? |
|  8_SCK | 0 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0  0 0 0 0 ? ? ? ? ? ? ? ? ? ? ? ? |
|  8_MTX | 0 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0  0 0 0 0 ? ? ? ? ? ? ? ? ? ? ? ? |
| 16_VH2 | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 16_ARY | 0 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0  0 0 0 0 ? ? ? ? ? ? ? ? ? ? ? ? |
| 16_SCK | 0 1 1 1 1 1 1 1 1 1 1 1 4 4 4 4  4 4 4 4 ? ? ? ? ? ? ? ? ? ? ? ? |
| 16_MTX | 0 1 1 1 1 1 1 1 1 1 1 1 4 4 4 4  4 4 4 4 ? ? ? ? ? ? ? ? ? ? ? ? |
| 32_VH3 | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 32_ARY | 0 1 1 1 1 1 1 1 1 1 1 1 4 4 4 4  4 4 4 4 ? ? ? ? ? ? ? ? ? ? ? ? |
| 32_SCK | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  4 4 4 4 ? ? ? ? ? ? ? ? ? ? ? ? |
| 32_MTX | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  4 4 4 4 ? ? ? ? ? ? ? ? ? ? ? ? |
| 64_VH4 | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 64_ARY | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 64_SCK | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
| 64_MTX | 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 |
+--------+------------------------------------------------------------------|
| Total  | 0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1  1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 |
|  512   |      Type 0-31      0 1 2 3 4 5  6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 |
```

Types are remapped in blocks in order A through H in the table bellow. The columns of the blocks are grouped in powers of two, either four or eight wide. The upper left letter is then shifted to the origin (i.e. 0, 0) to convert the SW:VT and POD bits into contiguous integer values(i.e. by shifting the SW:VT bits to the left 5 bits and ORing it with the POD bits).

```AsciiArt
| Vector | POD 0-31  .=Valid A-H=Order to convert blocks, lower case:64-bit |
| Type   | N I I C F I I C F I I C F I I T  F I I T P P P P P P P P P P P P |
| SW:VT  | I U I H P U S H P U S H P U S M  P U S M C C C C C C C C C C C C |
| b8:b5  | L A A A B B B B C C C C D D D D  E E E E a b c d e f g h i j k l |
+--------+------------------------------------------------------------------|
|   0/A  | A . . . . . . . . . . . . . . .  . . . . . . . . . . . . . . . . |
|   1/C  | A . . . I I I I H H H H G G G G  G G G G C C C C B B B B B B B B |
|   2/C  | A . . . . . . . H H H H G G G G  G G G G C C C C B B B B B B B B |
|   3/D  | A . . . . . . . H H H H G G G G  G G G G C C C C B B B B B B B B |
|   4/E  | A . . . . . . . . . . . . . . .  . . . . . . . . . . . . . . . . |
|   5/F  | A . . . . . . . I I I I G G G G  G G G G C C C C B B B B B B B B |
|   6/G  | A . . . . . . . . . . . . . . .  . . . . E E E E B B B B B B B B |
|   7/H  | A . . . . . . . . . . . . . . .  . . . . E E E E B B B B B B B B |
|   8/I  | A . . . . . . . . . . . . . . .  . . . . . . . . . . . . . . . . |
|   9/J  | A . . . . . . . . . . . . . . .  . . . . F F F F B B B B B B B B |
|  10/K  | A . . . . . . . . . . . . . . .  . . . . D D D D B B B B B B B B |
|  11/L  | A . . . . . . . . . . . . . . .  . . . . D D D D B B B B B B B B |
|  12/M  | A . . . . . . . . . . . . . . .  . . . . . . . . . . . . . . . . |
|  13/N  | A . . . . . . . . . . . . . . .  . . . . . . . . . . . . . . . . |
|  14/O  | A . . . . . . . . . . . . . . .  . . . . . . . . . . . . . . . . |
|  15/P  | A . . . . . . . . . . . . . . .  . . . . . . . . . . . . . . . . |
+--------+------------------------------------------------------------------|
| Total  | 0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1  1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 |
|  512   |      Type 0-31      0 1 2 3 4 5  6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 |
```

To convert the blocks above to contiguous Repacked Extended Mappable Types or Repacked Plain Context Types you shift the blocks to the origin (i.e. SW_VT:0 and POD: 0), then shift the SW_VT and POD bits back up to convert the blocks that are 4-wide to the blocks that are 8-wide.

### Repacked Extended Mappable Types

```AsciiArt
| Total | 0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1  1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 |
|  60   | Extended Type 0-31  0 1 2 3 4 5  6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 |
+-------+------------------------------------------------------------------|
| 00/0  | . A A A A A A A A A A A A A A A  G G G G G G G G G G G G G G G G |
| 01/1  | G G G G G G G G I I I I I I I I  G G G G G G G G H H H H H H H H |
| 10/2  | H H H H . . . . . . . . . . . .  . . . . . . . . . . . . . . . . |
```

### Repacked Plain Context Types

```AsciiArt
| Total | 0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1  1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 |
|  72   | Extended Type 0-31  0 1 2 3 4 5  6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 |
+-------+------------------------------------------------------------------|
| 00/0  | B B B B B B B B B B B B B B B B  B B B B B B B D D D D D D D D D |
| 01/1  | B B B B B B B B B B B B B B B B  B B B B B B B E E E E E E E E E |
| 10/2  | B B B B B B B B B B B B B B B B  B B B B B B B C C C C C C C C C |
| 10/2  | C C C C F F F F C C C C . . . .  . . . . . . . . . . . . . . . . |
```

## Extended Block Types

Because there are 12 Plain Context Types and only four 128-bit types, Extended Block Type are created by setting the MSb of the 16-bit data type pattern to `0b111...`, yielding eight Blocks of 511 Extended Block Types.

### Extended Blocks Table

The CNS, MD, and EB (Extended Block) bits take up 6 control bits, leaving 10 LSb.

| Value | Code | Description |
|:-----:|:----:|:------------|
|  00   | CIX  | A 9-bit Scoped or 9-bit Global Crabs Index. |
|  01   | EXT  | Extended Standard or Extended Context Types. |
|  02   | I1K  | 0 is NIL and A block of 1-1024 bytes. |
|  03   | I2K  | 0 is NIL and A block of 1025-2048 bytes. |
|  04   | R00  | Reserved. |
|  05   | R01  | Reserved. |
|  06   | R02  | Reserved. |
|  07   | BFA  | An 8-bit Void Signed Boolean or Void Minifloat. |

### Extended Standard Types

| ID  |  Type   |    Name    | Description |
|:---:|:-------:|:----------:|:------------|
| 00  |   FAL   |    False   | Boolean false. |
| 01  |   TRU   |    True    | Boolean true. |
| 02  |   VSB   |   Varint   | 16-bit signed MSb variant encoded integer. |
| 03  |   VUB   |   Varint   | 16-bit unsigned MSb variant encoded integer. |
| 04  |   VSC   |   Varint   | 32-bit signed MSb variant encoded integer. |
| 05  |   VUC   |   Varint   | 32-bit unsigned MSb variant encoded integer. |
| 06  |   VSD   |   Varint   | 64-bit signed MSb variant encoded integer. |
| 07  |   VUD   |   Varint   | 64-bit unsigned MSb variant encoded integer. |
| 08  |   STA   |   String   | Nil-terminated UTF-8 string. |
| 09  |   STB   |   String   | Nil-terminated UTF-16 string. |
| 10  |   STC   |   String   | Nil-terminated UTF-32 string. |
| 11  |   R01   |  Reserved  | Reserved. |
| 12  |   R02   |  Reserved  | Reserved. |
| 13  |   R03   |  Reserved  | Reserved. |
| 14  |   R04   |  Reserved  | Reserved. |
| 15  |   RSe   |  Reserved  | Reserved. |
| 16  |   ERA   |   Error    | 1-byte Error type. |
| 17  |   ERB   |   Error    | 2-byte Error type. |
| 18  |   ERC   |   Error    | 4-byte Error type. |
| 19  |   ERD   |   Error    | 8-byte Error type. |
| 20  |   EOA   | Err Object | 1-byte size-width Error type. |
| 21  |   EOB   | Err Object | 2-byte size-width Error type. |
| 22  |   EOC   | Err Object | 4-byte size-width Error type. |
| ..  |   ...   |     ...    | .... |
| 254 |   Any   |  Wildcard  | Wildcard; can be any type. |
| 255 |   INV   |   Invalid  | Marks an invalid type in a B-Sequence. |

## Extended 8-bit Types

The ETA, Extended Type 8-bit, Block stores either an 8-bit Void Boolean value if the MSb is 0, or 8-bit signed int if the MSb is 1.

### Pointers

There are two ways to make an ASCII Pointer, one is by setting the MD bits to MDP, the other is by making a negative ISZ (AKA the largest signed integer type). All ASCII Objects are pointer types, so setting the pointer types to ASCII Objects creates a pointer to a pointer.

When an ASCII Object's bytes is positive the type is a contiguous number of bytes, if the values is negative then it becomes a raw pointer from the origin of the Crabs machine.

At the very origin of the Crabs machine is a word aligned block of memory, which does not apply to 16-bit address space CPUs, that is 256 bytes plus the width of the CPU's cache line plus size of variables, which is typically 64 bytes on all CPUs with DDR RAM. 8-bit Crabs pointers are mapped to this 256-byte Crabs origin.

Pointer values between 257-65535

**[<< Previous Section: Types](Types.md) | [Next Section: Numbers >>](Numbers.md)**

## License

Copyright Kabuki Starship <<https://github.com/KabukiStarship/Script2>>.
