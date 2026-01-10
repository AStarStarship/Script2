// Copyright AStarship <https://astarship.net>.
#if SEAM >= SCRIPT2_CRABS_BSQ
#include "../Crabs.h"
#include "../BIn.hpp"
#include "../BOut.hpp"
#include "../BSeq.hpp"
#include "../Args.h"
#include "../Address.hpp"
//#include "../Mirror.h"
#if SEAM == SCRIPT2_CRABS_BSQ
#include "../_Debug.h"
#else
#include "../_Release.h"
#endif
using namespace ::_;
namespace Script2 {

class StarTest : public Operand {
public:
  const Op* Star(CHC index, Crabs* crabs) {
    static const Op foo = { "name",
      TBSeq<>().CParams() /*in*/,
      TBSeq<>().CParams() /*out*/,
      "description",
      'a',    //< First function index
      'b',    //< Last function index.
      'a',    //< Default function index.
      NILP    //< Evaluated expression Slot.
    };
    if (!crabs) return &foo;
    return NILP;
  }
};
}
#endif

namespace Script2 {
static const CHA* CrabsBSQ(const CHA* args) {
#if SEAM == SCRIPT2_CRABS_BSQ
  A_TEST_BEGIN;

  enum {
    BooferBytes = 2048,
    BooferWords = BooferBytes / sizeof(IUW),
    StackTotal = 8,
  };
  D_COUT("\nInitializing Crabs Machine");
  IUW boofer[BooferWords],
      unpacked_expr[BooferWords];
  StarTest star_test;
  IUD pc_ctx = 0;
  Crabs* crabs = CrabsInit(boofer, BooferBytes, StackTotal, &star_test,
                           unpacked_expr, BooferBytes, pc_ctx);
  TCrabsPrint<::_::COut>(StdOut(), crabs);

  D_COUT("\n|    Testing Root (@see \"a.h\")...\n");

  void* dez_args[4];
  uint8_t io_number_ = 98;  //< ASCII:'b'
  BIn* bin = CrabsBIn(crabs);
  BOut* bout = CrabsBOut(crabs);

  const Op* result;
  CrabsRingBell(crabs);
  CrabsAckBack(crabs);
  auto params = TTSQ<_IUA, _CHA, _FPD, _CHC>();
  D_COUT("\nBefore:");
  TBOutPrintVars<::_::COut>(StdOut(), bout);
  result = BOutWrite(bout, params, Args(dez_args, TAddress<'A', 'A', 'A'>(),
    &io_number_, "Test", TAddress<_BS, _CR>()), pc_ctx);
  D_COUT("\nAfter:");
  TBOutPrintVars<::_::COut>(StdOut(), bout);
  A_ASSERT(!result);

  TCrabsPrint<::_::COut>(StdOut(), crabs);
  
  //Mirror mirror (bin, bout);
  //CrabsScan(crabs);  //, &mirror);
  //Bypass handshake for testing purposes.
  CrabsScanBIn(crabs);
  TCrabsPrint<::_::COut>(StdOut(), crabs);
  D_COUT("\n| Done with Crabs tests.");
#endif
  return NILP;
}
}  //< namespace Script2
