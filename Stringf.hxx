// Copyright AStarship <https://astarship.net>.
#include "Stringf.hpp"
#include "Binary.hpp"
namespace _ {

BOL CHIsPrintable(CHA item) {
  if (item < ' ') {
    if (item == 9) return true; // TAB
    return false;
  }
  if (item == 127) return false;
  return true;
}

BOL CHIsPrintable(CHB item) {
  if (item < ' ') {
    if (item == 9) return true; // TAB
    return false;
  }
  if (item == 127) return false;
  return true;
}

BOL CHIsPrintable(CHC item) {
  if (item < ' ') {
    if (item == 9) return true; // TAB
    return false;
  }
  if (item == 127) return false;
  return true;
}

BOL CHIsBlank(CHA item) {
  if (item <= ' ') {
    if (item == 9) return false; // TAB
    return true;
  }
  if (item == 127) return true;
  return false;
}

BOL CHIsBlank(CHB item) {
  if (item <= ' ') {
    if (item == 9) return false; // TAB
    return true;
  }
  if (item == 127) return true;
  return false;
}

BOL CHIsBlank(CHC item) {
  if (item <= ' ') {
    if (item == 9) return false; // TAB
    return true;
  }
  if (item == 127) return true;
  return false;
}

const CHA* STAPrintCharsHeader() {
  return "\n|0       8       16      24      32      40      48      56      |"
         " Begin address:";
}

const CHA* STAPrintCharsBorder() {
  return "\n|+-------+-------+-------+-------+-------+-------+-------+-------|"
         " ";
}

const CHA* STAPrintHexHeader() {
  return "\n|0               8               16              24              "
         "|  Begin address:";
}

const CHA* STAPrintHexBorder() {
  return "\n|+---------------+---------------+---------------+---------------|"
         " ";
}

}  //< namespace _

#if SEAM >= SCRIPT2_COUT
#if SEAM == SCRIPT2_COUT
#include "_Debug.h"
#else
#include "_Release.h"
#endif

