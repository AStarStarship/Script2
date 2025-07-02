// Copyright Kabuki Starship <kabukistarship.com>.
#if SEAM >= SCRIPT2_RELEASE
#if SEAM == SCRIPT2_RELEASE
#include "../_Debug.h"
#else
#include "../_Release.h"
#endif
#endif
namespace Script2 {

inline const CHA* Release(const CHA* args) {
#if SEAM == SCRIPT2_RELEASE
#endif
  return NILP;
}

}  //< namespace Script2
