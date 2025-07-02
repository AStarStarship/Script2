// Copyright Kabuki Starship <kabukistarship.com>.
#if SEAM >= SCRIPT2_AUTOJECTS
#include "../Room.hpp"
#if SEAM == SCRIPT2_AUTOJECTS
#include "../_Debug.h"
#else
#include "../_Release.h"
#endif
#endif
using namespace ::_;
namespace Script2 {

static const CHA* Autojects(const CHA* args) {
#if SEAM == SCRIPT2_STACK
  A_TEST_BEGIN;
#endif
  return NILP;
}

}  //< namespace Script2