namespace _ {

CHA* SPrint(CHA* string, CHA* stop, CHC item) {
  // | Byte 1   | Byte 2   | Byte 3   | Byte 4   | UTF-32 Result         |
  // |:--------:|:--------:|:--------:|:--------:|:---------------------:|
  // | 0aaaaaaa |          |          |          | 00000000000000aaaaaaa |
  // | 110aaaaa | 10bbbbbb |          |          | 0000000000aaaaabbbbbb |
  // | 1110aaaa | 10bbbbbb | 10cccccc |          | 00000aaaabbbbbbcccccc |
  // | 11110aaa | 10bbbbbb | 10cccccc | 10dddddd | aaabbbbbbccccccdddddd |

  if (!string) return NILP;

  D_COUT("\n\n" << IUC(item) << ".) Printed:0x");
  if (!(item >> 7)) { // 1 ASCII CHA.
    if (string + 1 > stop) return NILP;
    *string++ = CHA(item);
    D_COUT(Hexf(*(string - 1)) << "   ");
  } else {
    CHB lsb_mask = 0x3f, msb_mask = 0x80;
    if ((item >> 11) == 0) {
      if (string + 2 >= stop) return NILP;
      *string++ = CHA(0xC0 | (item >> 6));
      *string++ = CHA(msb_mask | (item & lsb_mask));
      D_COUT(Hexf(*(string - 2)) << '_' << Hexf(*(string - 1)) << "   ");
    } else if ((item >> 16) == 0) {
      if (string + 3 >= stop) return NILP;

      *string++ = CHA(0xE0 | (item >> 12));
      *string++ = CHA(msb_mask | ((item >> 6) & lsb_mask));
      *string++ = CHA(msb_mask | (item & lsb_mask));
      D_COUT(Hexf(*(string - 3)) << '_' << Hexf(*(string - 2)) << '_'
                                 << Hexf(*(string - 1)) << "   ");
    } else if ((item >> 21) == 0) {
      if (string + 4 >= stop) return NILP;
      *string++ = CHA(0xF0 | (item >> 18));
      *string++ = CHA(msb_mask | ((item >> 12) & lsb_mask));
      *string++ = CHA(msb_mask | ((item >> 6) & lsb_mask));
      *string++ = CHA(msb_mask | (item & lsb_mask));
      D_COUT(Hexf(*(string - 4))
             << '_' << Hexf(*(string - 3)) << '_' << Hexf(*(string - 2)) << '_'
             << Hexf(*(string - 1)) << "   ");
    } else {
      D_COUT("\n\nUTF8 print Error: CHC is out of range!");
      return NILP;
    }
  }
  *string = 0;
  return string;
}

const CHA* SScan(const CHA* string, CHC& item) {
  if (!string) return NILP;
  CHA c = CHC(*string++);
  CHC lsb_mask = 0x3f, msb = 0x80, result = 0;
  D_COUT("SScan:" << Hexf(c));
  if (!(c >> 7)) {
    result = CHC(c);
  } else if ((IUA(c) >> 5) == 6) {
    result = (c & 31) << 6;
    c = CHC(*string++);
    D_COUT(Hexf(c));
    if (!(c & msb)) return NILP;
    result |= c & CHC(63);
    D_COUT(Hexf(*(string - 1)));
  } else if ((IUA(c) >> 4) == 0xE) {
    result = CHC(c & 15) << 12;
    c = CHC(*string++);
    if (!(c & msb)) return NILP;
    result |= (c & 63) << 6;
    c = CHC(*string++);
    if (!(c & msb)) return NILP;
    result |= c & lsb_mask;
    D_COUT('_' << Hexf(*(string - 2)) << '_' << Hexf(*(string - 1)));
  } else if ((IUA(c) >> 3) == 0x1E) {
    result = CHC(c & 7) << 18;
    c = CHC(*string++);
    if (!(c & msb)) return NILP;
    result |= (c & lsb_mask) << 12;
    c = CHC(*string++);
    if (!(c & msb)) return NILP;
    result |= (c & lsb_mask) << 6;
    c = CHC(*string++);
    if (!(c & msb)) return NILP;
    result |= c & lsb_mask;
    D_COUT('_' << Hexf(*(string - 3)) << '_' << Hexf(*(string - 2)) << '_'
               << Hexf(*(string - 1)));
  } else {
    D_COUT(" error:0x" << Hexf(c) << '_' << Hexf(*string++) << '_'
                       << Hexf(*string++) << '_' << Hexf(*string++) << '\n');
    return NILP;
  }
  item = result;
  return string;
}

CHA* SPrint(CHA* start, CHA* stop, CHB item) {
  // | Byte 1   | Byte 2   | Byte 3   |  UTF-32 Result   |
  // |:--------:|:--------:|:--------:|:----------------:|
  // | 0aaaaaaa |          |          | 000000000aaaaaaa |
  // | 110aaaaa | 10bbbbbb |          | 00000aaaaabbbbbb |
  // | 1110aaaa | 10bbbbbb | 10cccccc | aaaabbbbbbcccccc |
#if USING_STC == YES_0
  return SPrint(start, stop, CHC(item));
#else
  enum { c2ByteMSbMask = 0xC0, c3ByteMSbMask = 0xE0, c4ByteMSbMask = 0xF0 };
  if (!start || start >= stop) return NILP;
  if (!(item >> 7)) {  // 1 byte.
    if (start + 1 > stop) return NILP;
    *start++ = CHA(item);
    *start = 0;
    return start;
  }
  CHB lsb_mask = 0x3f, msb_mask = 0x80;
  if (!(item >> 12)) {  // 2 bytes.
    if (start + 2 >= stop) return NILP;
    *start++ = (CHA)(0xC0 | item >> 6);
    *start++ = (CHA)(msb_mask | ((item >> 6) & lsb_mask));
    *start = 0;
    return start;
  }  // else 3 bytes.
  if (start + 3 >= stop) return NILP;
  *start++ = (CHA)(0xE0 | item >> 12);
  *start++ = (CHA)(msb_mask | ((item >> 6) & lsb_mask));
  *start++ = (CHA)(msb_mask | ((item >> 12) & lsb_mask));
  *start = 0;
  return start;
#endif
}
#if USING_STB == YES_0
CHB* SPrint(CHB* start, CHB* stop, CHC item) {
  // | Bytes {4N, 4N+ 1} | Bytes {4N + 2, 4N+ 3} |    UTF-32 Result     |
  // |:-----------------:|:---------------------:|:--------------------:|
  // | 000000aaaaaaaaaa  |                       | 0000000000aaaaaaaaaa |
  // | 110110yyyyyyyyyy  |   110111xxxxxxxxxx    | yyyyyyyyyyxxxxxxxxxx |
  // |      0xD800       |         0xDC00        |                      |
  if (!start || start + 1 >= stop) return NILP;
  CHC lsb_mask = 0x3f, lsb = item & lsb_mask, msb = item >> 10;
  if (!msb) {
    if (start + 1 > stop) return NILP;
    *start++ = CHB(item);
    D_COUT("\nPrinting 1:" << (Hexf(CHB(item))));
    *start = 0;
    return start;
  } else {
    CHC msb_mask = 0xDC00;
    if (msb >> 10) return NILP;  // Non-Unicode value.
    if (start + 2 >= stop) return NILP;
    CHB nibble = (CHB)(lsb & msb_mask);
    D_COUT("\nPrinting 2:" << Hexf(CHB(nibble)));
    *start++ = nibble;
    nibble = (CHB)(msb & msb_mask);
    D_COUT(Hexf(CHB(nibble)));
    *start++ = nibble;
    *start = 0;
    return start;
  }
}

const CHB* SScan(const CHB* string, CHC& item) {
  // | Bytes {4N, 4N+ 1} | Bytes {4N + 2, 4N+ 3} | UTF-32 Result        |
  // |:-----------------:|:---------------------:|:--------------------:|
  // | 000000aaaaaaaaaa  |                       | 0000000000aaaaaaaaaa |
  // | 110110aaaaaaaaaa  | 110111bbbbbbbbbb      | aaaaaaaaaabbbbbbbbbb |
  CHB c = *string++;
  CHB lsb_mask = (1 << 10) - 1;
  if (c <= lsb_mask) {
    D_COUT(" Scanning 1:" << Hexf(c));
    item = CHC(c);
  } else if ((c >> 10) == 30) {
    D_COUT(" Scanning 1:" << Hexf(c));
    CHC r = (CHC(c)) & lsb_mask;
    c = *string++;
    if (c >> 10 != 55) return NILP;
    r |= ((CHC)(c & lsb_mask)) << 10;
  } else {
    D_COUT(" SScan error:" << Hexf(c));
    return NILP;
  }
  return string;
}
#endif

ATypef::ATypef(DTB type, Sizef count) : count(count.size), type(type) {}
ATypef::ATypef(DTC type, Sizef count) : count(count.size), type(type) {}
ATypef::ATypef(DTD type, Sizef count) : count(count.size), type(type) {}

ATypef::ATypef(DTB pod, DTB vt, Sizef count) :
  count(count.size),
  type(ATypePack(pod, vt))
{}

ATypef::ATypef(DTB pod, DTB vt, DTB sw, Sizef count) :
  count(count.size),
  type(ATypePack(pod, vt, sw))
{}

ATypef::ATypef(DTB pod, DTB vt, DTB sw, DTB map, Sizef count) :
  count(count.size),
  type(ATypePack(pod, vt, sw, map))
{}

ATypef::ATypef(DTB pod, DTB vt, DTB sw, DTB map, DTB mod, Sizef count) :
  count(count.size),
  type(ATypePack(pod, vt, sw, map, mod))
{}


Centerf ATypef::Center(ISW count) {
  Centerf result;

  return result;
}

Rightf ATypef::Right(ISW count) {
  Rightf result;

  return result;
}

AErrorf::AErrorf(ISW error, const CHA* message) :
  error(error),
  message(message) {}

Valuef::Valuef() : count(0), value() {}

Valuef::Valuef(void* item, ISW count) : count(count), value(item) {}
Valuef::Valuef(const void* item, ISW count) : count(count), value(item) {}
#if USING_STA == YES_0
Valuef::Valuef(CHA item, ISW count) : count(count), value(item) {}
Valuef::Valuef(const CHA* item, ISW count) : count(count), value(item) {}
#endif
#if USING_STB == YES_0
Valuef::Valuef(CHB item, ISW count) : count(count), value(item) {}
Valuef::Valuef(const CHB* item, ISW count) : count(count), value(item) {}
#endif
#if USING_STC == YES_0
Valuef::Valuef(CHC item, ISW count) : count(count), value(item) {}
Valuef::Valuef(const CHC* item, ISW count) : count(count), value(item) {}
#endif
Valuef::Valuef(ISA item, ISW count) : count(count), value(item) {}
Valuef::Valuef(IUA item, ISW count) : count(count), value(item) {}
Valuef::Valuef(ISB item, ISW count) : count(count), value(item) {}
Valuef::Valuef(IUB item, ISW count) : count(count), value(item) {}
Valuef::Valuef(ISC item, ISW count) : count(count), value(item) {}
Valuef::Valuef(IUC item, ISW count) : count(count), value(item) {}
Valuef::Valuef(ISD item, ISW count) : count(count), value(item) {}
Valuef::Valuef(IUD item, ISW count) : count(count), value(item) {}
#if USING_FPC == YES_0
Valuef::Valuef(FPC item, ISW count) : count(count), value(item) {}
#endif
#if USING_FPD == YES_0
Valuef::Valuef(FPD item, ISW count) : count(count), value(item) {}
#endif

ISW Valuef::Type() { return value.Type(); }

ISW Valuef::Count() { return count; }

void* Valuef::Value() { return value.WordPTR(); }

void* Valuef::ToPtr() { return value.ToPTR(); }

CHA* Valuef::ToSTA() { return value.ToSTA(); }
CHB* Valuef::ToSTB() { return value.ToSTB(); }
CHC* Valuef::ToSTC() { return value.ToSTC(); }

IUW Valuef::ToWord() { return value.Value(); }

Hexf::Hexf(const void* origin, ISW size) : element(origin, size) {}
#if CPU_ENDIAN == CPU_ENDIAN_LITTLE
Hexf::Hexf(const void* item) : element(IUW(item), -ISW(sizeof(const void*))) {}
Hexf::Hexf(CHA item) : element(item, -ISW(sizeof(ISA))) {}
Hexf::Hexf(ISA item) : element(item, -ISW(sizeof(ISA))) {}
Hexf::Hexf(IUA item) : element(item, -ISW(sizeof(IUA))) {}
Hexf::Hexf(CHB item) : element(item, -ISW(sizeof(CHB))) {}
Hexf::Hexf(ISB item) : element(item, -ISW(sizeof(ISB))) {}
Hexf::Hexf(IUB item) : element(item, -ISW(sizeof(IUB))) {}
Hexf::Hexf(CHC item) : element(item, -ISW(sizeof(CHC))) {}
Hexf::Hexf(ISC item) : element(item, -ISW(sizeof(ISC))) {}
Hexf::Hexf(IUC item) : element(item, -ISW(sizeof(IUC))) {}
Hexf::Hexf(ISD item) : element(item, -ISW(sizeof(ISD))) {}
Hexf::Hexf(IUD item) : element(item, -ISW(sizeof(IUD))) {}
#if USING_FPC == YES_0
Hexf::Hexf(FPC item) : element(item, -ISW(sizeof(FPC))) {}
#endif
#if USING_FPD == YES_0
Hexf::Hexf(FPD item) : element(item, -ISW(sizeof(FPD))) {}
#endif

Binaryf::Binaryf(const void* origin, ISW size) : element(origin, size) {}
Binaryf::Binaryf(const void* item)
    : element(IUW(item), -ISW(sizeof(const void*))) {}
Binaryf::Binaryf(ISA item) : element(item, -ISW(sizeof(ISA))) {}
Binaryf::Binaryf(IUA item) : element(item, -ISW(sizeof(IUA))) {}
Binaryf::Binaryf(ISB item) : element(item, -ISW(sizeof(ISB))) {}
Binaryf::Binaryf(IUB item) : element(item, -ISW(sizeof(IUB))) {}
Binaryf::Binaryf(ISC item) : element(item, -ISW(sizeof(ISC))) {}
Binaryf::Binaryf(IUC item) : element(item, -ISW(sizeof(IUC))) {}
Binaryf::Binaryf(ISD item) : element(item, -ISW(sizeof(ISD))) {}
Binaryf::Binaryf(IUD item) : element(item, -ISW(sizeof(IUD))) {}
#if USING_FPC == YES_0
Binaryf::Binaryf(FPC item) : element(item, -ISW(sizeof(FPC))) {}
#endif
#if USING_FPD == YES_0
Binaryf::Binaryf(FPD item) : element(item, -ISW(sizeof(FPD))) {}
#endif
#else
Hexf::Hexf(const void* item) : valuef(item, sizeof(const void*)) {}
Hexf::Hexf(ISA item) : valuef(item, sizeof(ISA)) {}
Hexf::Hexf(IUA item) : valuef(item, sizeof(IUA)) {}
Hexf::Hexf(ISB item) : valuef(item, sizeof(ISB)) {}
Hexf::Hexf(IUB item) : valuef(item, sizeof(IUB)) {}
Hexf::Hexf(ISC item) : valuef(item, sizeof(ISC)) {}
Hexf::Hexf(IUC item) : valuef(item, sizeof(IUC)) {}
Hexf::Hexf(ISD item) : valuef(item, sizeof(ISD)) {}
Hexf::Hexf(IUD item) : valuef(item, sizeof(IUD)) {}
#if USING_FPD == YES_0
Hexf::Hexf(FPC item) : valuef(item, sizeof(FPC)) {}
#endif
#if USING_FPD == YES_0
Hexf::Hexf(FPD item) : valuef(item, sizeof(FPD)) {}
#endif

Binaryf::Binaryf(const void* origin, ISW size) : valuef(origin, size) {}
Binaryf::Binaryf(const void* origin) : valuef(origin, sizeof(const void*)) {}
Binaryf::Binaryf(ISA item) : valuef(item, sizeof(ISA)) {}
Binaryf::Binaryf(IUA item) : valuef(item, sizeof(IUA)) {}
Binaryf::Binaryf(ISB item) : valuef(item, sizeof(ISB)) {}
Binaryf::Binaryf(IUB item) : valuef(item, sizeof(IUB)) {}
Binaryf::Binaryf(ISC item) : valuef(item, sizeof(ISC)) {}
Binaryf::Binaryf(IUC item) : valuef(item, sizeof(IUC)) {}
Binaryf::Binaryf(ISD item) : valuef(item, sizeof(ISD)) {}
Binaryf::Binaryf(IUD item) : valuef(item, sizeof(IUD)) {}
#if USING_FPD == YES_0
Binaryf::Binaryf(FPC item) : valuef(item, sizeof(FPC)) {}
#endif
#if USING_FPD == YES_0
Binaryf::Binaryf(FPD item) : valuef(item, sizeof(FPD)) {}
#endif
#endif

// Stringf::Stringf () {}
Stringf::Stringf() : type_(_NIL), count_(0), boofer_() {
  string_ = &boofer_[0];
  *boofer_ = 0;
}
//< Visual C++ is complaining about unitialized members. I think it's a bug.

Stringf::Stringf(const CHA* item) : string_(item), count_(0) { Print(item); }
#if USING_STB == YES_0
Stringf::Stringf(const CHB* item) : string_(item), count_(0) { Print(item); }
#endif
#if USING_STC == YES_0
Stringf::Stringf(const CHC* item) : string_(item), count_(0) { Print(item); }
#endif
Stringf::Stringf(CHA item) : string_(boofer_), count_(0) { Print(item); }
Stringf::Stringf(CHB item) : string_(boofer_), count_(0) { Print(item); }
Stringf::Stringf(CHC item) : string_(boofer_), count_(0) { Print(item); }
Stringf::Stringf(ISC item) : string_(boofer_), count_(0) { Print(item); }
Stringf::Stringf(IUC item) : string_(boofer_), count_(0) { Print(item); }
Stringf::Stringf(ISD item) : string_(boofer_), count_(0) { Print(item); }
Stringf::Stringf(IUD item) : string_(boofer_), count_(0) { Print(item); }
#if USING_FPC == YES_0
Stringf::Stringf(FPC item) : string_(boofer_), count_(0) { Print(item); }
#endif
#if USING_FPD == YES_0
Stringf::Stringf(FPD item) : string_(boofer_), count_(0) { Print(item); }
#endif
Stringf::Stringf(const CHA* item, ISW count) : string_(item), count_(count) {
  Print(item);
}
#if USING_STB == YES_0
Stringf::Stringf(const CHB* item, ISW count) : string_(item), count_(count) {
  Print(item);
}
#endif
#if USING_STC == YES_0
Stringf::Stringf(const CHC* item, ISW count) : string_(item), count_(count) {
  Print(item);
}
#endif
Stringf::Stringf(CHA item, ISW count) : string_(boofer_), count_(count) {
  Print(item);
}
Stringf::Stringf(CHB item, ISW count) : string_(boofer_), count_(count) {
  Print(item);
}
Stringf::Stringf(CHC item, ISW count) : string_(boofer_), count_(count) {
  Print(item);
}
Stringf::Stringf(ISC item, ISW count) : string_(boofer_), count_(count) {
  Print(item);
}
Stringf::Stringf(IUC item, ISW count) : string_(boofer_), count_(count) {
  Print(item);
}
Stringf::Stringf(ISD item, ISW count) : string_(boofer_), count_(count) {
  Print(item);
}
Stringf::Stringf(IUD item, ISW count) : string_(boofer_), count_(count) {
  Print(item);
}
#if USING_FPC == YES_0
Stringf::Stringf(FPC item, ISW count) : string_(boofer_), count_(count) {
  Print(item);
}
#endif
#if USING_FPD == YES_0
Stringf::Stringf(FPD item, ISW count) : string_(boofer_), count_(count) {
  Print(item);
}
#endif

IUW Stringf::Word() { return boofer_[0]; }

void* Stringf::Value() { return boofer_; }

void* Stringf::Ptr() { return TPtr<void>(boofer_[0]); }

const CHA* Stringf::STA() { return TPtr<const CHA>(string_); }
const CHB* Stringf::STB() { return TPtr<const CHB>(string_); }
const CHC* Stringf::STC() { return TPtr<const CHC>(string_); }

ISW Stringf::Type() { return type_; }

ISW Stringf::Count() { return count_; }

void Stringf::Print(const CHA* item) {
  type_ = _STA;
  string_ = item;
}
#if USING_STB == YES_0
void Stringf::Print(const CHB* item) {
  type_ = _STB;
  string_ = item;
}
#endif
#if USING_STC == YES_0
void Stringf::Print(const CHC* item) {
  type_ = _STC;
  string_ = item;
}
#endif

void Stringf::Print(CHA item) {
  CHA* boofer = TPtr<CHA>(boofer_);
  ::_::SPrint(boofer, boofer + LengthMax, item);
  type_ = _STA;
  string_ = boofer_;
}

#if USING_STB == YES_0
void Stringf::Print(CHB item) {
  CHA* boofer = TPtr<CHA>(boofer_);
  ::_::SPrint(boofer, boofer + LengthMax, item);
  type_ = _STA;
  string_ = boofer_;
}
#endif
#if USING_STC == YES_0
void Stringf::Print(CHC item) {
  CHA* boofer = TPtr<CHA>(boofer_);
  ::_::SPrint(boofer, boofer + LengthMax, item);
  type_ = _STA;
  string_ = boofer;
}
#endif
void Stringf::Print(ISC item) {
  CHA* boofer = TPtr<CHA>(boofer_);
#if SEAM >= SCRIPT2_ITOS
  ::_::TSPrint<CHA>(boofer, boofer + LengthMax, item);
#endif
  type_ = _STA;
  string_ = boofer;
}

void Stringf::Print(IUC item) {
  CHA* boofer = TPtr<CHA>(boofer_);
#if SEAM >= SCRIPT2_ITOS
  ::_::TSPrint<CHA>(boofer, boofer + LengthMax, item);
#endif
  type_ = _STA;
  string_ = boofer;
}

void Stringf::Print(ISD item) {
  CHA* boofer = TPtr<CHA>(boofer_);
#if SEAM >= SCRIPT2_ITOS
  ::_::TSPrint<CHA>(boofer, boofer + LengthMax, item);
#endif
  type_ = _STA;
  string_ = boofer;
}

void Stringf::Print(IUD item) {
  CHA* boofer = TPtr<CHA>(boofer_);
#if SEAM >= SCRIPT2_ITOS
  ::_::TSPrint<CHA>(boofer, boofer + LengthMax, item);
#endif
  type_ = _STA;
  string_ = boofer;
}

#if USING_FPC == YES_0
void Stringf::Print(FPC item) {
  CHA* boofer = TPtr<CHA>(boofer_);
  ::_::TSPrint<CHA>(boofer, boofer + LengthMax, item);
  type_ = _STA;
  string_ = boofer;
}
#endif
#if USING_FPD == YES_0
void Stringf::Print(FPD item) {
  CHA* boofer = TPtr<CHA>(boofer_);
  ::_::TSPrint<CHA>(boofer, boofer + LengthMax, item);
  type_ = _STA;
  string_ = boofer;
}
#endif

/*
void Stringf::PrintTMC(TMC item) {}

void Stringf::PrintTME(TMC item, IUC subsecond_tick) {}

void Stringf::PrintTMD(TMD item) {}

void Stringf::Print(ATypef item) {
  CHA* boofer = TPtr<CHA>(boofer_);
#if SEAM >= SCRIPT2_ITOS
  ::_::TSPrint<CHA>(boofer, boofer + LengthMax, item);
#endif
  type_ = item.type;
  string_ = boofer;
}

void Stringf::Print(TypeValue item) {
  DTW type = item.Type();
  type_ = type;
  static const CHA NotSupported[] = "Not supported\0";
  DTW pod_type = type & ATypePODMask;
  if (type != pod_type) {  // It's not a POD type.
  }
  switch (type) {
    case _NIL:
      // CHC c = 2205; // Empty-set Unicode character.
      return;
    case _CHA:
      Print(CHA(item.ToIUA()));
      return;
    case _ISA:
      Print(ISA(item.ToIUA()));
      return;
    case _IUA:
      Print((item.ToIUA()));
      return;
    case _CHB:
      Print(CHB(item.ToIUB()));
      return;
    case _ISB:
      Print(ISB(item.ToIUB()));
      return;
    case _IUB:
      Print(item.ToIUB());
      return;
    case _FPB:
      Print(item.ToIUB());
      return;
    case _CHC:
      Print(CHC(item.ToIUC()));
      return;
    case _ISC:
      Print(ISC(item.ToIUC()));
      return;
    case _IUC:
      Print(IUC(item.ToIUC()));
      return;
    case _FPC:
#if USING_FPC == YES_0
      Print(ToFloat(item.ToIUC()));
#endif
      return;
    case _TME:
      PrintTME(ISC(item.Word()), IUC(item.Word2()));
    case _ISD:
      Print(ISD(item.ToUID()));
      return;
    case _IUD:
      Print(item.ToUID());
      return;
    case _FPD:
#if USING_FPD == YES_0
      Print(ToFloat(item.ToUID()));
#endif
      return;
  }
  string_ = NotSupported;
}

Stringf::Stringf(ATypef item, ISW count) : string_(boofer_), count_(count) {
  Print(item);
}
Stringf::Stringf(TypeValue item, ISW count) : string_(boofer_), count_(count) {
  Print(item);
}*/

void Stringf::Hex(CHA item, ISW count) {
  *TPtr<CHA>(boofer_) = item;
  type_ = _CHA;
  count_ = -count;
}
#if USING_STB == YES_0
void Stringf::Hex(CHB item, ISW count) {
  *TPtr<CHB>(boofer_) = item;
  type_ = _CHB;
  count_ = -count;
}
#endif
#if USING_STC == YES_0
void Stringf::Hex(CHC item, ISW count) {
  *TPtr<CHC>(boofer_) = item;
  type_ = _CHC;
  count_ = -count;
}
#endif
void Stringf::Hex(ISA item, ISW count) {
  *TPtr<ISA>(boofer_) = item;
  type_ = _ISA;
  count_ = -count;
}
void Stringf::Hex(IUA item, ISW count) {
  *TPtr<IUA>(boofer_) = item;
  type_ = _IUA;
  count_ = -count;
}

void Stringf::Hex(ISB item, ISW count) {
  *TPtr<ISB>(boofer_) = item;
  type_ = _ISB;
  count_ = -count;
}

void Stringf::Hex(IUB item, ISW count) {
  *TPtr<IUB>(boofer_) = item;
  type_ = _IUB;
  count_ = -count;
}

void Stringf::Hex(ISC item, ISW count) {
  *TPtr<ISC>(boofer_) = item;
  type_ = _ISC;
  count_ = -count;
}

void Stringf::Hex(IUC item, ISW count) {
  *TPtr<IUC>(boofer_) = item;
  type_ = _IUC;
  count_ = -count;
}

void Stringf::Hex(ISD item, ISW count) {
  *TPtr<ISD>(boofer_) = item;
  type_ = _ISD;
  count_ = -count;
}

void Stringf::Hex(IUD item, ISW count) {
  *TPtr<IUD>(boofer_) = item;
  type_ = _IUD;
  count_ = -count;
}

#if USING_FPC == YES_0
void Stringf::Hex(FPC item, ISW count) {
  *TPtr<FPC>(boofer_) = item;
  type_ = _FPC;
  count_ = -count;
}
#endif

#if USING_FPD == YES_0
void Stringf::Hex(FPD item, ISW count) {
  *TPtr<FPD>(boofer_) = item;
  type_ = _FPD;
  count_ = -count;
}
#endif

Centerf::Centerf() {}

#if USING_STA == YES_0
Centerf::Centerf(CHA item, ISW count) : element(item, count) {}
Centerf::Centerf(const CHA* item, ISW count) : element(item, count) {}
#endif
#if USING_STB == YES_0
Centerf::Centerf(CHB item, ISW count) : element(item, count) {}
Centerf::Centerf(const CHB* item, ISW count) : element(item, count) {}
#endif
#if USING_STC == YES_0
Centerf::Centerf(CHC item, ISW count) : element(item, count) {}
Centerf::Centerf(const CHC* item, ISW count) : element(item, count) {}
#endif
Centerf::Centerf(ISC item, ISW count) : element(item, count) {}
Centerf::Centerf(IUC item, ISW count) : element(item, count) {}
Centerf::Centerf(ISD item, ISW count) : element(item, count) {}
#if USING_FPC == YES_0
Centerf::Centerf(FPC item, ISW count) : element(item, count) {}
#endif
#if USING_FPD == YES_0
Centerf::Centerf(FPD item, ISW count) : element(item, count) {}
#endif
Centerf::Centerf(IUD item, ISW count) : element(item, count) {}
//Centerf::Centerf(ATypef item, ISW count) : element(item, count) {}

Centerf& Centerf::Hex(CHA item, ISW count) {
  element.Hex(item, count);
  return *this;
}
#if USING_STB == YES_0
Centerf& Centerf::Hex(CHB item, ISW count) {
  element.Hex(item, count);
  return *this;
}
#endif
#if USING_STC == YES_0
Centerf& Centerf::Hex(CHC item, ISW count) {
  element.Hex(item, count);
  return *this;
}
#endif
Centerf& Centerf::Hex(ISA item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Centerf& Centerf::Hex(IUA item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Centerf& Centerf::Hex(ISB item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Centerf& Centerf::Hex(IUB item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Centerf& Centerf::Hex(ISC item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Centerf& Centerf::Hex(IUC item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Centerf& Centerf::Hex(ISD item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Centerf& Centerf::Hex(IUD item, ISW count) {
  element.Hex(item, count);
  return *this;
}
#if USING_FPC == YES_0
Centerf& Centerf::Hex(FPC item, ISW count) {
  element.Hex(item, count);
  return *this;
}
#endif
#if USING_FPD == YES_0
Centerf& Centerf::Hex(FPD item, ISW count) {
  element.Hex(item, count);
  return *this;
}
#endif

Rightf::Rightf() {}
Rightf::Rightf(CHA item, ISW count) : element(item, count) {}
Rightf::Rightf(const CHA* item, ISW count) : element(item, count) {}
#if USING_STB == YES_0
Rightf::Rightf(CHB item, ISW count) : element(item, count) {}
Rightf::Rightf(const CHB* item, ISW count) : element(item, count) {}
#endif
#if USING_STC == YES_0
Rightf::Rightf(CHC item, ISW count) : element(item, count) {}
Rightf::Rightf(const CHC* item, ISW count) : element(item, count) {}
#endif
Rightf::Rightf(ISC item, ISW count) : element(item, count) {}
Rightf::Rightf(IUC item, ISW count) : element(item, count) {}
Rightf::Rightf(ISD item, ISW count) : element(item, count) {}
Rightf::Rightf(IUD item, ISW count) : element(item, count) {}
#if USING_FPC == YES_0
Rightf::Rightf(FPC item, ISW count) : element(item, count) {}
#endif
#if USING_FPD == YES_0
Rightf::Rightf(FPD item, ISW count) : element(item, count) {}
#endif

Rightf& Rightf::Hex(CHA item, ISW count) {
  element.Hex(item, count);
  return *this;
}
#if USING_STB == YES_0
Rightf& Rightf::Hex(CHB item, ISW count) {
  element.Hex(item, count);
  return *this;
}
#endif
#if USING_STC == YES_0
Rightf& Rightf::Hex(CHC item, ISW count) {
  element.Hex(item, count);
  return *this;
}
#endif
Rightf& Rightf::Hex(ISA item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Rightf& Rightf::Hex(IUA item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Rightf& Rightf::Hex(ISB item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Rightf& Rightf::Hex(IUB item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Rightf& Rightf::Hex(ISC item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Rightf& Rightf::Hex(IUC item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Rightf& Rightf::Hex(ISD item, ISW count) {
  element.Hex(item, count);
  return *this;
}
Rightf& Rightf::Hex(IUD item, ISW count) {
  element.Hex(item, count);
  return *this;
}
#if USING_FPC == YES_0
Rightf& Rightf::Hex(FPC item, ISW count) {
  element.Hex(item, count);
  return *this;
}
#endif
#if USING_FPD == YES_0
Rightf& Rightf::Hex(FPD item, ISW count) {
  element.Hex(item, count);
  return *this;
}
#endif

Linef::Linef(CHA item, ISW count) : element(string, count), string("") {
  CHA* cursor = string;
  *cursor++ = '\n';
  *cursor++ = item;
  *cursor++ = item;
  *cursor++ = item;
  *cursor = 0;
}
Linef::Linef(const CHA* item, ISW count) : element(item, count), string("") {}

Headingf::Headingf(const CHA* caption1)
    : element(caption1, AConsoleWidth),
      style(NILP),
      caption2(NILP),
      caption3(NILP) {}

Headingf::Headingf(const CHA* caption1, const CHA* caption2)
    : element(caption1, AConsoleWidth),
      style(NILP),
      caption2(caption2),
      caption3(NILP) {}

Headingf::Headingf(const CHA* caption1, const CHA* caption2,
                   const CHA* caption3, const CHA* style, ISW count)
    : element(caption1, count),
      style(style),
      caption2(caption2),
      caption3(caption3) {}

Charsf::Charsf(const void* start, const void* stop)
    : element(TPtr<const CHA>(start),
              TPtr<const CHA>(stop) - TPtr<const CHA>(start)) {}
Charsf::Charsf(const void* start, ISW count)
    : element(TPtr<const CHA>(start), count) {}

#if USING_STB == YES_0
Charsf::Charsf(const CHB* start, const CHB* stop)
    : element(start, stop - start) {}
Charsf::Charsf(const CHB* start, ISW count) : element(start, count) {}
#endif
#if USING_STC == YES_0
Charsf::Charsf(const CHC* start, const CHC* stop)
    : element(start, stop - start) {}
Charsf::Charsf(const CHC* start, ISW count) : element(start, count) {}
#endif

Indentf::Indentf(ISW indent_count) : indent_count(indent_count) {}

Sizef::Sizef(ISA size) : size(size) {}
Sizef::Sizef(ISB size) : size(size) {}
Sizef::Sizef(ISC size) : size(size) {}
Sizef::Sizef(ISD size) : size(size) {}

}  //< namespace _

#if SEAM >= SCRIPT2_FTOS
#if SEAM == SCRIPT2_FTOS
#include "_Debug.h"
#else
#include "_Release.h"
#endif

#include <cstdio>  // For sprintf_s

namespace _ {

CHA* SPrint(CHA* string, CHA* stop, FPC value) {
  if (!string || string >= stop) return NILP;
  ISW size = stop - string;
  D_COUT("\nString:" << Hexf(string) << " end:" << Hexf(stop) << 
         " size:" << size << "\nExpecting:" << value);
  ISC count = sprintf_s(string, stop - string, "%f", value);
  if (count <= 0) return NILP;
  return string + count;
}

#if USING_FPD == YES_0
CHA* SPrint(CHA* start, CHA* stop, FPD value) {
  if (!start || start >= stop) return NILP;
  ISW size = stop - start;
  ISC count = sprintf_s(start, size, "%lf", value);
  if (count <= 0) return NILP;
  return start + count;
}
#endif
#if USING_FPC == YES_0
const CHA* SScan(const CHA* start, FPC& value) {
  ISC count = sscanf_s(start, "%f", &value);
  return TStringFloatStop<CHA>(start);
}
#endif
const CHA* SScan(const CHA* start, FPD& value) {
  ISC count = sscanf_s(start, "%lf", &value);
  return TStringFloatStop<CHA>(start);
}
}  //< namespace _
#endif
#endif
