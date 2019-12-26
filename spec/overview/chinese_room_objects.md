# [SCRIPT Specification](../)

## [Overview](./)

### Chinese Room Objects

|      Class | Code | Description       |
|-----------:|:----:|:------------------|
|      Array | ARY  | An *ASCII Array*. |
|        Bin | BIN  | A *B-Input Sequence*, or *B-Input*, is an A*B B-Input Stream. |
|       Bout | BOU  | A *B-Output Sequence*, or *B-Output*, is an A*B B-Output Stream. |
|      Clock | CLK  | Used for 32-bit and 64-bit timestamps. |
|       Door | DOR  | A door in a Chinese Room that leads to another Chinese Room or Agent. |
|  Interrupt | INT  | An Interrupt that causes the Room to Reset.  |
| Expression | EXP  | An asynchronous Group structured expression. |
|        Log | LOG  | A EXP used for a log. |
|  Operation | OPN  | A header for an Operation. |
|    Operand | OPD  | A header for an Operation. |
|     Portal | PTL  | A B-Sequence portal to another Chinese Room. |
|       Room | ROO  | A Chinese Room that can read and write B-Sequences. |
|        Set | SET  | Interface for a *ASCII Set Data Type*. |
|       Slot | SLT  | A slot (i.e. Socket) in a Door in a Chinese Room in the form of a Ring Buffer Socket. |
|      Table | TBL  | A Symbol Table implemented as a Set with no data. |
|       Wall | WAL  | A Wall in a Chinese Room composed of a contiguous word-aligned block of memory. |

**[<< Previous Section:Content Table](../)** | **[Next Section:ASCII Data Specification >>](../data/)**

## License

Copyright 2015-9 © [Kabuki Starship™](https://kabukistarship.com); all rights reserved.

This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at <https://mozilla.org/MPL/2.0/>.
