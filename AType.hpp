// Copyright Kabuki Starship <kabukistarship.com>.
#pragma once
#ifndef INCLUDED_TYPES_INLINE_CODE
#define INCLUDED_TYPES_INLINE_CODE 1
#include "AType.h"
#if SEAM >= SCRIPT2_COUT
namespace _ {

/*
inline IUA ValueBase2(IUC value) {
  // Example: 0b0000_0000_0000_0000_0111_0111_1001_1101
  return 0;
} */

/* Gets the log_2 of the sizeof(T).
Naming Convension:
ISN = Integer Signed N-Bit = int and A=8-bit, B=16-bit, ...
O = 64-bits
N = 32-bits
M = 16-bits
L = 8-bits
SCRIPT Spec does not support 128-bit CPUs.
*/
template<typename T>
constexpr DTB CASizeCode() {
  switch (sizeof(T)) {
    case    1: return 0;  // A
    case    2: return 1;  // B
    case    4: return 2;  // C
    case    8: return 3;  // D
    case   16: return 4;  // E
    case   32: return 5;  // F
    case   64: return 6;  // G
    case  128: return 7;  // H
    case  256: return 8;  // I    2^8=256
    case  512: return 9;  // J
    case 1024: return 10; // K
    case 2048: return 11; // L
  }
  return 0;
}

template<typename T, typename DT=DTB>
constexpr DT CASizeBits() {
  return DT(1) << ATypeSWBit0;
}

// Gets the ASCII Size Width letter A-K
template<typename T>
constexpr CHA CSizeCodef() {
  return 'A' + CHA(CASizeCode<T>());
}

// Gets the ASCII Size Width letter A-K
inline CHA ASizeCodef(ISA sw) {
  return 'A' + CHA(sw);
}
inline CHA ASizeCodef(ISB sw) {
  return 'A' + CHA(sw);
}
inline CHA ASizeCodef(ISC sw) {
  return 'A' + CHA(sw);
}
inline CHA ASizeCodef(ISD sw) {
  return 'A' + CHA(sw);
}

template<typename T>
T TCTXHandle(ACTXHandler actxh, void* begin, void* end, DTW type, IUW value, 
             IUW vmsb) {
  if (!actxh) return 0;
  return (T)actxh(begin, end, type, value, vmsb);
}

// Strings for the POD types 0-31.
template<typename CH = CHR>
const CH* TATypePODs() {
  static const CH Strings[64][4] = {
      {'N', 'I', 'L', NIL},  //< 00
      {'I', 'U', 'A', NIL},  //< 01
      {'I', 'S', 'A', NIL},  //< 02
      {'C', 'H', 'A', NIL},  //< 03
      {'F', 'P', 'B', NIL},  //< 04
      {'I', 'U', 'B', NIL},  //< 05
      {'I', 'S', 'B', NIL},  //< 06
      {'C', 'H', 'B', NIL},  //< 07
      {'F', 'P', 'C', NIL},  //< 08
      {'I', 'U', 'C', NIL},  //< 09
      {'I', 'S', 'C', NIL},  //< 10
      {'C', 'H', 'C', NIL},  //< 11
      {'F', 'P', 'D', NIL},  //< 12
      {'I', 'U', 'D', NIL},  //< 13
      {'I', 'S', 'D', NIL},  //< 14
      {'T', 'M', 'D', NIL},  //< 15
      {'F', 'P', 'E', NIL},  //< 16
      {'I', 'U', 'E', NIL},  //< 17
      {'I', 'S', 'E', NIL},  //< 18
      {'T', 'M', 'E', NIL},  //< 19
      {'E', 'P', 'a', NIL},  //< 20
      {'E', 'P', 'b', NIL},  //< 21
      {'E', 'P', 'c', NIL},  //< 22
      {'E', 'P', 'd', NIL},  //< 23
      {'E', 'P', 'e', NIL},  //< 24
      {'E', 'P', 'f', NIL},  //< 25
      {'E', 'P', 'g', NIL},  //< 26
      {'E', 'P', 'h', NIL},  //< 27
      {'E', 'P', 'i', NIL},  //< 28
      {'E', 'P', 'j', NIL},  //< 29
      {'E', 'P', 'k', NIL},  //< 30
      {'E', 'P', 'l', NIL},  //< 31
      {'E', 'N', 'V', NIL},  //< 32
  };
  return &Strings[0][0];
}

template<typename CH = CHR, typename IS = ISW>
inline const CH* TATypePODs(IS type, ACTXHandler actxh) {
  type = (type < 0 || type > ATypePODTotal) ? ATypePODTotal : type;
  if (type >= _PCa)
    return (const CH*)ACTXHandle(actxh, NILP, NILP, type, 0, 0);
  return &TATypePODs<CH>()[type << 2];
}

template<typename CH = CHR, typename IS = ISW>
inline const CH* TATypePODs(IS type) {
  type = (type < 0 || type > ATypePODTotal) ? ATypePODTotal : type;
  if (type >= _PCa) return (const CH*)ACTXHandle(NILP, NILP, type, 0, 0);
  return &TATypePODs<CH>()[type << 2];
}

template<typename CH = CHR>
const CH* TATypeVectors() {
  static const CH Strings[17][4] = {
      {'V', 'H', 'A', NIL},  //< 00
      {'A', 'R', 'A', NIL},  //< 01
      {'S', 'C', 'A', NIL},  //< 02
      {'M', 'A', 'A', NIL},  //< 03
      {'V', 'H', 'B', NIL},  //< 04
      {'A', 'R', 'B', NIL},  //< 05
      {'S', 'C', 'B', NIL},  //< 06
      {'M', 'A', 'B', NIL},  //< 07
      {'V', 'H', 'C', NIL},  //< 08
      {'A', 'R', 'C', NIL},  //< 09
      {'S', 'C', 'C', NIL},  //< 10
      {'M', 'A', 'C', NIL},  //< 11
      {'V', 'H', 'D', NIL},  //< 12
      {'A', 'R', 'D', NIL},  //< 13
      {'S', 'C', 'D', NIL},  //< 14
      {'M', 'A', 'D', NIL},  //< 15
      {'I', 'N', 'V', NIL},  //< 16
  };
  return &Strings[0][0];
}

template<typename CH = CHR, typename IS = ISW>
const CH* TATypeVectors(IS value) {
  value = (value < 0 || value > 16) ? 16 : value;
  return &TATypeVectors<CH>()[value << 2];
}

template<typename CH = CHR, typename IS = ISW>
const CH* TATypeVectors(IS size_width_bits, IS vector_type_bits) {
  IS value = (size_width_bits << 2) | vector_type_bits;
  value = (value < 0 || value > 16) ? 16 : value;
  return &TATypeVectors<CH>()[value << 2];
}

template<typename CH = CHR>
const CH* TATypeVectorClasses() {
  static const CH Strings[5][4] = {
      {'V', 'H', 'T', NIL},  //< 00
      {'A', 'R', 'Y', NIL},  //< 01
      {'S', 'C', 'K', NIL},  //< 02
      {'M', 'T', 'X', NIL},  //< 03
      {'I', 'N', 'V', NIL},  //< 04
  };
  return &Strings[0][0];
}

template<typename CH = CHR, typename IS = ISW>
const CH* TATypeVectorClasses(IS value) {
  value = (value < 0 || value > 16) ? 16 : value;
  return &TATypeVectorClasses<CH>()[value << 2];
}

template<typename CH = CHR>
const CH* TATypeMODs() {
  static const CH Strings[9][8] = {
      {NIL},  //< 0
      {'P', 'T', 'R', NIL},  //< 1
      {'P', 'T', 'I', NIL},  //< 2
      {'C', 'T', 'X', NIL},  //< 3
      {'C', 'N', 'S', NIL},  //< 4
      {'C', 'N', 'S','_', 'P', 'T', 'R', NIL},  //< 5
      {'C', 'N', 'S','_', 'P', 'I', 'X', NIL},  //< 6
      {'C', 'N', 'S','_', 'C', 'T', 'X', NIL},  //< 7
      {'I', 'N', 'V', NIL},  //< 4
  };
  return &Strings[0][0];
}

template<typename CH = CHR, typename IS = ISW>
const CH* TATypeMODs(IS value) {
  value = (value < 0 || value > 8) ? 8 : value;
  return &TATypeMODs<CH>()[value << 3];
}

template<typename CH = CHR>
const CH* TATypeMODsCNS() { return TATypeMODs<CH>()[2 * 4]; }

template<typename CH = CHR>
const CH* TATypeMaps() {
  static const CH Strings[5][4] = {
      {'M', 'A', 'C', NIL},  //< 00
      {'M', 'A', 'D', NIL},  //< 01
      {'I', 'N', 'V', NIL},  //< 04
  };
  return &Strings[0][0];
}

template<typename CH = CHR, typename IS = ISW>
const CH* TATypeMaps(IS value) {
  value = (value < 0 || value > 2) ? 2 : value;
  return &TATypeMaps<CH>()[value << 2];
}

/* Human-readable Crabs error strings. */
template<typename CH = CHR>
const CH* TAErrors() {
  static const CH error_strings[ASCIIErrorCount + 1][32] = {
    /*00*/{'S','u','c','k',' ','i','t',0,},
    /*01*/{'I','n','v','a','l','i','d',0,},
    /*02*/{'I','n','v','a','l','i','d',' ','b','o','o','f','e','r',0},
    /*03*/{'I','n','v','a','l','i','d',' ','b','o','u','n','d','s',0},
    /*04*/{'I','n','v','a','l','i','d',' ','d','o','o','r',0},
    /*05*/{'I','n','v','a','l','i','d',' ','h','e','a','d','e','r',0},
    /*06*/{'I','n','v','a','l','i','d',' ','h','a','s','h',0},
    /*07*/{'I','n','v','a','l','i','d',' ','i','n','d','e','x',0},
    //--------------------------------------------------------------------------
    /*08*/{'I','n','v','a','l','i','d',' ','i','n','p','u','t',0},
    /*09*/{'I','n','v','a','l','i','d',' ','e','n','q','u','e','r','y',0},
    /*10*/{'I','n','v','a','l','i','d',' ','o','p',0},
    /*11*/{'I','n','v','a','l','i','d',' ','o','p','e','r','a','n','d',0},
    /*12*/{'I','n','v','a','l','i','d',' ','r','o','o','m',0},
    /*13*/{'I','n','v','a','l','i','d',' ','t','y','p','e',0},
    /*14*/{'I','n','v','a','l','i','d',' ','U','T','F','-','8',0},
    /*15*/{'I','n','v','a','l','i','d',' ','U','T','F','-','1','6',0},
    //--------------------------------------------------------------------------
    /*16*/{'A','r','r','a','y',' ','u','n','d','e','r','f','l','o','w',0},
    /*17*/{'B','o','o','f','e','r',' ','u','n','d','e','r','f','l','o','w',0},
    /*18*/{'K', 'e', 'y', 's', ' ', 'b', 'o', 'o', 'f', 'e', 'r', ' ', 'u','n','d',
           'e', 'r', 'f', 'l', 'o', 'w', 0, },
    /*19*/{'P','a','r','a','m',' ','u','n','d','e','r','f','l','o','w',0},
    /*20*/{'S','t','a','c','k',' ','u','n','d','e','r','f','l','o','w',0},
    /*21*/{'T','e','x','t',' ','u','n','d','e','r','f','l','o','w',0},
    /*22*/{'V','a','r','i','n','t',' ','u','n','d','e','r','f','l','o','w',0},
    /*23*/{'Y','o','u','r',' ','m','o','m',' ','u','n','d','e','r','f','l','o','w',
          0},
    //--------------------------------------------------------------------------
    /*24*/{'A','r','r','a','y',' ','o','v','e','r','f','l','o','w',0},
    /*25*/{'B','o','o','f','e','r',' ','o','v','e','r','f','l','o','w',0},
    /*26*/{'K', 'e', 'y', 's', ' ', 'b', 'o', 'o', 'f', 'e', 'r', ' ', 'o', 'v',
           'e', 'r', 'f', 'l', 'o', 'w', 0 },
    /*27*/{'P','a','r','a','m',' ','o','v','e','r','f','l','o','w',0},
    /*28*/{'S','t','a','c','k',' ','o','v','e','r','f','l','o','w',0},
    /*29*/{'T','e','x','t',' ','o','v','e','r','f','l','o','w',0},
    /*30*/{'V','a','r','i','n','t',' ','o','v','e','r','f','l','o','w',0},
    /*31*/{'Y','o','u','r',' ','m','o','m',' ','o','v','e','r','f','l','o','w',
          0},
    //--------------------------------------------------------------------------
    /*32*/{'P','a','r','a','m',' ','n','i','l',0},
    /*33*/{'P','a','r','a','m',' ','i','s',' ','e','r','r','o','r',' ','c','o',
           'd','e',0},
    /*34*/{'P','a','r','a','m',' ','i','n','v','a','l','i','d',0},
    /*35*/{'P','a','r','a','m',' ','e','r','o','n','e','o','u','s',0},
    /*36*/{'R', 'e', 'a', 'd', ' ', 'o', 'n', 'l', 'y', 0},
    /*37*/{'W', 'r', 'i', 't', 'e', ' ', 'o', 'n', 'l', 'y', 0},
    /*38*/{'U','n','a','u','t','h','e','r','i','z', 'e','d',0},
    /*39*/{'U','n','a','u','t','h','e','r','i','z', 'e','d',0},
    //--------------------------------------------------------------------------
    /*40*/{'U','n','a','v','a','i','l','a','b','l','e',0},
    /*41*/{'U','n','a','v','a','i','l','a','b','l','e',' ','k','e','y',0},
    /*42*/{'I','m','p','l','e','m','e','n','t','a','t','i','o','n',0}
  };
  return &error_strings[0][0];
}

/* Stores an ASCII type and pointer to it's value. */
template<typename DT = DTW>
struct TATypeValuePtr {
  DT    type;   //< The ASCII data type word.
  void* value;  //< POint to the value of the type.
};

/* Stores an ASCII data type and offset to value.
This class is preferred over TATypeValuePtr for x86_64 because two 32-bit or 
smaller values may be returned from functions without using the stack. */
template<typename IS = ISW, typename DT = DTW>
struct TATypeValue {
  DT type;      //< ASCII data type.
  IS value;     //< Offset to the value of the type.
};

/* Stores a pointer to the ASCII data type and it's value. */
template<typename IS = ISW, typename DT = DTW, typename CH = CHR>
struct TATypeKV {
  const CH* key;          //< Pointer to the key.
  TATypeValue<IS, DT> tv; //< AType value offset pair.
};

/* Stores a pointer to the ASCII data type and it's value. */
template<typename IS = ISW, typename DT = DTW, typename CH = CHR>
struct TATypeKeyValueIndex {
  IS index;                        //< Index of the key-value pair.
  TATypeKV<IS, DT, CH> type_value; //< Pointer to the value of the type.
};

/* An 8-bit, 16-bit, or 32-bit ASCII Data Type. */
template<typename DT>
class TType {
 public:

