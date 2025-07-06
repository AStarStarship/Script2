// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef SCRIPT2_BOUT_HPP
#define SCRIPT2_BOUT_HPP
#include "BOut.h"
#if SEAM >= SCRIPT2_CRABS
#if SEAM == SCRIPT2_CRABS
#include "_Debug.h"
#else
#include "_Release.h"
#endif
namespace _ {

inline const CHA* BOutBegin(const BOut* bout) {
  return TPtr<CHA>(bout) + sizeof(BOut);
}

inline CHA* BOutBegin(BOut* bout) {
  return CPtr<CHA>(BOutBegin(CPtr<BOut>(bout)));
}

template<typename Printer>
Printer& TBOutPrint(Printer& printer, BOut* bout) {
  A_ASSERT(bout);
  ISN size = bout->bytes;
  return printer << Linef('_', 80) << "\nBOut: size:" << size
          << " start:" << bout->origin << " stop:" << bout->stop
          << " read:" << bout->read << Charsf(BOutBoofer(bout), size - 1);
}
}  //< namespace _
#endif
#endif
