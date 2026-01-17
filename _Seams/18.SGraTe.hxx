// Copyright AStarship <https://astarship.net>.
#if SEAM >= SCRIPT2_SGRATE
#include "../Room.hpp"
#if SEAM == SCRIPT2_SGRATE
#include "../_Debug.h"
#else
#include "../_Release.h"
#endif
#endif
using namespace ::_;
namespace Script2 {

/* Seam contains test functions for the rest of the Autojects. */
static const CHA* SGraTe(const CHA* args) {
#if SEAM == SCRIPT2_STACK
  A_TEST_BEGIN;
#endif
  return NILP;
}

}  //< namespace Script2
