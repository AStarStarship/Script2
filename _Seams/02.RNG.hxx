// Copyright Kabuki Starship <kabukistarship.com>.
#if SEAM >= SCRIPT2_RNG
#include "../RNG.h"
#if SEAM == SCRIPT2_RNG
#include "../_Debug.h"
#else
#include "../_Release.h"
#endif
#endif
using namespace ::_;
namespace Script2 {

static const CHA* RNG(const CHA* args) {
#if SEAM >= SCRIPT2_RNG
  A_TEST_BEGIN;

#if SEAM == SCRIPT2_RNG
  enum { PrintCount = 256 };
#else
  enum { PrintCount = 1 };
#endif

  for (ISN i = 0; i < PrintCount; ++i)
    D_COUT('\n' << i << ".) " << Random(TSignedMin<ISN>(), TSignedMax<ISN>()));

#endif
  return NILP;
}
}  //< namespace Script2
