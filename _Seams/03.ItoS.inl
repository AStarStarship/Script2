// Copyright Kabuki Starship™ <kabukistarship.com>.
#if SEAM >= SCRIPT2_ITOS
#include <cstring>
#include <cstdio>
//
#include "../Puff.hpp"
#include "../RNG.h"
#include "../Uniprinter.hpp"
#if SEAM == SCRIPT2_ITOS
#include "../_Debug.inl"
#else
#include "../_Release.inl"
#endif
#endif

using namespace _;
namespace Script2 {

inline const CHA* ItoS(const CHA* args) {
#if SEAM >= SCRIPT2_ITOS
  A_TEST_BEGIN;
  D_COUT(
      "\n\nDirections: To use this tester, you'll want to run the script on "
      "random numbers until you find one that fails the test. After the test "
      "has failed you add that number to the problem_child array so it will "
      "get tested first and you'll get some extra debug information.");

  D_COUT("\n\nTesting Pow10_UI2...");
  IUB pow10_ui2 = 1;
  for (IUB i = 0; i < cUI2DigitTotal; ++i) {
    A_AVOW_INDEX(pow10_ui2, Pow10(i), i);
    pow10_ui2 *= 10;
  }

  D_COUT("\n\nTesting Pow10_UI4...");
  IUC pow10_ui4 = 1;
  for (IUC i = 0; i < cUI4DigitTotal; ++i) {
    A_AVOW_INDEX(pow10_ui4, Pow10(i), i);
    pow10_ui4 *= 10;
  }

  D_COUT("\n\nTesting Pow10_UI8...");
  IUD pow10_ui8 = 1;
  for (IUD i = 0; i < cUI8DigitTotal; ++i) {
    A_AVOW_INDEX(pow10_ui8, Pow10(i), i);
    pow10_ui8 *= 10;
  }

  static const IUD edge_condition[] = {1,
                                       12,
                                       123,
                                       1234,
                                       12345,
                                       123456,
                                       1234567,
                                       12345678,
                                       123456789,
                                       Pow10_UI8()[1] - 1,
                                       Pow10_UI8()[1],
                                       Pow10_UI8()[1] + 1,
                                       Pow10_UI8()[1] + Pow10_UI8()[1] / 2,
                                       Pow10_UI8()[2] - 1,
                                       Pow10_UI8()[2],
                                       Pow10_UI8()[2] + 1,
                                       Pow10_UI8()[2] + Pow10_UI8()[2] / 2,
                                       Pow10_UI8()[3] - 1,
                                       Pow10_UI8()[3],
                                       Pow10_UI8()[3] + 1,
                                       Pow10_UI8()[3] + Pow10_UI8()[3] / 2,
                                       Pow10_UI8()[4] - 1,
                                       Pow10_UI8()[4],
                                       Pow10_UI8()[4] + 1,
                                       Pow10_UI8()[4] + Pow10_UI8()[4] / 2,
                                       Pow10_UI8()[5] - 1,
                                       Pow10_UI8()[5],
                                       Pow10_UI8()[5] + 1,
                                       Pow10_UI8()[5] + Pow10_UI8()[5] / 2,
                                       Pow10_UI8()[6] - 1,
                                       Pow10_UI8()[6],
                                       Pow10_UI8()[6] + 1,
                                       Pow10_UI8()[6] + Pow10_UI8()[6] / 2,
                                       Pow10_UI8()[7] - 1,
                                       Pow10_UI8()[7],
                                       Pow10_UI8()[7] + 1,
                                       Pow10_UI8()[7] + Pow10_UI8()[7] / 2,
                                       Pow10_UI8()[8] - 1,
                                       Pow10_UI8()[8],
                                       Pow10_UI8()[8] + 1,
                                       Pow10_UI8()[8] + Pow10_UI8()[8] / 2,
                                       Pow10_UI8()[9] - 1,
                                       Pow10_UI8()[9],
                                       Pow10_UI8()[9] + 1,
                                       Pow10_UI8()[9] + Pow10_UI8()[9] / 2,
                                       0};

  static const IUD problem_child[] = {9173263544803952, 827672716845, 0};

  enum { cProblemChildCount = 2, Size = 23 };

  CHA text[Size + 1], expecting[Size + 1];
  CHA socket[Size];
  CHA* result;
  IUD result_ui8, expected_ui8;

  D_COUT("\nTesting ScanUnsigned<IU, CHT> (const CHT*, const CHA*, I);");

  for (ISN i = 0; i < 1 << 6; ++i) {
    expected_ui8 = RandomUI8();
    sprintf_s(socket, Size, "%llu", expected_ui8);
    const CHA* test = TScanUnsigned<IUD, CHA>(socket, result_ui8);
    A_ASSERT(test);
    A_AVOW(expected_ui8, result_ui8);
  }

  D_COUT("\n\nTesting Puff ItoS Algorithm...\n\n");

  ISN count = TSTRLength<IUD>(problem_child);
  D_COUT("\n\nTesting %i problem children...\n\n" << count);

  for (ISN i = 0; i < count; ++i) {
    expected_ui8 = problem_child[i];
    sprintf_s(expecting, 24, "%llu", expected_ui8);
    static const CHA kPuffDebugHeader[] =
        "\n\n    "
        "|6666555555555544444444443333333333222222222211111111110000000000|\n"
        "    "
        "|3210987654321098765432109876543210987654321098765432109876543210|\n"
        "    "
        "|*   *  *  *   *  *  *   *  *  *   *  *  *   *  *  *   *  *  *   |\n"
        "    |\0";
    D_COUT(kPuffDebugHeader << Binaryf(expected_ui8) << '|' << '\n'
                            << i << ".) ");
    ISN expected_length = TSTRLength<CHA>(expecting);
    result = TSPrintUnsigned<IUD, CHA>(text, text + Size - 1, expected_ui8);
    if (!result) {
      D_PAUSE("An error occurred :-(");
      break;
    }
    *result = 0;
    D_AVOW(expecting, text);
  }

  count = TSTRLength<IUD>(edge_condition);
  D_COUT("\n\nTesting " << count << " edge conditions...\n\n");
  for (ISW i = 0; i < count; ++i) {
    expected_ui8 = edge_condition[i];
    sprintf_s(expecting, 24, "%llu", expected_ui8);
    D_COUT("\n\n" << i + 1 << ".) ");
    result = TSPrintUnsigned<IUD, CHA>(text, text + Size - 1, expected_ui8);
    if (!result) {
      D_PAUSE("An error occurred :-(");
      break;
    }
    *result = 0;
    D_AVOW(expecting, text);
  }
#if D_THIS
  count = 200;
#else
  count = 1000;
#endif
  /* The RNG some broke. I don't know what's wrong.
  D_COUT("\n\nTesting " << count << " random numbers of each length...\n\n");
  ISN count_digits = STRLength(count);
  D_COUT("\n\ncount_digits:" << count_digits);

  // We don't want to do 1000 tests of length 1, so we're going to

  for (ISN i = 0; i < 20; ++i) {
    for (ISN j = 0; j < count; ++j) {
      if (j >= Pow10_UI8()[i + i] - 1 - Pow10_UI8()[i]) break;
      IUD lower_bounds = Pow10_UI8()[i], upper_bounds = Pow10_UI8()[i + 1] - 1;
      expected_ui8 = Random(lower_bounds, upper_bounds);
      sprintf_s(expecting, 24, "%llu", expected_ui8);
      D_COUT("\n\n" << i + 1);
      result = TSPrintUnsigned<IUD, CHA>(text, text + Size - 1, expected_ui8);
      if (!result) {
        D_PAUSE("An error occurred :-(");
        break;
      }
      *result = 0;
      D_AVOW(expecting, text);
    }
  }*/

  D_COUT("\n\nProblem children...");

  D_COUT('\n' << 12321960);

#endif
  return 0;
}
}  //< namespace Script2
