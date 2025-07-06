// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef SCRIPT2_BSQ_HPP
#define SCRIPT2_BSQ_HPP
#include "BSeq.h"
#if SEAM >= SCRIPT2_LIST
#if SEAM == SCRIPT2_LIST
#include "_Debug.h"
#else
#include "_Release.h"
#endif
namespace _ {

/* Utility class for printing B-Sequences. */
template<typename ISY = ISN, typename DT = DTB>
struct TBSeq {
  const DT* params;  //< BSeq params.

  TBSeq(const DT* params) : params(params) {
    // Nothing to do here! (:-)|=<
  }
};

enum {
  BSQMax = 420   //< Max number of elements in a BSQ.
};

#if CPU_SIZE == CPU_2_BYTE
inline ISB UnpackSVI(ISB value) {
  if (value < 0) {
    IUB result = 0x8000 return result | ~(value - 1);
  }
  return value;
}

inline ISB PackSVI(ISB value) {
  if (value < 0) {
    IUB result = 1 << 15;
    return result | ((~value + 1) << 1);
  }
  return value;
}
#endif

constexpr ISC CBSeqSize(const ISC* params) {
  if (!params) {
    return 0;
  }
  ISC bytes = sizeof(ISC), 
      count = *params++;

  if (count > BSQMax) {
    return 0;
  }

  for (; count > 0; --count) {
    ISC param = *params++;

    if (param == _NIL) {  // This is illegal.
      return 0;
    }
    //if (param <= _TKN) {
    //  bytes += sizeof(ISC);
    //  ++params;
    //}
    if (param == _ISE) {
      bytes += sizeof(ISC);
      ++params;
    }
    if (param == _IUE) {
      bytes += sizeof(ISC);
      ++params;
    }
    //if (param >= _LST && param <= _MAP) {  // This is illegal.
    //  return 0;
    //}
    //if (param > _MAP) {
    //  if (param >> 8) {  // This is an error.
    //    return 0;
    //  }
    //  if (param & 0x20) {     // It's a multi-dimensional array so
    //    param = *params;      // add the number_ of dimensions + 1;
    //    params += param + 1;  // for the dimension count.
    //  }
    //}
    bytes += sizeof(ISC);
  }
  return bytes;
}

/* Creates a immutable Script B-Sequence.
C++11 variadic template to ensure only one copy in ROM
and to eliminate some redundant typing. */
template<const ISC... N>
inline const ISC* TParams() {
  static const ISC Size = 0,  // BsqSize ({ N... })
      cList[sizeof...(N)] = {N...};
  return &Size;
}

/* Writes the given value to the socket between begin and end without any checks.
@warning You must memory align begin and end and verify the boofer fits before
calling. */
template<typename IS = ISR>
void* TBSeqWrite_NC(void* begin, void* end, DTB type, IUW value,
  IUW msb = 0) {
  D_COUT(" value:" << value << " value_msb:" << msb);
  // | b15 | b14:b13 | b12:b9 | b8:b7 | b6:b5 | b4:b0 |
  // |:---:|:-------:|:------:|:-----:|:-----:|:-----:|
  // | CNS |    MD   |   MT   |  SW   |  VT   |  POD  |
  type &= DTB(-1) >> 1;
  const DTB MD = type >> ATypeMDBit0;
  type ^= MD << ATypeMDBit0;

  ISW freespace = ISW(end) - ISW(begin);
  if (type <= _CHA) {
  Write1Byte:
    auto ptr = TPtr<IUA>(begin);
    if (freespace < 1) return NILP;
    *ptr++ = MD ? *TPtr<IUA>(value)
                : IUA(value);
    return ptr;
  }
  if (type <= _CHB) {
  Write2Bytes:
    if (freespace < 2) return NILP;
    auto ptr = TPtr<IUB>(begin);
    *ptr++ = MD ? *TPtr<IUB>(value)
                : IUB(value);
    return ptr;
  }
  if (type <= _CHC) {
  Write4Bytes:
    if (freespace < 4) return NILP;
    auto ptr = TPtr<IUC>(begin);
    *ptr++ = MD ? *TPtr<IUC>(value)
                 : IUC(value);
    return ptr;
  }
  if (type <= _TMD) {
  Write8Bytes:
    if (freespace < 8) return NILP;
    auto ptr = TPtr<IUD>(begin);
    *ptr++ = MD ? *TPtr<IUD>(value)
                 : IUD(value);
    return ptr;
  }
  if (type <= _TME) {
  Write16Bytes:
    if (freespace < 16) return NILP;
    auto dcursor = TPtr<IUW>(begin);
    if (MD) {
      auto vcursor = TPtr<IUW>(value);
      *dcursor++ = *vcursor++;
      #if CPU_SIZE == CPU_2_BYTE
      *dcursor++ = *vcursor++;
      *dcursor++ = *vcursor++;
      *dcursor++ = *vcursor++;
      *dcursor++ = *vcursor++;
      *dcursor++ = *vcursor++;
      *dcursor++ = *vcursor++;
      *dcursor++ = *vcursor++;
      #elif CPU_SIZE == CPU_4_BYTE
      *dcursor++ = *vcursor++;
      *dcursor++ = *vcursor++;
      *dcursor++ = *vcursor++;
      #endif
      return dcursor;
    }
#if CPU_SIZE == CPU_8_BYTE
    *dcursor++ = value;
    *dcursor++ = msb;
#endif
    return dcursor;
  }
  if (type <= _ECE) goto Write16Bytes;
  if (type <= _ECD) goto Write8Bytes;
  if (type <= _ECC) goto Write4Bytes;
  if (type <= _ECB) goto Write2Bytes;
  if (type <= _ECA) goto Write1Byte;

  DTB mt = type >> ATypeMTBit0;
  type ^= mt << ATypeMTBit0;
  DTB sw = type >> ATypeSWBit0;
  type ^= sw << ATypeSWBit0;
  DTB vt = type >> ATypeVTBit0;
  type ^= vt << ATypeVTBit0;
  //@todo Fix me!
  if (vt == 0) { // Vector of Homotuples.
    auto bytes = (1 << vt) * ATypeSizeOfPOD(type);
    return TPtr<ISA>(begin) + bytes;
  }
  else {
    switch (vt) {
    case 0: {
      auto bytes = *TPtr<ISA>(value);
      if (freespace <= bytes) return NILP;
      *TPtr<ISA>(begin) = bytes;
      return TPtr<ISA>(begin) + bytes;
    }
    case 1: {
      auto bytes = *TPtr<ISB>(value);
      if (freespace <= bytes) return NILP;
      *TPtr<ISB>(begin) = bytes;
      return TPtr<ISA>(begin) + bytes;
    }
    case 2: {
      auto bytes = *TPtr<ISC>(value);
      if (freespace <= bytes) return NILP;
      *TPtr<ISC>(begin) = bytes;
      return TPtr<ISA>(begin) + bytes;
    }
    case 3: {
      auto bytes = *TPtr<ISD>(value);
      if (freespace <= bytes) return NILP;
      *TPtr<ISD>(begin) = bytes;
      return TPtr<ISA>(begin) + bytes;
    }
    }
  }
  return NILP;
}
template<typename IS = ISR>
void* TBSeqWrite_NC(void* begin, void* end, DTB type, const void* value) {
  return TBSeqWrite_NC<IS>(begin, end, type, IUW(value));
}

template<typename IS = ISR>
void* TBSeqWrite_NC(void* begin, void* end, DTC type, IUW value) {
  auto result = TBSeqWrite_NC<IS>(begin, end, DTB(type), value);
  if (!result) return result;
  return TBSeqWrite_NC<IS>(result, end, DTB(type >> 16), value);
}
template<typename IS = ISR>
void* TBSeqWrite_NC(void* begin, void* end, DTC type, const void* value) {
  return TBSeqWrite_NC<IS>(begin, end, type, IUW(value));
}

template<typename IS = ISR>
void* TBSeqWrite_NC(void* begin, void* end, DTD type, IUW value) {
  auto result = TBSeqWrite_NC<IS>(begin, end, DTB(type), value);
  if (!result) return result;
  result = TBSeqWrite_NC<IS>(result, end, DTB(type >> 16), value);
  if (!result) return result;
  return TBSeqWrite_NC<IS>(result, end, DTB(type >> 24), value);
}
template<typename IS = ISR>
void* TBSeqWrite_NC(void* begin, void* end, DTD type, const void* value) {
  return TBSeqWrite_NC<IS>(begin, end, type, IUW(value));
}

template<typename IS = ISR>
void* TBSeqWrite(void* begin, void* end, DTB type, const void* value) {
  return TBSeqWrite<IS>(begin, end, type, value);
}

template<typename IS = ISR>
void* TBSeqWrite(void* begin, void* end, DTC type, const void* value) {
  auto result = TBSeqWrite<IS>(begin, end, DTB(type), value);
  if (!result) return result;
  return TBSeqWrite<IS>(result, end, DTB(type >> 16), value);
}

template<typename IS = ISR>
void* TBSeqWrite(void* begin, void* end, DTD type, const void* value) {
  auto result = TBSeqWrite<IS>(begin, end, DTB(type), value);
  if (!result) return result;
  result = TBSeqWrite<IS>(result, end, DTB(type >> 16), value);
  if (!result) return result;
  return TBSeqWrite<IS>(result, end, DTB(type >> 24), value);
}

template<typename Printer>
Printer& TBSeqPrint(Printer& o, const ISN* params) {
  ISN param_count = *params++,
      i     = 0;
  DTB type  = 0,
      value = 0;

  o << "Param<";
  if (param_count > BSQMax) {
    o << "\nInvalid num_params: " << param_count;
    return o;
  }
  o << param_count << ": ";
  for (i = 1; i < param_count; ++i) {
    value = *params++;
    type = value & 0x1f;  //< Mask off type.
    value = value >> 5;   //< Shift over array type.
    o << ATypef(value) << ", ";
    if (type >= STR_) {
      if (value) {
        o << "\nError: arrays may only be created from POD types.";
        return o;
      }
      // Print out the max length of the .
      ++i;
      value = *params++;
      o << value;
    } else if (value > 31) {
      if (value > 127) {  //< It's a multi-dimensional array.
        o << "Multi-dimensional Array:" << value << ", ";
      }
      // Then it's an array.
      ++i;
      switch (value) {  //< Print out the Array type.
        case 0: {
          break;
        }
        case 1: {
          value = *params++;
          o << "IUA:" << value << ", ";
          break;
        }
        case 2: {
          value = *params++;
          o << "IUB:" << value << ", ";
          break;
        }
        case 3: {
          value = *params++;
          o << "IUC:" << value << ", ";
          break;
        }
        case 4: {
          value = *params++;
          o << "IUD:" << value << ", ";
          break;
        }
        case 5: {
          value = *params++;
          if (value == 0) {
            o << "IUA:[0]";
            break;
          }
          o << "IUA:[" << value << ": ";
          for (ISN i = value; i != 0; --i) {
            value = *params++;
            o << value << ", ";
          }
          value = *params++;
          o << value << "]";
          break;
        }
        case 6: {
          value = *params++;
          if (value == 0) {
            o << "IUB:[0]";
            break;
          }
          o << "IUB:[" << value << ": ";
          for (ISN i = value; i != 0; --i) {
            value = *params++;
            o << value << ", ";
          }
          value = *params++;
          o << value << "]";
          break;
        }
        case 7: {
          value = *params++;
          if (value == 0) {
            o << "IUC:[0]";
            break;
          }
          o << "IUC:[" << value << ": ";
          for (ISN i = value; i != 0; --i) {
            value = *params++;
            o << value << ", ";
          }
          value = *params++;
          o << value << "]";
          break;
        }
      }
    }
  }
  // Do the last set without a comma.
  value = *params++;
  o << ATypef(value) << ", ";
  if (value == STR_) {
    ++i;
    value = *params++;
    o << value;
  } else if (value > 31) {
    // Then it's an array.
    type = value & 0x1f;  //< Mask off type.
    value = value >> 5;   //< Shift over array type.
    ++i;
    switch (value) {
      case 0: {
        break;
      }
      case 1: {
        value = *params++;
        o << "IUA:" << value << ", ";
        break;
      }
      case 2: {
        value = *params++;
        o << "IUB:" << value << ", ";
        break;
      }
      case 3: {
        value = *params++;
        o << "IUC:" << value << ", ";
        break;
      }
      case 4: {
        value = *params++;
        o << "IUE:" << value << ", ";
        break;
      }
      case 5: {
        value = *params++;
        if (value == 0) {
          o << "IUA:[0]";
          break;
        }
        o << "IUA:[" << value << ": ";
        for (ISN i = value; i != 0; --i) {
          value = *params++;
          o << value << ", ";
        }
        value = *params++;
        o << value << "]";
        break;
      }
      case 6: {
        value = *params++;
        if (value == 0) {
          o << "IUB:[0]";
          break;
        }
        o << "IUB:[" << value << ": ";
        for (ISN i = value; i != 0; --i) {
          value = *params++;
          o << value << ", ";
        }
        value = *params++;
        o << value << "]";
        break;
      }
      case 7: {
        value = *params++;
        if (value == 0) {
          o << "IUC:[0]";
          break;
        }
        o << "IUC:[" << value << ": ";
        for (ISN i = value; i != 0; --i) {
          value = *params++;
          o << value << ", ";
        }
        value = *params++;
        o << value << "]";
        break;
      }
    }
  }
  o << '>';
  return o;
}

}  //< namespace _

#endif
#endif
