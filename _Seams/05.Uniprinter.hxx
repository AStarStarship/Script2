// Copyright Kabuki Starship <kabukistarship.com>.
#if SEAM >= SCRIPT2_UNIPRINTER
#include "../Uniprinter.hpp"
#include "../Array.hpp"
#if SEAM == SCRIPT2_UNIPRINTER
#include "../_Debug.h"
#else
#include "../_Release.h"
#endif
#endif

using namespace ::_;
namespace Script2 {
#if SEAM >= SCRIPT2_UNIPRINTER
template<typename CHT = CHR, typename IS = ISR>
static const CHA* TestSPrinterCH() {
  D_COUT(Linef('-') << "\n\n\nTesting UTF<CH" << CSizeCodef<CHT>() << ",IS"
                    << sizeof(IS) << ">\n\n"
                    << Linef('-'));
  enum {
    Count = ATypeCodomainTotal,
  };
  CHT str_a[Count];
  static const CHT Testing123[] = { 'T', 'e', 's', 't', 'i', 'n',
                                     'g', ' ', '1', ',', ' ', '2',
                                     ',', ' ', '3', '.', NIL };

  D_RAM_WIPE(str_a, Count * sizeof(CHT));
  TSPrint<CHT>(str_a, Count, Testing123);
  D_COUT(Charsf(str_a, 64));

  TSPrinter<CHT, IS> utf(str_a, Count);

  enum { TestStringsCount = 4 };

  const CHT TestStrings[5][2][7] = {{{'?', NIL, NIL, NIL, NIL, NIL, NIL},
                                     {NIL, NIL, NIL, NIL, NIL, NIL, NIL}},
                                    {{'?', NIL, NIL, NIL, NIL, NIL, NIL},
                                     {'?', NIL, NIL, NIL, NIL, NIL, NIL}},
                                    {{'?', ' ', NIL, NIL, NIL, NIL, NIL},
                                     {'?', NIL, NIL, NIL, NIL, NIL, NIL}},
                                    {{'A', 'p', 'p', 'l', 'e', 's', NIL},
                                     {'A', 'p', 'p', 'l', 'e', 's', NIL}},
                                    {{'A', 'p', 'p', 'l', 'e', 's', NIL},
                                     {'A', 'p', 'p', 'l', 'e', 's', NIL}}};
  const CHT* cursor;
  for (ISC i = 0; i < TestStringsCount; ++i) {
    D_RAM_WIPE(str_a, Count * sizeof(CHT));
    cursor = TSPrintString<CHT>(str_a, str_a + Count, TestStrings[i][0]);
    D_COUT(Charsf(str_a, 64));
    Test(cursor);
    cursor = TStringEquals<CHT>(str_a, TestStrings[i][0]);
    Test(cursor);
  }

  D_COUT(Headingf("Testing TSPrinter<CHT, ISZ>") <<
         "\n\nExpecting \"" << Testing123 << '\"');
  static const CHT CommaSpace[] = {',', ' ', NIL};

  const CHT TestingSpace[] = {'T', 'e', 's', 't', 'i', 'n', 'g', ' ', NIL};

  D_RAM_WIPE(str_a, Count * sizeof(CHT));

  utf.Set(str_a).Print(TestingSpace);
  utf.Print(1);
  utf.Print(CommaSpace);
  utf.Print(2);
  utf.Print(", ");
  utf.Print(3);
  utf.Print('.');

  utf.Set(str_a) << TestingSpace << 1 << CommaSpace << 2 << ", " << 3 << '.';
  D_COUT(Charsf(str_a, 64));
  A_AVOW(Testing123, str_a);

  D_COUT("\n\nTesting TStringEquals<CHT>");

  const CHT CompareStrings[4][9] = {
      {'T', 'e', 's', 't', 'i', 'n', 'g', NIL, NIL},
      {'T', 'e', 'x', 't', 'i', 'n', 'g', NIL, NIL},
      {'T', 'e', 's', 't', 'i', 'n', 'g', '@', NIL},
      {'T', 'e', 'x', 't', 'i', 'n', 'g', '@', NIL},
  };

  A_ASSERT(!TStringEquals<CHT>(CompareStrings[0], CompareStrings[1]));
  A_ASSERT(!TStringEquals<CHT>(CompareStrings[0], CompareStrings[3]));
  A_ASSERT( TStringEquals<CHT>(CompareStrings[0], CompareStrings[0]));
  A_ASSERT(!TStringEquals<CHT>(CompareStrings[2], CompareStrings[3]));
  A_ASSERT( TStringEquals<CHT>(CompareStrings[2], CompareStrings[2]));

  const CHT Chars1to9[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', NIL};
  A_AVOW(9, TStringLength<CHT>(Chars1to9));

  D_COUT("\n\nTesting TStringFind<CHT>");

  const CHT One[] = {'1', ',', NIL};
  const CHT ThreePeriod[] = {'3', '.', NIL};
  A_ASSERT(TStringFind<CHT>(Testing123, One));
  A_ASSERT(TStringFind<CHT>(Testing123, ThreePeriod));

  D_COUT(Headingf("Testing TPrintRight<CHT>"));

  const CHT RightAligned[12][13] = {
      {'.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'T', '.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'T', 'e', '.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'T', 'e', 's', '.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'T', 'e', 's', 't', '.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL},
      {'T', 'e', 's', 't', 'i', 'n', 'g', ' ', NIL, NIL, NIL, NIL, NIL},
      {' ', 'T', 'e', 's', 't', 'i', 'n', 'g', ' ', NIL, NIL, NIL, NIL},
      {' ', ' ', 'T', 'e', 's', 't', 'i', 'n', 'g', ' ', NIL, NIL, NIL},
      {' ', ' ', ' ', 'T', 'e', 's', 't', 'i', 'n', 'g', ' ', NIL, NIL},
      {' ', ' ', ' ', ' ', 'T', 'e', 's', 't', 'i', 'n', 'g', ' ', NIL}};

  ISC shift_right = 6;
  for (ISC i = 0; i < 12; ++i) {
    D_RAM_WIPE(str_a, (ISW)(Count * sizeof(CHT)));
    cursor = TPrintRight<CHT>(str_a, str_a + Count - 1, TestingSpace, i + 1);
    D_ASSERT_INDEX(cursor, i);
    D_COUT(Charsf(str_a, 64)
           << "\n    Wrote:\"" << str_a << "\":" << TStringLength<CHT>(str_a));
    A_AVOW_INDEX(&RightAligned[i][0], str_a, i);
  }
  D_COUT(Headingf("Testing TPrintCenter<CHT>"));

  const CHT CenterAligned[13][14] = {
      {'.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'1', '.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'1', '2', '.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'1', '2', '3', '.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'1', '2', '3', '4', '.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL, NIL},
      {'1', '2', '3', '4', '5', '.', '.', '.', NIL, NIL, NIL, NIL, NIL, NIL},
      {'1', '2', '3', '4', '5', '6', '7', '8', '9', NIL, NIL, NIL, NIL, NIL},
      {'1', '2', '3', '4', '5', '6', '7', '8', '9', ' ', NIL, NIL, NIL, NIL},
      {' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ', NIL, NIL, NIL},
      {' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ', ' ', NIL, NIL},
      {' ', ' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ', ' ', NIL}};

  static const CHT Numbers1To9[] = {'1', '2', '3', '4', '5',
                                    '6', '7', '8', '9', NIL};

  for (ISC i = 12; i >= 0; --i) {
    D_RAM_WIPE(str_a, Count * sizeof(CHT));
    cursor = TPrintCenter<CHT>(str_a, str_a + Count - 1, Numbers1To9, i + 1);
    D_ASSERT_INDEX(cursor, i);
    D_COUT(Charsf(str_a, 64)
           << "\n    Wrote:\"" << str_a << "\":" << TStringLength<CHT>(str_a));
    A_AVOW_INDEX(&CenterAligned[i][0], str_a, i);
  }

  return NILP;
}

static const CHA* TestSPrinter() {
#if USING_STA == YES_0
  { const CHA* result = TestSPrinterCH<CHA, ISC>(); if (result) return result; }
#endif
#if USING_STB == YES_0
  { const CHA* result = TestSPrinterCH<CHB, ISC>(); if (result) return result; }
#endif
#if USING_STC == YES_0
  { const CHA* result = TestSPrinterCH<CHC, ISC>(); if (result) return result; }
#endif
  return NILP;
}

static const CHA* TestATypefARY() {
  D_COUT("\nPrinting ARY types...");
  const ISW CTotal = 1024;
  CHA boofer[CTotal] = {};
  TSPrinter<CHA, ISW> p(boofer, CTotal);

  for (DTB i = 1; i < 32; ++i) {
    DTB vt_bits = 1 << ATypeVTBit0;
    D_COUT('\n' << i << ':');
    DTB t_0 = i | vt_bits,
        t_1 = (1 << ATypeSWBit0) | t_0,
        t_2 = (2 << ATypeSWBit0) | t_0,
        t_3 = (3 << ATypeSWBit0) | t_0;
    D_COUT('\n' << i << ':' <<
           "\n    0x" << Hexf(t_0) << ' ' <<
           ATypef(t_0) <<
           "\n    0x" << Hexf(t_1) << ' ' <<
           ATypef(t_1) << 
           "\n    0x" << Hexf(t_2) << ' ' <<
           ATypef(t_2) << 
           "\n    0x" << Hexf(t_3) << ' ' <<
           ATypef(t_3));
  }
  return NILP;
}

static const CHA* TestATypefVHT() {
  D_COUT("\n\nPrinting VHT types...");
  const ISW CTotal = 1024;
  CHA boofer[CTotal] = {};
  TSPrinter<CHA, ISW> p(boofer, CTotal);

  for (DTB i = 1; i < 32; ++i) {
    DTB t_1 = (1 << ATypeSWBit0) | i,
        t_2 = (2 << ATypeSWBit0) | i,
        t_3 = (3 << ATypeSWBit0) | i;
    D_COUT('\n' << i << ':' <<
           "\n    0x" << Hexf(i) << ' ' <<
           ATypef(i) <<
           "\n    0x" << Hexf(t_1) << ' ' <<
           ATypef(t_1) << 
           "\n    0x" << Hexf(t_2) << ' ' <<
           ATypef(t_2) << 
           "\n    0x" << Hexf(t_3) << ' ' <<
           ATypef(t_3));
  }
  return NILP;
}

static const CHA* TestATypefSCK() {
  D_COUT("\n\nPrinting SCK types...");
  const ISW CTotal = 1024;
  CHA boofer[CTotal] = {};
  TSPrinter<CHA, ISW> p(boofer, CTotal);

  for (DTB i = 1; i < ATypePODTotal; ++i) {
    DTB vt_bits = _SCK << ATypeVTBit0,
        t_0 = vt_bits | i,
        t_1 = (1 << ATypeSWBit0) | t_0,
        t_2 = (2 << ATypeSWBit0) | t_0,
        t_3 = (3 << ATypeSWBit0) | t_0;
    D_COUT('\n' << i << ':' <<
           "\n    0x" << Hexf(t_0) << ' ' <<
           ATypef(t_0) <<
           "\n    0x" << Hexf(t_1) << ' ' <<
           ATypef(t_1) << 
           "\n    0x" << Hexf(t_2) << ' ' <<
           ATypef(t_2) << 
           "\n    0x" << Hexf(t_3) << ' ' <<
           ATypef(t_3));
  }
  return NILP;
}

static const CHA* TestATypefMTX() {
  D_COUT("\n\nPrinting MTX types...");
  const ISW CTotal = 1024;
  CHA boofer[CTotal] = {};
  TSPrinter<CHA, ISW> p(boofer, CTotal);

  for (DTB i = 1; i < ATypePODTotal; ++i) {
    DTB t_0 = (_MTX << ATypeVTBit0) | i,
        t_1 = (1 << ATypeSWBit0) | t_0,
        t_2 = (2 << ATypeSWBit0) | t_0,
        t_3 = (3 << ATypeSWBit0) | t_0;
    D_COUT('\n' << i << ':' <<
           "\n    0x" << Hexf(t_0) << ' ' <<
           ATypef(t_0) <<
           "\n    0x" << Hexf(t_1) << ' ' <<
           ATypef(t_1) << 
           "\n    0x" << Hexf(t_2) << ' ' <<
           ATypef(t_2) << 
           "\n    0x" << Hexf(t_3) << ' ' <<
           ATypef(t_3));
  }
  return NILP;
}

static const CHA* TestATypeMaps() {
  D_COUT("\n\nTesting MAP types...");
  const ISW CTotal = 1024;
  CHA boofer[CTotal] = {};
  TSPrinter<CHA, ISW> p(boofer, CTotal);
  const DTB Step = 8;
  for (DTB map_type = 1; map_type < ATypePODTotal; map_type += Step) {
    D_COUT("\nMap of " << TATypePODs<>(map_type) << " to:");
    for (DTB pod_type = 1; pod_type < ATypePODTotal; ++pod_type) {
      DTB type = (pod_type << ATypeMTBit0) | _IUA;
      D_COUT("\n  " << ATypef(type));
    }
  }
  return NILP;
}

static const DTB TestATypeEXTContains(DTB* ext_start, DTB* ext_stop, DTB type) {
  while (ext_start < ext_stop) {
    DTB t = *ext_start++;
    if (type == t) return t;
  }
  return 0;
}

static const CHA* TestATypeEXT() {
  D_COUT("\n\nTesting Extended Types...");
  const ISW CTotal = 1024;
  DTB t = 0;
  D_COUT("\n\nTesting Plain Context types...");

  D_COUT("\nTesting Block A.Bottom...");
  for (DTB sw_vt = 1; sw_vt <= 3; ++sw_vt) {
    for (DTB pod = _PCe; pod <= _PCl; ++pod) {
      A_AVOW(t++, ATypeToEXT(sw_vt, pod));
    }
  }
  D_COUT("\nTesting Block C...");
  for (DTB sw_vt = 10; sw_vt <= 11; ++sw_vt) {
    for (DTB pod = _PCa; pod <= _PCd; ++pod)
      A_AVOW(t++, ATypeToEXT(sw_vt, pod));
  }
  D_COUT("\nTesting Block A.Middle...");
  for (DTB sw_vt = 5; sw_vt <= 7; ++sw_vt) {
    for (DTB pod = _PCe; pod <= _PCl; ++pod)
      A_AVOW(t++, ATypeToEXT(sw_vt, pod));
  }
  D_COUT("\nTesting Block D...");
  for (DTB sw_vt = 6; sw_vt <= 7; ++sw_vt) {
    for (DTB pod = _PCa; pod <= _PCd; ++pod)
      A_AVOW(t++, ATypeToEXT(sw_vt, pod));
  }
  D_COUT("\nTesting Block A.Top...");
  for (DTB sw_vt = 9; sw_vt <= 1; ++sw_vt) {
    for (DTB pod = _PCe; pod <= _PCl; ++pod)
      A_AVOW(t++, ATypeToEXT(sw_vt, pod));
  }
  D_COUT("\nTesting Block B.Bottom...");
  for (DTB sw_vt = 1; sw_vt <= 3; ++sw_vt) {
    for (DTB pod = _PCa; pod <= _PCd; ++pod)
      A_AVOW(t++, ATypeToEXT(sw_vt, pod));
  }
  D_COUT("\nTesting Block E...");
  for (DTB pod = _PCa; pod <= _PCd; ++pod) {
    A_AVOW(t++, ATypeToEXT(9, pod));
  }
  D_COUT("\nTesting Block B.Top...");
  for (DTB pod = _PCa; pod <= _PCd; ++pod) {
    A_AVOW(t++, ATypeToEXT(5, pod));
  }

  D_COUT("\n\nTesting Extended Standard types...");
  t = 0;

  D_COUT("\nTesting Block F.Bottom...");
  for (DTB sw_vt = 1; sw_vt <= 3; ++sw_vt) {
    for (DTB pod = _FPD; pod <= _TME; ++pod)
      A_AVOW(t--, ATypeToEXT(sw_vt, pod));
  }
  D_COUT("\nTesting Block H...");
  for (DTB pod = _FPB; pod <= _CHB; ++pod)
    A_AVOW(t--, ATypeToEXT(1, pod));
  for (DTB pod = _FPC; pod <= _CHC; ++pod)
    A_AVOW(t--, ATypeToEXT(5, pod));

  D_COUT("\nTesting Block F.Top...");
  for (DTB pod = _FPD; pod <= _TME; ++pod)
    A_AVOW(t--, ATypeToEXT(5, pod));

  D_COUT("\nTesting Block G...");
  for (DTB sw_vt = 1; sw_vt <= 3; ++sw_vt) {
    for (DTB pod = _FPC; pod <= _CHC; ++pod) {
      A_AVOW(t--, ATypeToEXT(sw_vt, pod));
    }
  }

  D_COUT("\n\nTesting Standard Types...");
  DTB nonextended_bounds[16] = {
    _PCl,
    _CHA,
    _CHB,
    _CHB,
    _PCl,
    _CHB,
    _TME,
    _TME,
    _PCl,
    _TME,
    _TME,
    _TME,
    _PCl,
    _PCl,
    _PCl,
    _PCl
  };
  for (DTB sw_vt = 0; sw_vt <= 15; ++sw_vt) {
    DTB last_nonextended = nonextended_bounds[sw_vt];
    DTB pod = 0;
    for (; pod <= last_nonextended; ++pod) {
      A_AVOW(DTB(0), ATypeToEXT(sw_vt, pod));
    }
    if(sw_vt < 12 && sw_vt & 3) {
      for (; pod <= _TME; ++pod) {
        if (!(sw_vt == 1 && pod == _FPD)) {
          DTB result = ATypeToEXT(sw_vt, pod);
          A_ASSERT(result < 0);
        }
      }
      for (; pod <= _PCl; ++pod) {
        if(!(sw_vt == 1 && pod == _PCe)) {
          DTB result = ATypeToEXT(sw_vt, pod);
          A_ASSERT(result > 0);
        }
      }
    }
  }

  return NILP;
}

static const CHA* TestPrintAType() {
  D_COUT("\n\nTesting ATypef...");
  //A_RUN_TEST(TestATypefVHT);
  //A_RUN_TEST(TestATypefARY);
  //A_RUN_TEST(TestATypefSCK);
  //A_RUN_TEST(TestATypefMTX);
  //A_RUN_TEST(TestATypeMaps);
  A_RUN_TEST(TestATypeEXT);
  return NILP;
}

static const CHA* TestProblemChildren() {
  static const ISD problem_children[29] = {
    420, 4200, 42000, 420000, 4200000, 9999999, 10000000, 12000000,
    13000000, 12321959, 12321960, 13000000, 16500000, 16800000,
    16777216,16777217,
    17000000, 19999990, 20000000, 30000000, 40000000, 50000000, 60000000,
    70000000, 80000000, 90000000, 99999999, 100000000, 1000000000
  };
  // length 8 range: 10000000 to 16777216
  CHA boofer[1024];
  TSPrinter<CHA> p(boofer, 1024);
  D_COUT(boofer);
  for (ISN dddddez = 11; dddddez < 27; ++dddddez) {
    auto nutz_in_yo_mouth = problem_children[dddddez];
    D_COUT("\n\ndddddez ");
    D_COUT(nutz_in_yo_mouth);
    p << "\nnutz in your face: " << nutz_in_yo_mouth << '\n';
    D_COUT(boofer);
    p.Reset();
  }
  return NILP;
}

#endif  //< #if SEAM >= SCRIPT2_UNIPRINTER

static const CHA* Uniprinter(const CHA* args) {
  A_TEST_BEGIN;
#if SEAM >= SCRIPT2_UNIPRINTER
  A_RUN_TEST(TestPrintAType);
  //A_RUN_TEST(TestSPrinter);
  //A_RUN_TEST(TestProblemChildren);
#endif
  return NILP;
}
}  //< namespace Script2
