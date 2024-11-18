// Copyright Kabuki Starship <kabukistarship.com>.
#if SEAM >= SCRIPT2_TABLE
#include "../Table.hpp"
//
#include "./TestWords.h"
#if SEAM == SCRIPT2_TABLE
#include "../_Debug.hxx"
#else
#include "../_Release.hxx"
#endif
using namespace _;
namespace Script2 {

template<TBL_A>
void TestTable() {
  D_COUT(Linef("\n\n\n\n\n\n+---\nTesting ATable<IS")
         << CSizef<ISZ>() << ",IU" << CSizef<HSH>() << ",CH"
         << CSizef<CHT>() << ">\n"
         << Linef("+---\n\n"));
  ISY total_init = 13;
  ATable<TBL_P> table(total_init);
  const TBL* This = table.This();
  const ISZ size_bytes = table.Bytes();

  static const CHT a[] = {'A', '\0'}, b[] = {'B', '\0'}, c[] = {'C', '\0'},
                   d[] = {'D', '\0'}, e[] = { 'E', '\0' },
                   abc[] = {'a', 'b', 'c', '\0'},
                   bac[] = {'b', 'a', 'c', '\0'},
                   cba[] = {'c', 'b', 'a', '\0'},
                   cab[] = {'c', 'a', 'b', '\0'},
                   def[] = {'d', 'e', 'f', '\0'},
                   fed[] = {'f', 'e', 'd', '\0'},
                   efd[] = {'e', 'f', 'd', '\0'},
                   dfe[] = {'d', 'f', 'e', '\0'},
                   test[] = {'t', 'e', 's', 't', '\0'};

  A_AVOW(ISY(0), table.Append(a));
  A_ASSERT(TTableHashesVerify<TBL_P>(This));
  A_AVOW(ISY(0), table.Find(a));

  A_AVOW(ISY(1), table.Append(b));
  A_ASSERT(TTableHashesVerify<TBL_P>(This));
  A_AVOW(ISY(0), table.Find(a));
  A_AVOW(ISY(1), table.Find(b));

  A_AVOW(ISY(2), table.Append(c));
  A_ASSERT(TTableHashesVerify<TBL_P>(This));
  A_AVOW(ISY(0), table.Find(a));
  A_AVOW(ISY(1), table.Find(b));
  A_AVOW(ISY(2), table.Find(c));

  A_AVOW(ISY(3), table.Append(d));
  A_ASSERT(TTableHashesVerify<TBL_P>(This));
  A_AVOW(ISY(0), table.Find(a));
  A_AVOW(ISY(1), table.Find(b));
  A_AVOW(ISY(2), table.Find(c));
  A_AVOW(ISY(3), table.Find(d));

  A_AVOW(ISY(0), table.Append(a));
  A_ASSERT(TTableHashesVerify<TBL_P>(This));
  A_AVOW(ISY(1), table.Append(b));
  A_AVOW(ISY(2), table.Append(c));
  A_AVOW(ISY(3), table.Append(d));

  A_AVOW(ISY(4), table.Append(abc));
  A_ASSERT(TTableHashesVerify<TBL_P>(This));
  A_AVOW(ISY(4), table.Find(abc));

  A_AVOW(ISY(5), table.Append(bac));
  A_ASSERT(TTableHashesVerify<TBL_P>(This));
  A_AVOW(ISY(4), table.Find(abc));
  A_AVOW(ISY(5), table.Find(bac));

  A_AVOW(ISY(6), table.Append(cba));
  A_ASSERT(TTableHashesVerify<TBL_P>(This));
  A_AVOW(ISY(4), table.Find(abc));
  A_AVOW(ISY(5), table.Find(bac));
  A_AVOW(ISY(6), table.Find(cba));

  A_AVOW(ISY(7), table.Append(e));
  A_ASSERT(TTableHashesVerify<TBL_P>(This));
  A_AVOW(ISY(4), table.Find(abc));
  A_AVOW(ISY(5), table.Find(bac));
  A_AVOW(ISY(6), table.Find(cba));
  A_AVOW(ISY(7), table.Find(e));

  A_AVOW(ISY(8), table.Append(cab));
  A_ASSERT(TTableHashesVerify<TBL_P>(This));
  A_AVOW(ISY(4), table.Find(abc));
  A_AVOW(ISY(5), table.Find(bac));
  A_AVOW(ISY(6), table.Find(cba));
  A_AVOW(ISY(7), table.Find(e));
  A_AVOW(ISY(8), table.Find(cab));

  A_AVOW(ISY(9 ), table.Append(def));
  A_AVOW(ISY(10), table.Append(fed));
  A_AVOW(ISY(11), table.Append(efd));
  A_AVOW(ISY(12), table.Append(dfe));
  A_AVOW(ISY(9 ), table.Find(def));
  A_AVOW(ISY(10), table.Find(fed));
  A_AVOW(ISY(11), table.Find(efd));
  A_AVOW(ISY(12), table.Find(dfe));
  D_COUT_OBJ(table);
  A_AVOW(CAInvalidIndex<ISY>(), table.Find(test));

  const CHT* test_words = TTestWords<CHT>::Words(),
    * word_cursor = test_words;
  ISZ word_step = TTestWords<CHT>::CharsMax;

  ISY i = total_init;
  D_COUT("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  D_COUT("\n\nStep 8: Testing Factory.Grow...\n" << Linef("---") << '\n');
  A_AVOW(ISY(i++), table.Append(word_cursor += word_step));
  //table.COut();
  D_COUT("\n\nStep 8b: Testing POD types...\n" << Linef("---\n"));
  for (; i < ISY(TTestWords<CHT>::Total) - 8;) {
    A_AVOW(ISY(i++), table.Append(word_cursor += word_step));
    A_AVOW(ISY(i++), table.Append(word_cursor += word_step));
    A_AVOW(ISY(i++), table.Append(word_cursor += word_step));
    A_AVOW(ISY(i++), table.Append(word_cursor += word_step));
    A_AVOW(ISY(i++), table.Append(word_cursor += word_step));
    A_AVOW(ISY(i++), table.Append(word_cursor += word_step));
    A_AVOW(ISY(i++), table.Append(word_cursor += word_step));
    A_AVOW(ISY(i++), table.Append(word_cursor += word_step));
  }

  D_COUT("\n\nStep 8c Adding large string...:\n" << Linef("---\n"));
  enum { LargeStringLength = 255 };
  CHT large_string[LargeStringLength] = { 0 };
  CHT* cursor = large_string;
  for (ISN i = 0; i < LargeStringLength - 1; ++i) *cursor++ = '*';
  *cursor = 0;
  ISZ index = table.Append(large_string);
  auto dez_nutz = table.This();
  D_COUT_TABLE(dez_nutz);
}
}  //< namespace Script2
#endif

namespace Script2 {
static const CHA* Table(const CHA* args) {
#if SEAM >= SCRIPT2_TABLE
  A_TEST_BEGIN;

#if USING_UTF8 == YES_0
  TestTable<CHA, ISC, ISB, IUC>();
  TestTable<CHA, ISD, ISC, IUD>();
#endif
#if USING_UTF16 == YES_0
  TestTable<CHB, ISC, ISB, IUC>();
  TestTable<CHB, ISD, ISC, IUD>();
#endif
#if USING_UTF32 == YES_0
  TestTable<CHC, ISC, ISB, IUC>();
  TestTable<CHC, ISD, ISC, IUD>();
#endif
#endif
  return nullptr;
}
}  //< namespace Script2
