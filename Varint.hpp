// Copyright AStarship <https://astarship.net>; all rights reserved.
#pragma once
#ifndef SCRIPT2_VARINT_HPP
#define SCRIPT2_VARINT_HPP
#include <_Config.h>
#if SEAM >= SCRIPT2_DIC
namespace _ {

#if CPU_SIZE == CPU_2_BYTE
inline ISB UnpackSVI(ISB value) {
  if (value < 0) {
    IUB result = 0x8000 return result | ~(value - 1);
  }
  return value;
}

inline ISB PackVSI(ISB value) {
  if (value < 0) {
    IUB result = 1 << 15;
    return result | ((~value + 1) << 1);
  }
  return value;
}
#else
inline ISC VSCUnpack(ISC value) {
  if (value < 0) {
    IUC result = 0x80000000;
    return result | ~(value - 1);
  }
  return value;
}

inline ISC VSCPack(ISC value) {
  if (value < 0) {
    ISC result = 0x80000000;
    return result | ((~value + 1) << 1);
  }
  return value;
}
#endif

inline ISD VSDUnpack(ISD value) {
  if (value < 0) {
    ISD result = 0x8000000000000000;
    return result | ~(value - 1);
  }
  return value;
}

inline ISD VSDPack(ISD value) {
  if (value < 0) {
    ISD result = 0x8000000000000000;
    return result | ((~value + 1) << 1);
  }
  return value;
}

template<typename IS = ISW>
inline IS TVarintPack(IS value) {
  if (value < 0) {
    IS result = IS(-1) >> 1;
    return result | ((~value + 1) << 1);
  }
  return value;
}

}  //< namespace _
#endif
#endif
