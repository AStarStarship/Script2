// Copyright Kabuki Starship <kabukistarship.com>.
#if SEAM >= SCRIPT2_ROOM
#include "../Room.hpp"
#if SEAM == SCRIPT2_ROOM
#include "../_Debug.h"
#else
#include "../_Release.h"
#endif
#endif
using namespace ::_;
namespace Script2 {

static const CHA* Room(const CHA* args) {
#if SEAM == SCRIPT2_ROOM
  A_TEST_BEGIN;
  //Room room_a, //
  //     room_b;
#endif
  return NILP;
}

}  //< namespace Script2