  DT type;  //< The ASCII Data Type.

  TType(DT type) : type(type) {} //< Stores the type.
};

constexpr DTB CATypePOD(IUA value) { return _IUA; }
constexpr DTB CATypePOD(ISA value) { return _ISA; }
constexpr DTB CATypePOD(CHA value) { return _CHA; }

//constexpr DTB CAType(FPB value) { return _FPB; }
constexpr DTB CATypePOD(IUB value) { return _IUB; }
constexpr DTB CATypePOD(ISB value) { return _ISB; }
constexpr DTB CATypePOD(CHB value) { return _CHB; }

constexpr DTB CATypePOD(FPC value) { return _FPC; }
constexpr DTB CATypePOD(IUC value) { return _IUC; }
constexpr DTB CATypePOD(ISC value) { return _ISC; }
constexpr DTB CATypePOD(CHC value) { return _CHC; }

constexpr DTB CATypePOD(FPD value) { return _FPD; }
constexpr DTB CATypePOD(IUD value) { return _IUD; }
constexpr DTB CATypePOD(ISD value) { return _ISD; }
//constexpr DTB CAType(TMD value) { return _TMD; }

//constexpr DTB CAType(FPE value) { return _FPE; }
//constexpr DTB CAType(IUE value) { return _IUE; }
//constexpr DTB CAType(ISE value) { return _ISE; }
//constexpr DTB CAType(TME value) { return _TME; }

template<typename T>
constexpr DTB CATypePOD() {
  T foo = 0;
  return CAType(foo);
}

/* Extracts the Vector type. */
template<typename DT = DTB>
inline DT TTypeVector(DTW type) {
  return DT((type >> 5) & 3);
}
template<typename DT = DTB>
constexpr DT CTypeVector(DTW type) {
  return DT((type >> 5) & 3);
}

/* Extracts the Map type 0-3 of the type. */
template<typename DT = DTB>
inline DT TTypeMap(DTW type) {
  return DT((type >> 8) & 3);
}
template<typename DT = DTB>
constexpr DT CTypeMap(DTW type) {
  return DT((type >> 8) & 3);
}

// Returns the memory alignment mask for this type.
ISA ATypeAlignMask(DTB type) {
  DezNutz:
  if (type <= _CHA) return 0;
  if (type <= _CHB) return 1;
  if (type <= _CHC) return ACPUAlignC;
  if (type <= _TME) return ACPUAlignD;
  if (type <  _ECD) return ACPUAlignD;
  if (type <  _ECC) return ACPUAlignC;
  if (type <  _ECB) return 1;
  if (type <  _ECA) return 0;
  DTB mod = type >> ATypeMDBit0;
  type ^= mod << ATypeMDBit0;
  DTB mt = type >> ATypeMTBit0;
  type ^= mt << ATypeMTBit0;
  DTB sw = type >> ATypeSWBit0;
  type ^= sw << ATypeSWBit0;
  DTB vt = type >> ATypeVTBit0;
  type ^= vt << ATypeVTBit0;
  if (vt == 0) { // Vetor of 2 to 4 Homo-tuples
    type &= (ATypePODTotal - 1);
    goto DezNutz;
  }
  switch (sw) {
  case 0: return 0;
  case 1: return 1;
  case 2: return ACPUAlignC;
  case 3: return ACPUAlignD;
  }
  return ACPUMask;
}
ISA ATypeAlignMask(DTC type) {  return ATypeAlignMask(DTB(type)); }
ISA ATypeAlignMask(DTD type) {  return ATypeAlignMask(DTB(type)); }

/* Aligns the pointer up to the word boundry required by the type. */
template<typename T = void>
T* TATypePtrUp(void* pointer, DTB type) {
  ISW align_mask = ATypeAlignMask(type);
  return reinterpret_cast<T*>(ISW(pointer) + (-ISW(pointer) & align_mask));
}
template<typename T = void>
inline const T* TATypePtrUp(const void* pointer, DTB type) {
  return const_cast<const T*>(TATypePtrUp<T>(const_cast<T*>(pointer), type));
}
template<typename T = void>
T* TATypePtrUp(void* pointer, DTC type) {
  return TATypePtrUp<T>(pointer, DTB(type));
}
template<typename T = void>
const T* TATypePtrUp(const void* pointer, DTC type) {
  return TATypePtrUp<T>(pointer, DTB(type));
}
template<typename T = void>
T* TATypePtrUp(void* pointer, DTD type) {
  return TATypePtrUp<T>(pointer, DTB(type));
}
template<typename T = void>
const T* TATypePtrUp(const void* pointer, DTD type) {
  return TATypePtrUp<T>(pointer, DTB(type));
}

/* Aligns the pointer down to the word boundry required by the type. */
template<typename T = void>
T* TATypePtrDown(void* pointer, DTB type) {
  ISW align_mask = ATypeAlignMask(type);
  return reinterpret_cast<T*>(ISW(pointer) - (ISW(pointer) & align_mask));
}
template<typename T = void>
inline const T* TATypePtrDown(const void* pointer, DTB type) {
  return const_cast<const T*>(TATypePtrDown<T>(const_cast<T*>(pointer), type));
}
template<typename T = void>
T* TATypePtrDown(void* pointer, DTC type) {
  return TATypePtrDown<T>(pointer, DTB(type));
}
template<typename T = void>
const T* TATypePtrDown(const void* pointer, DTC type) {
  return TATypePtrDown<T>(pointer, DTB(type));
}
template<typename T = void>
T* TATypePtrDown(void* pointer, DTD type) {
  return TATypePtrDown<T>(pointer, DTB(type));
}
template<typename T = void>
const T* TATypePtrDown(const void* pointer, DTD type) {
  return TATypePtrDown<T>(pointer, DTB(type));
}

/* Creates an ASCII Vector Data Type. */
template<typename DT = DTB>
inline DT TATypeVector(DTW pod_type, DTW vector_type, DTW width_bit_count = 0) {
  return DT(pod_type | (vector_type << 5) | (width_bit_count << 7));
}
template<typename DT = DTB>
constexpr DT CATypeVector(DTW pod_type, DTW vector_type,
                         DTW width_bit_count = 0) {
  return DT(pod_type | (vector_type << 5) | (width_bit_count << 7));
}

/* Creates an ASCII Map Type. */
template<typename DT = DTB>
constexpr DT CATypeMap(DTW pod_type, DTW map_type, DTW width_bit_count = 0) {
  return DT(pod_type | (map_type << 9) | (width_bit_count << 14));
}
template<typename DT = DTB>
inline DT TATypeMap(DTW pod_type, DTW map_type, DTW width_bit_count = 0) {
  return DT(pod_type | (map_type << 9) | (width_bit_count << 14));
}

template<typename CH = CHR, typename IS = ISN>
const CH* TAErrors(IS index) {
  if (index < 0) index *= -1;
  if (index >= ASCIIErrorCount) index = ASCIIErrorCount;
  return &TAErrors<CH>()[index << 5];
}

/* The ASCII Data Type mask for the SW (Size Width) bits. */
template<typename IS = CHR, typename DT = DTB>
constexpr DT CATypeSW() {
  return (sizeof(IS) ==  1) ? 0 
       : (sizeof(IS) ==  2) ? 1
       : (sizeof(IS) ==  4) ? 2
       : (sizeof(IS) ==  8) ? 3 : 0;
}

/* The ASCII Data Type mask for the SW (Size Width) bits. */
template<typename T, typename DT = DTB>
constexpr DT CATypeSW(DT pod_type) {
  return pod_type | (CATypeSW<T, DT>() << ATypeSWBit0);
}

template<typename T, typename DT = DTB>
inline DT TATypeSW(DT pod_type) {
  return pod_type | (CATypeSW<T, DT>() << ATypeSWBit0);
}

template<typename IS = ISW>
IS TATypeSizeOf(const void* value, DTB type) {
  if (type < ATypePODTotal)
    return ATypeSizeOfPOD(type);
  // | b15:b14 | b13:b9 | b8:b7 | b6:b5 | b4:b0 |
  // |:-------:|:------:|:-----:|:-----:|:-----:|
  // |   MOD   |   MT   |  SW   |  VT   |  POD  |
  DTB mod = type >> ATypeMDBit0;
  if (mod && 1) return sizeof(void*);
  type ^= mod << ATypeMDBit0;
  DTB mt = type >> ATypeMTBit0;
  type ^= mt << ATypeMTBit0;
  DTB sw = type >> ATypeSWBit0;
  type ^= sw << ATypeSWBit0;
  DTB vt = type >> ATypeVTBit0;
  type ^= vt << ATypeVTBit0;
  if (vt == DTB(0)) {
    IS dez  = IS(sw);
    IS nutz = IS(ATypeSizeOfPOD(type));
    return dez * nutz;
  }
  IS size = 1;
  switch (sw) {
    case 0: return IS(*static_cast<const ISA*>(value));
    case 1: return IS(*static_cast<const ISB*>(value));
    case 2: return IS(*static_cast<const ISC*>(value));
  }
  return IS(*static_cast<const ISD*>(value));
}

template<typename IS = ISW>
IS TATypeSizeOf(void* value, DTB type) {
  return TATypeSizeOf<IS>((const void*)value, type);
}
template<typename IS = ISW>
IS TATypeSizeOf(const void* value_base, IS bytes, DTB type) {
  const IUA* vbase = (const IUA*)value_base;
  return TATypeSizeOf<IS>(vbase + bytes, type);
}
template<typename IS = ISW>
IS TATypeSizeOf(void* value_base, IS bytes, DTB type) {
  const void* vbase = (const void*)value_base;
  return TATypeSizeOf<IS>(vbase, bytes, type);
}

/* Returns the ASCII Type for the given floating-point type FP.
FPB:  4   0b00100   (0b001 << 2) | 0b00
FPC:  8   0b01000   (0b010 << 2) | 0b00
FPD: 12   0b01100   (0b011 << 2) | 0b00
FPE: 16   0b10000   (0b100 << 2) | 0b00
*/
template<typename FP, typename DT = DTB>
constexpr DT CATypeFP() {
  return (CATypeSW<FP, DT>() << 2);
}

/* Returns the ASCII Type for the given unsigned integer type IS.
IUA:  1   0b00001   (0b000 << 2) | 0b01
IUB:  5   0b00101   (0b001 << 2) | 0b01
IUC:  9   0b01001   (0b010 << 2) | 0b01
IUD: 13   0b01101   (0b011 << 2) | 0b01
IUE: 17   0b10001   (0b100 << 2) | 0b01
*/
template<typename IU, typename DT = DTB>
constexpr DT CATypeIU() {
  return (CATypeSW<IU, DT>() << 2) | _IUA;
}

/* Returns the ASCII Type for the given signed integer type IS.
ISA:  2   0b00010   (0b000 << 2) | 0b10
ISB:  6   0b00110   (0b001 << 2) | 0b10
ISC: 10   0b01010   (0b010 << 2) | 0b10
ISD: 14   0b01110   (0b011 << 2) | 0b10
ISE: 18   0b10010   (0b100 << 2) | 0b10
*/
template<typename IS, typename DT = DTB>
constexpr DT CATypeIS() {
  return (CATypeSW<IS, DT>() << 2) | _ISA;
}

/* Returns the ASCII Type for the given character type CH.
CHB:  3   0b0011   (0b00 << 2) | 0b11
CHC:  7   0b0111   (0b01 << 2) | 0b11
CHD: 11   0b1011   (0b10 << 2) | 0b11
CHE: 15   0b1111   (0b11 << 2) | 0b11

template<typename CH, typename DT = DTB>
constexpr DT CATypeCH() {
  return (CATypeSize<CH, DT>() << 2) | 3;
} */

/* Extracts the UTF type.
@return 0 if the type is not a stirng type or 1, 2, or 4 if it is. */
inline ISA ATypeTextFormat(DTW type) {
  DTW pod_type = type & ATypePODMask;
  if (pod_type == type) return -1;  //< then core_type < 32
  type >>= ATypePODBits;
  DTW vt = type & 3;
  type >>= 2;
  DTW sw = type & 3;
  if (vt != _SCK) return -1;

  if (pod_type == _CHA) return 1;
  if (pod_type == _CHB) return 2;
  if (pod_type <= _CHC) return 3;
  return -1;
}

/* Gets the alignment mask of the given type. */
inline DTW AlignmentMask(CHA item) { return 0; }
inline DTW AlignmentMask(ISA item) { return 0; }
inline DTW AlignmentMask(IUA item) { return 0; }
inline DTW AlignmentMask(CHB item) { return 1; }
inline DTW AlignmentMask(ISB item) { return 1; }
inline DTW AlignmentMask(IUB item) { return 1; }
inline DTW AlignmentMask(CHC item) { return 3; }
inline DTW AlignmentMask(ISC item) { return 3; }
inline DTW AlignmentMask(IUC item) { return 3; }
inline DTW AlignmentMask(FPC item) { return 3; }
inline DTW AlignmentMask(ISD item) { return 7; }
inline DTW AlignmentMask(IUD item) { return 7; }
inline DTW AlignmentMask(FPD item) { return 7; }
inline DTW AlignmentMask(void* item) { return ACPUMask; }
inline DTW AlignmentMask(const void* item) { return ACPUMask; }

/* Gets the type of the given item. */
inline DTW TypeOf(CHA item) { return _CHA; }
inline DTW TypeOf(ISA item) { return _ISA; }
inline DTW TypeOf(IUA item) { return _IUA; }
inline DTW TypeOf(CHB item) { return _CHB; }
inline DTW TypeOf(ISB item) { return _ISB; }
inline DTW TypeOf(IUB item) { return _IUB; }
inline DTW TypeOf(CHC item) { return _CHB; }
inline DTW TypeOf(ISC item) { return _ISC; }
inline DTW TypeOf(IUC item) { return _IUC; }
inline DTW TypeOf(FPC item) { return _FPC; }
inline DTW TypeOf(ISD item) { return _ISD; }
inline DTW TypeOf(IUD item) { return _IUD; }
inline DTW TypeOf(FPD item) { return _FPD; }
inline DTW TypeOf(CHA* item) { return _STA; }
inline DTW TypeOf(const CHA* item) { return _CNS_STA; }
inline DTW TypeOf(void* item) { return _PTR; }
inline DTW TypeOf(const void* item) { return _CNS_PTR; }

template<typename IS>
inline BOL TSizeIsValid(IS size) {
  return (size & (sizeof(IS) - 1)) == 0;
}

/* A ROM  for one of the 32 types.
C++11 variadic templates ensure there is only one copy in of the given in ROM.

template<CHA CharA, CHA CharB, CHA CharC>
inline IUC T() {
  return ((IUC)CharA) & (((IUC)CharB) << 8) & (((IUC)CharC) << 16);
}*/

/* Masks off the primary type. */
inline ISA ATypeMaskPOD(DTW value) { return value & 0x1f; }

/* Returns true if the given type is an Array type. */
inline BOL ATypeIsArray(DTW type) { return type >= ATypePODTotal; }

inline ISN ATypeSizeWidthCode(ISN type) { return type >> 6; }

/* Extracts the Map Type. */
inline DTW ATypeMap(DTW core_type, DTW map_type) {
  return core_type | (map_type << (ATypePODBits + 2));
}

inline DTW ATypeMap(DTW core_type, DTW map_type, DTW size_width) {
  return ATypeMap(core_type, map_type) | (size_width << ATypePODBits);
}

inline BOL ATypeIsPOD(DTW type) {
  return !((type >> 5) || (type & ATypePODMask));
}

}  //< namespace _
#endif  //< #if SEAM >= SCRIPT2_COUT
#endif  //< #ifndef INCLUDED_TYPES_INLINE_CODE
