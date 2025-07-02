// Copyright Kabuki Starship <kabukistarship.com>.
#include "AType.hpp"
//
#include "Array.h"
#if SEAM == SCRIPT2_COUT
#include "_Debug.h"
#else
#include "_Release.h"
#endif
namespace _ {

#if SEAM >= SCRIPT2_UNIPRINTER
DTB ATypeRemapEP(DTW sw_vt_bits, DTW pod_type, DTD ep_remap) {
  return DTB((pod_type >> (pod_type - _PCa) * 5) & ATypePODMask);
}

DTW ACTXHandlerDefault(void* begin, void* end, DTW type, IUW value, IUW vmsb) {
  static const IUD Map = (IUD(_ISA) << _PCaBit0) | (IUD(_ISA) << _PCbBit0) |
                         (IUD(_CHC) << _PCcBit0) | (IUD(_FPD) << _PCdBit0) |
                         (IUD(_TMD) << _PCeBit0) | (IUD(_TME) << _PCfBit0) |
                         (IUD(_FPE) << _PCgBit0) | (IUD(_TME) << _PChBit0) |
                         (IUD(_IUD) << _PCiBit0) | (IUD(_IUE) << _PCjBit0) |
                         (IUD(_IUE) << _PCkBit0) | (IUD(_IUE) << _PClBit0);
  static CHR PCStrings[12][4]{
    {'P','C','a', 0}, {'P','C','b', 0}, {'P','C','c', 0}, {'P','C','d', 0},
    {'P','C','e', 0}, {'P','C','f', 0}, {'P','C','g', 0}, {'P','C','h', 0},
    {'P','C','i', 0}, {'P','C','j', 0}, {'P','C','k', 0}, {'P','C','l', 0},
  };  //< Dez Nutz a-l takes up 192 bytes in UTF-32 or 48 with UTF-8
  static CHR ECStrings[ATypeCTXTotal][4]{
    {'C','0','0', 0}, {'C','0','1', 0}, {'C','0','2', 0}, {'C','0','3', 0},
    {'C','0','4', 0}, {'C','0','5', 0}, {'C','0','6', 0}, {'C','0','7', 0},
    {'C','0','8', 0}, {'C','0','9', 0}, {'C','1','0', 0}, {'C','1','1', 0},
    {'C','1','2', 0}, {'C','1','3', 0}, {'C','1','4', 0}, {'C','1','5', 0},
    {'C','1','6', 0}, {'C','1','7', 0}, {'C','1','8', 0}, {'C','1','9', 0},
    {'C','2','0', 0}, {'C','2','1', 0}, {'C','2','2', 0}, {'C','2','3', 0},
    {'C','2','4', 0}, {'C','2','5', 0}, {'C','2','6', 0}, {'C','2','7', 0},
    {'C','2','8', 0}, {'C','2','9', 0}, {'C','3','0', 0}, {'C','3','1', 0},
    {'C','3','2', 0}, {'C','3','3', 0}, {'C','3','4', 0}, {'C','3','5', 0},
    {'C','3','6', 0}, {'C','3','7', 0}, {'C','3','8', 0}, {'C','3','9', 0},
    {'C','4','0', 0}, {'C','4','1', 0}, {'C','4','2', 0}, {'C','4','3', 0},
    {'C','4','4', 0}, {'C','4','5', 0}, {'C','4','6', 0}, {'C','4','7', 0},
    {'C','4','8', 0}, {'C','4','9', 0}, {'C','5','0', 0}, {'C','5','1', 0},
    {'C','5','2', 0}, {'C','5','3', 0}, {'C','5','4', 0}, {'C','5','5', 0},
    {'C','5','6', 0}, {'C','5','7', 0}, {'C','5','8', 0}, {'C','5','9', 0},
    {'C','6','0', 0}, {'C','6','1', 0}, {'C','6','2', 0}, {'C','6','3', 0},
    {'C','6','4', 0}, {'C','6','5', 0}, {'C','6','6', 0}, {'C','6','7', 0},
    {'C','6','8', 0}, {'C','6','9', 0}, {'C','7','0', 0}, {'C','7','1', 0}
  };  //< Takes up 1152 bytes in UTF-32, 288 with UTF-8.
  //< 336-1344 bytes is enough for ARM assembly to offset the instruction pointer
  //< from to avoid having to load it from the .bss section. I forgot if this is
  //< optimal in x86 assembly.
  
  // Array that stores if it's a POD type.
  static const ISA ECAlign[12]{
    0,
    0,
    ACPUAlignC,
    ACPUAlignD,
    ACPUAlignE,
    ACPUAlignE,
    ACPUAlignE,
    ACPUAlignD,
    ACPUAlignD,
    ACPUAlignE,
    ACPUAlignE,
    ACPUAlignE,
  };
  #if CPU_SIZE != CPU_2_BYTES
  const DTW Action = type >> 16;
  type ^= Action << 16;
  #endif
  const DTW SW_VT = type >> ATypePODBits;
  const DTW POD = type & ATypePODMask;
  if (!begin && !end) {
    DTW align_mask = ECAlign[POD - _PCa];
    if (value) return 72;
    return align_mask;
  }
  if (!ATypeIsCTX(SW_VT, POD)) return 0;
  DTW ctx_index = ATypeToCTX_NC(SW_VT, POD);
  if (!begin) return ATypeRemapEP(SW_VT, POD, Map);
  if (!end) return DTW(PCStrings + (POD - _PCa));

  #if CPU_SIZE != CPU_2_BYTE
  switch (Action) {
    #ifdef USING_STA
    case ACTXFunPrintSTA: {
      TSPrinter<CHA> p_a((CHA*)begin, (CHA*)end);
      while (ctx_index-- > 0) p_a.Hex(IUA(ctx_index));
      return DTW(p_a.start);
    }
    #endif
    #ifdef USING_STB
    case ACTXFunPrintSTB: {
      TSPrinter<CHB> p_b((CHB*)begin, (CHB*)end);
      while (ctx_index-- > 0) p_b.Hex(IUA(ctx_index));
      return DTW(p_b.start);
    }
    #endif
    #ifdef USING_STC
    case ACTXFunPrintSTC: {
      TSPrinter<CHC> p_c((CHC*)begin, (CHC*)end);
      while (ctx_index-- > 0) p_c.Hex(IUA(ctx_index));
      return DTW(p_c.start);
    }
    #endif
    case ACTXFunWrite: {
      #if SEAM >= SCRIPT2_STACK
      return ArrayCopy(begin, end, (void*)value, ISW(vmsb));
      #else
      return 0;
      #endif
    }
  }
  #endif

  return 0;
}

ACTXFrame::ACTXFrame() :
  handler(ACTX_HANDLER_INIT),
  epoch(AClockEpochInit)
{}

ACTXFrame* ACTX() {
  static IUW frame[(sizeof(ACTXFrame) + ACPUCacheLineSize) >> ACPUBytesLog2];
  return (ACTXFrame*)(ISW(frame) + (-ISW(frame) & ISW(0x3f)));
}
  
DTW ACTXHandle(ACTXHandler actxh, void* begin, void* end, DTW type, IUW value,
               IUW vmsb) {
  if (actxh) return actxh(begin, end, type, value, vmsb);
  return 0;
}

DTW ACTXHandle(void* begin, void* end, DTW type, IUW value, IUW vmsb) {
  return ACTXHandle(ACTX()->handler, begin, end, type, value, vmsb);
}
#endif

DTB ATypeMDDeassert(DTW type) {
  const DTW MD = (type >> ATypeMDBit0) & 0x3;
  type ^= MD << ATypeMDBit0;
  return DTB(type ^ DTW(MD << ATypeMDBit0));
}

DTB ATypeMDP(DTW type) {
  const DTW MD = (type >> ATypeMDBit0) & 0x3;
  type ^= MD << ATypeMDBit0;
  return DTB(type ^ DTW(_MDP << ATypeMDBit0));
}

DTB ATypeMDI(DTW type) {
  const DTW MD = (type >> ATypeMDBit0) & 0x3;
  type ^= MD << ATypeMDBit0;
  return DTB(type ^ DTW(_MDI << ATypeMDBit0));
}

DTB ATypeMDC(DTW type) {
  const DTW MD = (type >> ATypeMDBit0) & 0x3;
  type ^= MD << ATypeMDBit0;
  return DTB(type ^ DTW(_MDC << ATypeMDBit0));
}

DTB ATypeCNS(DTW type) {
  return DTB(ATypeCNSBit | type);
}

DTB ATypeCNS_MDP(DTW type) {
  return DTB(ATypeCNSBit | ATypeMDP(type));
}

DTB ATypeCNS_MDI(DTW type) {
  return DTB(ATypeCNSBit | ATypeMDI(type));
}

DTB ATypeCNS_MDC(DTW type) {
  return DTB(ATypeCNSBit | ATypeMDC(type));
}

IUE::IUE(IUB v1, IUB v2, IUB v3, IUB v4, IUB v5, IUB v6, IUB v7, IUB v8) :
  lsb(IUC(v1) & IUD(v2) << 16 & IUD(v3) << 32 & IUD(v4) << 48),
  msb(IUD(v5) & IUD(v6) << 16 & IUD(v7) << 32 & IUD(v8) << 48) {}

IUE::IUE(IUC v1, IUC v2, IUC v3, IUC v4) :
  lsb(IUD(v1)& IUD(v2) << 32),
  msb(IUD(v2)& IUD(v3) << 32) {}

IUE::IUE(IUD lsb, IUD msb) : lsb(lsb), msb(msb) {}

ISE::ISE(IUB v1, IUB v2, IUB v3, IUB v4, IUB v5, IUB v6, IUB v7, IUB v8) :
  lsb(IUD(v1)& IUD(v2) << 16 & IUD(v3) << 32 & IUD(v4) << 48),
  msb(IUD(v5)& IUD(v6) << 16 & IUD(v7) << 32 & IUD(v8) << 48) {}

ISE::ISE(IUC v1, IUC v2, IUC v3, IUC v4) :
  lsb(IUD(v1)& IUD(v2) << 32),
  msb(IUD(v2)& IUD(v3) << 32) {}

ISE::ISE(IUD lsb, IUD msb) : lsb(lsb), msb(msb) {}

#if CPU_SIZE == CPU_2_BYTES
FPC::FPC(IUB lsb, IUB msb) : lsb(lsb), msb(msb) {}
#endif

#if CPU_SIZE <= CPU_4_BYTES
FPD::FPD(IUB v1, IUB v2, IUB v3, IUB v4) :
  lsb(IUB(v1) & IUB(v2) << 32),
  msb(IUB(v2) & IUB(v3) << 32) {}

FPD::FPD(IUC lsb, IUC msb) : lsb(lsb), msb(msb) {}
#endif

FPE::FPE(IUB v1, IUB v2, IUB v3, IUB v4, IUB v5, IUB v6, IUB v7, IUB v8) :
  lsb(IUD(v1) & IUD(v2) << 16 & IUD(v3) << 32 & IUD(v4) << 48),
  msb(IUD(v5) & IUD(v6) << 16 & IUD(v7) << 32 & IUD(v8) << 48) {}

FPE::FPE(IUC v1, IUC v2, IUC v3, IUC v4) :
  lsb(IUD(v1) & IUD(v2) << 32),
  msb(IUD(v2) & IUD(v3) << 32) {}

FPE::FPE(IUD lsb, IUD msb) : lsb(lsb), msb(msb) {}

DTB ATypePack(DTB pod, DTB vt) {
  return pod | vt << ATypeVTBit0;
}

DTB ATypePack(DTB pod, DTB vt, DTB sw) {
  return pod | vt << ATypeVTBit0 | sw << ATypeSWBit0;
}

DTB ATypePack(DTB pod, DTB vt, DTB sw, DTB mt) {
  return pod | vt << ATypeVTBit0 | sw << ATypeSWBit0 | mt << ATypeMTBit0;
}

DTB ATypePack(DTB pod, DTB vt, DTB sw, DTB mt, DTB mod) {
  return pod | vt << ATypeVTBit0 | sw << ATypeSWBit0 | mt << ATypeMTBit0 |
         mod << ATypeMDBit0;
}

BOL ATypeIsCH(DTB type) {
  // CHA: 3   0b0011
  // CHB: 7   0b0111
  // CHC: 11  0b1011
  //return (type & 3) && (type != 15);
  return type == _CHA || type == _CHB || type == _CHC;
}

BOL ATypeVTBits(DTB type) {
  //| b15 | b14:b13 | b12:b9 | b8:b7 | b6:b5 | b4:b0 |
  //|:---:|:-------:|:------:|:-----:|:-----:|:-----:|
  //| CNS |    MD   |   MT   |  SW   |  VT   |  POD  |
  const DTB mask = 3,
        VT = (type >> ATypeVTBit0) & mask,
        MT = (type >> ATypeMTBit0) & mask;
  return (VT != _ARY || MT != 0) ? -1 : VT;
}

// Retrusn the size of an ASCII POD Type 0-31 in bytes.
ISA ATypeSizeOfPOD(DTB type) {
  if (type <= 0) return 0;
  if (type <= _CHA) return 1;
  if (type <= _CHB) return 2;
  if (type <= _CHC) return 4;
  if (type <= _TMD) return 8;
  if (type <= _TME) return 16;
#if USING_CT5
  if (type <= _CT5) return 16;
#endif
#if USING_CT4
  if (type <= _CT4) return 8;
#endif
#if USING_CT3
  if (type <= _CT3) return 4;
#endif
#if USING_CT2
  if (type <= _CT2) return 2;
#endif
  if (type <= 31) return 1;
  return 0;
}

ISW ATypeBytes(const void* value, DTB type) {
  return TATypeSizeOf<ISW>(value, type);
}

ISW ATypeBytes(const void* value_base, ISA bytes, DTB type) {
  return ATypeBytes(TPtr<>(value_base, bytes), type);
}

void* ATypeValueEnd(void* value, DTB type) {
  return TPtr<void>(value, ATypeBytes(value, type));
}

// Returns an array of the customizable POD type sizes.
//const ISA* ATypeCustomSize() {
//  return NILP;
//}

// Returns an array of the user-defined type alignment masks.
//const ISA* ATypeCustomAlignMask() {
//  return NILP;
//}

// Returns the custom time alignment mask for the given type.
//ISA ATypeCustomAlignMask(DTA type) {
//  return 0;
//}

/* Converts an ASCII Data Type to Extended Type.
Extended Types include 
@pre    Dev shall deassert MOD bits.
@return 0 if the type is not Extended, negative if it's Extended Standard, and 
positive if its a Plain Context type. */
DTB ATypeToEXT_NC(DTW type_msb, DTW type_pod) {
  DTB msb = DTB(type_msb),
      pod = DTB(type_pod);
  if (msb > 11 || (msb & 3) == 0) return 0;
  // Checking if it's a context type.
  // @todo Can I replace some of the msb with constants?
  if (pod >= _PCe)  return ((msb - 1) << 3) | (pod - _PCe);   //< A
  if (pod >= _PCa) {
    if (msb < 6)
      return ((msb + 15) << 2) | (pod - _PCa);  //< B
    if (msb >  9)
      return ((msb -  4) << 2) | (pod - _PCa);  //< C
    if (msb <  9) 
      return ((msb +  8) << 2) | (pod - _PCa);  //< D
    // then (sw_vt == 9)
    return ((msb + 10) << 2) | (pod - _PCa);    //< E
  }
  // Checking if it's an extended type.
  if (pod < _FPB || msb > 5 || msb > 1 && pod < _FPC) return 0;
  if (pod >= _FPD) return -(((msb - 1) << 3) | (pod - _FPD));              //< F
  if (pod >= _FPC && msb <= 3) return -(((msb + 9) << 2) | (pod - _FPC));  //< G
  return -((3 << 3) | (pod - _FPB)); //< H
}
DTB ATypeToEXT(DTW type) {
  type &= (~DTB(0) >> 2); //< Don't care if it's const or ptr.
  const DTW SW_VT = type >> ATypeVTBit0;
  return ATypeToEXT_NC(SW_VT, type ^ SW_VT << ATypeVTBit0);
}
DTB ATypeToEXT(DTW type_msb, DTW type_pod ) {
  return ATypeToEXT((type_msb << ATypeVTBit0) | type_pod);
}

BOL ATypeIsEXT(DTW sw_vt, DTW pod) {
  if (sw_vt && !pod)
    return true; //< A
  if ((sw_vt & 3) == 0 || sw_vt >= 12)
    return false; //< VHT
  if (pod >= _FPE)
    return true; //< B
  DTW type_m4 = (pod >> 2) & 3; //< @todo I don't think I need the &3
  DTW sw_vt_shift = sw_vt + 3;
  return !(sw_vt_shift > type_m4 * 4);
}

/* Checks if the type is an Extended Type.
@see ~/Spec/Data/ExtendedTypes#FasterEXTBooleanMethod */
BOL ATypeIsEXT(DTW type) {
  type &= ~(3 << ATypeMDBit0); //< Don't care if it's const or ptr.
  //type &= ATypePODMask;
  const DTW MSb = type >> ATypeVTBit0;
  return ATypeIsEXT(MSb, type ^ (MSb << ATypeVTBit0));
}

BOL ATypeIsCTX(DTW sw_vt, DTW pod) {
  return pod >= _PCa && sw_vt <= 11 && sw_vt != 4 && sw_vt != 8;
}

BOL ATypeIsCTX(DTW type) {
  type &= (DTW(-1) >> 2); //< Don't care if it's const or ptr.
  const DTW SW_VT = type >> ATypeVTBit0;
  return ATypeIsCTX(SW_VT, type ^ (SW_VT << DTW(ATypeVTBit0)));
}

DTW ATypeToCTX_NC(DTW sw_vt, DTW pod) {
  if(pod >= _PCa) return ATypeCTXStart + 8 +
    (((sw_vt - 5) << (ATypeVTBit0 - 2)) | (pod - 24));  //< C
  if (sw_vt <= 7)
    return ATypeCTXStart + (((sw_vt - 5) << ATypeVTBit0) | (pod - 16)); //< D
  return ATypeCTXStart + (((sw_vt - 9) << ATypeVTBit0) | (pod - 20));  //< E
}

DTB ATypeRemapEP_NC(DTW pod_type, DTW ep_remap) {
  return (pod_type >> (pod_type - _PCa) * 5) & ATypePODMask;
}

Nil::Nil() {}
constexpr ISW Nil::Size() { return 0; }
constexpr ISW Nil::Bytes() { return 0; }
constexpr ISW Nil::SizeWords() { return 0; }
IUW* Nil::Words() { return NILP; }















ATypeValue::ATypeValue() : type_(_NIL), value_(0), vmsb_(0) {}

#if USING_STA == YES_0
ATypeValue::ATypeValue(CHA value) : type_(_CHA), value_(IUW(value)), vmsb_(0) {}
ATypeValue::ATypeValue(const CHA* value)
    : type_(_STA), value_(IUW(value)), vmsb_(0) {}
#endif
#if USING_STB == YES_0
ATypeValue::ATypeValue(CHB value) : type_(_CHB), value_(IUW(value)), vmsb_(0) {}
ATypeValue::ATypeValue(const CHB* value)
    : type_(_STB), value_(IUW(value)), vmsb_(0) {}
#endif
#if USING_STC == YES_0
ATypeValue::ATypeValue(CHC value) : type_(_CHC), value_(IUW(value)), vmsb_(0) {}
ATypeValue::ATypeValue(const CHC* value)
    : type_(_STC), value_(IUW(value)), vmsb_(0) {}
#endif
ATypeValue::ATypeValue(ISA value) : type_(_ISA), value_(IUW(value)), vmsb_(0) {}
ATypeValue::ATypeValue(IUA value) : type_(_IUA), value_(IUW(value)), vmsb_(0) {}
ATypeValue::ATypeValue(ISB value) : type_(_ISB), value_(IUW(value)), vmsb_(0) {}
ATypeValue::ATypeValue(IUB value) : type_(_IUB), value_(IUW(value)), vmsb_(0) {}
#if CPU_SIZE == CPU_2_BYTE
AValue::AValue(ISC value) : type_(_ISC) {
  // @todo I don't know if this is going to be needed. In my mind the compiler
  // will push the word_ onto the program stack because of the *reintpret_cast.
  // This might however get optimized into just storing value. Dissassemble me!
  *TPtr<ISC>(&word_) = value;
}
#else
ATypeValue::ATypeValue(ISC value) : type_(_ISC), value_(IUW(value)), vmsb_(0) {}
#endif

#if CPU_SIZE == CPU_2_BYTE
AValue::AValue(IUC value) : type_(_IUC) {
  *TPtr<IUC>(&word_) = value;
}
#else
ATypeValue::ATypeValue(IUC value) : type_(_IUC), value_(IUW(value)), vmsb_(0) {}
#endif

#if CPU_SIZE == CPU_8_BYTE
ATypeValue::ATypeValue(ISD value) : type_(_ISD), value_(IUW(value)), vmsb_(0) {}
#else
AValue::AValue(ISD value) : type_(_ISD) { *TPtr<ISD>(&word_) = value; }
#endif

#if CPU_SIZE == CPU_8_BYTE
ATypeValue::ATypeValue(IUD value) : type_(_IUD), value_(IUW(value)), vmsb_(0) {}
#else
AValue::AValue(IUD value) : type_(_IUD) {
  *TPtr<IUD>(&word_) = value;
}

#endif
#if USING_FPC == YES_0
#if CPU_SIZE == CPU_8_BYTE
ATypeValue::ATypeValue(FPC value)
    : type_(_FPC), value_(ToUnsigned(value)), vmsb_(0) {}
#else
AValue::AValue(FPC value) : type_(_FPC) { *TPtr<FPC>(&word_) = value; }
#endif
#endif

#if USING_FPD == YES_0
#if CPU_SIZE == CPU_8_BYTE
ATypeValue::ATypeValue(FPD value)
    : type_(_FPD), value_(ToUnsigned(value)), vmsb_(0) {}
#else
AValue::AValue(FPD value) : type_(_FPD) { *TPtr<FPD>(&word_) = value; }
#endif
#endif

ATypeValue::ATypeValue(void* value) : 
  type_(_PTR), value_(IUW(value)), vmsb_(0) {}
ATypeValue::ATypeValue(const void* value) :
  type_(_CNS_PTR), value_(IUW(value)), vmsb_(0) {}

ATypeValue::ATypeValue(void* base_ptr, ISW offset) :
  type_(_PTR), value_(IUW(ISW(base_ptr) + offset)), vmsb_(0) {}
ATypeValue::ATypeValue(const void* base_ptr, ISW offset) :
  type_(_CNS_PTR), value_(IUW(ISW(base_ptr) + offset)), vmsb_(0) {}

ATypeValue::ATypeValue(DTW type, void* value) :
  type_(type), value_(IUW(value)), vmsb_(0) {}
ATypeValue::ATypeValue(DTW type, const void* value) :
  type_(type), value_(IUW(value)), vmsb_(0) {}

ATypeValue::ATypeValue(DTW type, void* base_ptr, ISW offset) :
  type_(type), value_(IUW(ISW(base_ptr) + offset)), vmsb_(0) {}
ATypeValue::ATypeValue(DTW type, const void* base_ptr, ISW offset) :
  type_(type), value_(IUW(ISW(base_ptr) + offset)), vmsb_(0) {}

ATypeValue::ATypeValue(DTW type, void* value, void* value_end) :
  type_(type) {
  Set(type, value, value_end);
}

ATypeValue::ATypeValue(DTW type, const void* value, const void* value_end) : 
  type_(type) {
  Set(type, value, value_end);
}

ATypeValue::ATypeValue(DTW type, void* base_ptr, ISW offset, void* value_end) {
  Set(type, base_ptr, offset, value_end);
}

ATypeValue::ATypeValue(DTW type, const void* base_ptr, ISW offset, 
                       const void* value_end) {
  Set(type, base_ptr, offset, value_end);
}

ATypeValue::ATypeValue(DTW type, void* base_ptr, ISW offset,
  ISW base_bytes) {
  Set(type, base_ptr, offset, base_bytes);
}

ATypeValue::ATypeValue(DTW type, const void* base_ptr, ISW offset, 
                       ISW base_bytes) {
  Set(type, base_ptr, offset, base_bytes);
}


DTW ATypeValue::Type() { return type_; }

DTW ATypeValue::UnicodeFormat() { return ATypeTextFormat(type_); }

void* ATypeValue::WordPTR() { return &value_; }

void* ATypeValue::ToPTR() { return TPtr<void>(value_); }
CHA* ATypeValue::ToSTA() { return TPtr<CHA>(value_); }
CHB* ATypeValue::ToSTB() { return TPtr<CHB>(value_); }
CHC* ATypeValue::ToSTC() { return TPtr<CHC>(value_); }
IUA ATypeValue::ToIUA() { return IUA(value_); }
IUB ATypeValue::ToIUB() { return IUB(value_); }
IUN ATypeValue::ToIUN() { return IUN(value_); }
IUC ATypeValue::ToIUC() {
#if CPU_SIZE == CPU_2_BYTE
  // @todo Inspect dissassembly to check if we even need the #if #else here.
  // I have a feeling the compiler will optmize away memory copies I think
  // I'm avoiding.
  return *TPtr<IUC>(&word_);
#else
  return IUC(value_);
#endif
}
IUD ATypeValue::ToUID() {
#if CPU_SIZE == CPU_8_BYTE
  return value_;
#else
  // @todo Inspect dissassembly to check if we even need the #if #else here.
  // I have a feeling the compiler will optmize away memory copies I think
  // I'm avoiding.
  return *TPtr<IUD>(&word_);
#endif
}

IUW ATypeValue::Value() { return value_; }
IUW ATypeValue::MSB() { return vmsb_; }

void ATypeValue::SetWord(IUW value) { value_ = value; }
void ATypeValue::SetWord2(IUW value) { vmsb_ = value; }
void ATypeValue::SetNIL() { type_ = value_ = _NIL; }
void ATypeValue::SetNIL(IUW value) {
  type_ = _NIL;
  value_ = value;
}

inline void* ATypeValue::Set(void* value) {
  if (!value) D_RETURN_TPTR_ERROR(void, -ErrorParamPointer);
  ATypeMDP(_PTR);
  value_ = IUW(value);
  return NILP;
}

inline const void* ATypeValue::Set(const void* value)
{
  if (!value) D_RETURN_TPTR_ERROR(void, -ErrorParamPointer);
  ATypeMDP(_PTR);
  value_ = IUW(value);
  return NILP;
}

inline void* ATypeValue::Set(void* base_ptr, ISW voffset) {
  if (!base_ptr) D_RETURN_TPTR_ERROR(void, -ErrorParamPointer);
  ATypeMDP(_PTR);
  value_ = IUW(ISW(base_ptr) + voffset);
  return NILP;
}

inline const void* ATypeValue::Set(const void* base_ptr, ISW voffset)
{
  if (!base_ptr) D_RETURN_TPTR_ERROR(void, -ErrorParamPointer);
  ATypeMDP(_PTR);
  value_ = IUW(ISW(base_ptr) + voffset);
  return NILP;
}

inline void* ATypeValue::Set(DTW type, void* value) {
  if (!value) D_RETURN_TPTR_ERROR(void, -ErrorParamPointer);
  ATypeMDP(type);
  value_ = IUW(value);
  vmsb_  = 0;
  return NILP;
}

inline const void* ATypeValue::Set(DTW type, const void* value)
{
  if (!value) D_RETURN_TPTR_ERROR(void, -ErrorParamPointer);
  ATypeMDP(type);
  value_ = IUW(value);
  vmsb_ = 0;
  return NILP;
}

inline void* ATypeValue::Set(DTW type, void* base_ptr, ISW voffset) {
  if (!base_ptr || voffset < 0) D_RETURN_TPTR_ERROR(void, -ErrorParamPointer);
  ATypeMDP(type);
  value_ = IUW(ISW(base_ptr) + voffset);
  return NILP;
}

inline const void* ATypeValue::Set(DTW type, const void* base_ptr, ISW voffset) {
  if (!base_ptr || voffset < 0) D_RETURN_TPTR_ERROR(void, -ErrorParamPointer);
  ATypeMDP(type);
  value_ = IUW(ISW(base_ptr) + voffset);
  return NILP;
}

inline void* ATypeValue::Set(DTW type, void* value, void* value_end) {
  if (!value || !value_end) D_RETURN_TPTR_ERROR(void, -ErrorParamPointer);
  ATypeMDP(type);
  value_ = IUW(value);
  vmsb_ = IUW(value_end);
  return NILP;
}

inline const void* ATypeValue::Set(DTW type, const void* value, 
                                   const void* value_end) {
  if (!value || !value_end) D_RETURN_TPTR_ERROR(void, -ErrorParamPointer);
  ATypeMDP(type);
  value_ = IUW(value);
  vmsb_ = IUW(value_end);
  return NILP;
}

inline void* ATypeValue::Set(DTW type, void* base_ptr, ISW offset, 
                             void* value_end) {
  return Set(type, TPtr<>(base_ptr, offset), value_end);
}

inline const void* ATypeValue::Set(DTW type, const void* base_ptr, ISW offset,
                             const void* value_end) {
  return Set(type, TPtr<>(base_ptr, offset), value_end);
}

inline void* ATypeValue::Set(DTW type, void* base_ptr, ISW offset, 
                             ISW base_bytes) {
  return Set(type, TPtr<>(base_ptr, offset), TPtr<>(base_ptr, base_bytes));
}

inline const void* ATypeValue::Set(DTW type, const void* base_ptr, ISW offset,
                             ISW base_bytes) {
  return Set(type, TPtr<>(base_ptr, offset), TPtr<>(base_ptr, base_bytes));
}

#if USING_STA == YES_0
void ATypeValue::Set(CHA value) {
  type_ = _CHA;
  value_ = IUW(value);
  vmsb_ = 0;
}
void ATypeValue::Set(const CHA* value) {
  type_ = CATypeMap(_STA, _CNS_PTR);
  value_ = IUW(value);
  vmsb_ = 0;
}
#endif
#if USING_STB == YES_0
void ATypeValue::Set(CHB value) {
  type_ = _CHB;
  value_ = IUW(value);
  vmsb_ = 0;
}
void ATypeValue::Set(const CHB* value) {
  type_ = _STB;
  value_ = IUW(value);
  vmsb_ = 0;
}
#endif
#if USING_STC == YES_0
void ATypeValue::Set(CHC value) {
  type_ = _CHC;
  value_ = IUW(value);
  vmsb_ = 0;
}
void ATypeValue::Set(const CHC* value) {
  type_ = _STC;
  value_ = IUW(value);
  vmsb_ = 0;
}
#endif
void ATypeValue::Set(ISA value) {
  type_ = _ISA;
  value_ = IUW(value);
  vmsb_ = 0;
}
void ATypeValue::Set(IUA value) {
  type_ = _IUA;
  value_ = IUW(value);
  vmsb_ = 0;
}
void ATypeValue::Set(ISB value) {
  type_ = _ISB;
  value_ = IUW(value);
  vmsb_ = 0;
}
void ATypeValue::Set(IUB value) {
  type_ = _IUB;
  value_ = IUW(value);
  vmsb_ = 0;
}
void ATypeValue::Set(BOL value) {
  type_ = _BOL;
  value_ = IUW(value);
  vmsb_ = 0;
}
void ATypeValue::Set(ISC value) {
  type_ = _ISC;
  value_ = IUW(value);
  vmsb_ = 0;
}
void ATypeValue::Set(IUC value) {
  type_ = _IUC;
  value_ = IUW(value);
  vmsb_ = 0;
}
void ATypeValue::Set(ISD value) {
  type_ = _ISD;
  value_ = IUW(value);
  vmsb_ = 0;
}
void ATypeValue::Set(IUD value) {
  type_ = _IUD;
  value_ = IUW(value);
  vmsb_ = 0;
}
#if USING_FPC == YES_0
void ATypeValue::Set(FPC value) {
  type_ = _FPC;
  value_ = IUW(value);
  vmsb_ = 0;
}
#endif
#if USING_FPD == YES_0
void ATypeValue::Set(FPD value) {
  type_ = _FPD;
  value_ = IUW(value);
  vmsb_ = 0;
}
#endif

}  //< namespace _
