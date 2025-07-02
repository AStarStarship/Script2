// Copyright Kabuki Starship <kabukistarship.com>.
#if SEAM >= SCRIPT2_COUT
#include "../Uniprinter.hpp"
#if SEAM == SCRIPT2_COUT
#include "../_Debug.h"
#else
#include "../_Release.h"
#endif
#endif
using namespace ::_;
namespace Script2 {

inline const CHA* COut(const CHA* args) {
#if SEAM >= SCRIPT2_COUT && USING_CONSOLE == YES_0

  A_TEST_BEGIN;
  
  D_COUT(Headingf("Testing ArgsToString"));
  
  CHA arg_string[48] = "C:\\Windows\0Foo\0\0Bar    \0\0\0   420    \0";
  D_COUT("arg_string:\"");
  CHA* cursor = arg_string;
  for (ISN i = 0; i < 35; ++i) D_COUT(*cursor++);
  D_COUT('\"');

  CHA* test_args[] = {arg_string, arg_string + 11, arg_string + 16,
                      arg_string + 26};
  const ISC ArgCount = 4;

  D_COUT("\nArguments:\n");
  for (ISC i = 0; i < ArgCount; ++i) {
    CHA* arg = test_args[i];
    if (arg) {
      D_COUT("\n" << i << ".)\"" << arg << "\" delta:" << arg - arg_string);
    } else {
      D_COUT("\nNil arg.");
    }
  }
  D_COUT("\n\nRunning ArgsToString... ");

  D_ASSERT(ArgsToString(ArgCount, test_args));

  D_COUT("Result:\"");
  D_COUT(test_args[1]);

  CHC ch4_found;

  D_COUT(Headingf("Testing CHA* SPrint (CHA*,CHA*,CHC);"));
  enum {
    STAEdgeCondition2 = 0x7f,
    STAEdgeCondition3 = 0x7ff,
    STAEdgeCondition4 = 0xffff,
    STACount = 8
  };
  CHA str1[STACount];
  CHA* str1_cursor = SPrint(str1, STACount, CHC(0));
  A_ASSERT(str1_cursor);
  const CHA* str1_result = SScan(str1, ch4_found);
  D_ASSERT_INDEX(str1_result, ISC(0));
  A_AVOW_INDEX(CHC(0), ch4_found, 0);

  for (CHC ch4_expected = STAEdgeCondition4; ch4_expected < (1 << 21);
       ch4_expected += 64) {
    str1_cursor = SPrint(str1, STACount, ch4_expected);
    D_ASSERT_INDEX(str1_cursor, IUC(ch4_expected));
    const CHA* str1_result = SScan(str1, ch4_found);
    D_ASSERT_INDEX(str1_result, IUC(ch4_expected));
    A_AVOW_INDEX(ch4_expected, ch4_found, ISC(ch4_expected));
  }

#if USING_STB == YES_0
  D_COUT(Headingf("Testing Testing CHB* SPrint (CHB*,CHB*,CHC)..."));
  enum {
    STRBCount = 4,
  };
  CHB str2[STRBCount] = {};
  CHB* str2_cursor = str2;
  str2_cursor = SPrint(str2, ISW(STRBCount) - 1, CHC(0));
  D_COUT(Hexf(str2) << TPtr<CHA>(str2 + 3) - 1);
  A_ASSERT(str2_cursor);
  const CHB* str2_result = SScan(str2, ch4_found);
  D_ASSERT_INDEX(str2_result, ISC(0));
  A_AVOW_INDEX(CHC(0), ch4_found, 0);

  for (CHC ch4_expected = 1; ch4_expected < (1 << 10); ++ch4_expected) {
    str2_cursor = SPrint(str2, 3, ch4_expected);
    D_ASSERT_INDEX(str2_cursor, IUC(ch4_expected));
    const CHB* str2_result = SScan(str2, ch4_found);
    D_ASSERT_INDEX(str2_result, IUC(ch4_expected));
    A_AVOW_INDEX(ch4_expected, ch4_found, ISC(ch4_expected));
  }
  
  D_COUT(Headingf("Testing Hex functions"));
  for (ISC i = 0; i < 16; ++i) {
    ISC value = HexToByte(HexNibbleToLowerCase(i));
    Test(i, value);
    // D_COUT("\n    " << i << ".) " >> value);
    value = HexToByte(HexNibbleToUpperCase(i));
    // D_COUT(" Result:" << value);
    Test(i, value);
  }

  for (ISC i = 0; i < 256; ++i) {
    IUB c = HexByteToLowerCase(i);
    // D_COUT('\n' << i << ".) Expecting:" << Hexf(i)
    //             << "        HexByteToLowerCase:" << CHA(c) << CHA(c >> 8));
    ISC value = HexToByte(c);
    // D_COUT("        HexToByte:" << value);
    A_AVOW(i, value);
    value = HexToByte(HexByteToUpperCase(i));
    // D_COUT(" Result:" << value);
    Test(i, value);
  }
#endif

#endif
  return 0;
}

}  //< namespace Script2
