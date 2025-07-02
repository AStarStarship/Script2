// Copyright Kabuki Starship <kabukistarship.com>.
#pragma once
#ifndef SCRIPT2_BOOFER_DECL
#define SCRIPT2_BOOFER_DECL 1
#include <_Config.h>
#if SEAM >= SCRIPT2_ROOM
namespace _ {

/* Creates/Gets a static socket of the specified size. */
template<ISW BooferSize = BooferSizeDefault>
inline CHA* Boofer() {
  enum {
    BooferSizeWords =
        (BooferSize / sizeof(IUW)) + BooferSize % sizeof(IUW) ? 1 : 0
  };
  static IUW socket[BooferSizeWords];
  return TPtr<CHA>(socket);
}

}  //< namespace _
#endif
#endif
