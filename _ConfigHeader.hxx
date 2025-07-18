// Copyright AStarship <https://astarship.net>.

#include <_Seams.hxx>

#define SCRIPT2 0

#define YES_0 0
#define NO_0 1

#define STRING_TYPE_A 1  //< UTF-8.
#define STRING_TYPE_B 2  //< UTF-16.
#define STRING_TYPE_C 3  //< UTF-32.
#define STRING_TYPE_D 4  //< MSB-variant encoding.

#define ATYPE_8BIT    0  //< Code 0-3 maps to A-D for 8-bit ASCII size-width.
#define ATYPE_16BIT   1  //< Code 0-3 maps to A-D for 16-bit ASCII size-width.
#define ATYPE_32BIT   2  //< Code 0-3 maps to A-D for 32-bit ASCII size-width.
#define ATYPE_64BIT   3  //< Code 0-3 maps to A-D for 64-bit ASCII size-width.

#define PLATFORM_BARE_METAL 1
#define PLATFORM_MBED_BARE_METAL 2
#define PLATFORM_MBED_OS 3
#define PLATFORM_ARDUINO 4
#define PLATFORM_WIN32 5
#define PLATFORM_WINDOWS 6
#define PLATFORM_ANDROID 7
#define PLATFORM_LINUX 8
#define PLATFORM_OSX 9
#define PLATFORM_IOS 10

#define CPU_X86 1
#define CPU_X64 2
#define CPU_ARM8 3
#define CPU_ARM16 4
#define CPU_ARM32 5
#define CPU_ARM64 6

#include <cstdint>
#if defined(_MSC_VER) && defined(_M_AMD64)
#define USING_VISUAL_CPP_X64 1
#include <intrin.h>
#include <intrin0.h>
#pragma intrinsic(_umul128)
#elif (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6))
#define USING_GCC 1
#if defined(__x86_64__)
#define COMPILER_SUPPORTS_16_BYTE_INTEGERS 1
#endif
#endif

#define ASSEMBLE_EXE 0
#define ASSEMBLE_LIB_STATIC 1
#define ASSEMBLE_LIB_DYNAMIC 1

#define CPU_1_BYTE 1
#define CPU_2_BYTE 1
#define CPU_4_BYTE 2
#define CPU_8_BYTE 3

#define CPU_ENDIAN_LITTLE 0

#define NILP nullptr

typedef char CHA;
typedef char16_t CHB;
typedef char32_t CHC;
typedef wchar_t CHN;

typedef int8_t ISA;
typedef uint8_t IUA;
typedef int16_t ISB;
typedef uint16_t IUB;
typedef bool BOL;
typedef int32_t ISC;
typedef uint32_t IUC;
typedef int64_t ISD;
typedef uint64_t IUD;
typedef uint64_t IUE;
typedef int64_t ISE;

typedef IUB FPB;
typedef float FPC;
typedef double FPD;
typedef double FPE;

typedef uintptr_t IUW;
typedef intptr_t ISW;

typedef int ISN;
typedef unsigned int IUN;

typedef short ISM;
typedef unsigned short IUM;

typedef void* PTR;
typedef const void* PTC;

//typedef ISC TMC;  //< A 32-bit seconds since epoch timestamp.
//typedef ISD TMD;  //< A 64-bit seconds since epoch timestamp.

typedef ISW DTW;  //< Word-sized Ascii Data Type.
typedef ISA DTA;  //< 8-bit Ascii Data Type.
typedef ISB DTB;  //< 16-bit Ascii Data Type.
typedef ISC DTC;  //< 32-bit Ascii Data Type.
typedef ISD DTD;  //< 64-bit Ascii Data Type.
//struct IUE { 
//   IUD a,
//       b
//};

// | b15 | b14:b13 | b12:b9 | b8:b7 | b6:b5 | b4:b0 |
// |:---:|:-------:|:------:|:-----:|:-----:|:-----:|
// | CNS |    MD   |   MT   |  SW   |  VT   |  POD  |
enum {
  _RSB = 97, //< 97. A type-value tuple list with 2-byte signed bytes.
  _RSC = 98, //< 98. A type-value tuple list with 4-byte signed bytes.
  _RSD = 99, //< 99. A type-value tuple list with 8-byte signed bytes.
  ATypePODBits    = 5,        //< Bit count for POD types 0-31.
  ATypeVTBit0     = 5,        //< Start bit of the Vector Type bits.
  ATypeSWBit0     = 7,        //< Start bit of the Size Width bits.
  ATypeMTBit0     = 9,        //< Start bit of the Mapped Word Type bits.
  ATypeMDBit0     = 13,       //< Start bit of the MOD bits.
  ATypeCNSBit     = 15,       //< Const Type bit number.
  ATypePODMask    = 0x001f,   //< Starting index of invalid types.
  ATypeMDMask     = 0x6000,   //< Mask for the MD bit.
  ATypeCNSMask    = 0x8000,   //< Mask for the CNS bit.
  ATypePCTotal    = 12,       //< Total of Plain Context Types PCa-PCl.
  ATypePODTotal   = 32,       //< Starting index of invalid types.
  ATypeCodomainTotal = 512,   //< Total types you can map to (codomain).
  ATypeEXSTotal   = 52,       //< Total Extended Standard Types.
  ATypeCTXStart   = 136,      //< First Extended Type Context Type index.
  ATypeCTXTotal   = 72,       //< Total number of Context Types.
  ACTXLengthMax   = 15,       //< Max length of an Extended Type label.
  ACTXFunPrintSTA = 0,        //< ACTX Handler prints to a UTF-8 SPrinter.
  ACTXFunPrintSTB = 1,        //< ACTX Handler prints to a UTF-16 SPrinter.
  ACTXFunPrintSTC = 2,        //< ACTX Handler prints to a UTF-32 SPrinter.
  ACTXFunWrite = 3,
  // The total number of Extended ASCII Types including the Impossible Type.
  ATypeEXTEnd = ATypeEXSTotal + ATypeCTXTotal,
  // Largest ASCII Data Type unmapped Extended Type value.
  ATypeEXTStop  = 15 * ATypePODTotal,
  // Largest ASCII Data Type unmapped Context Type value.
  ATypeCTXMax   = 387,
  SlotBytesMin = 32             //< Minimum size of a slot in bytes.
};

namespace _ {
// ASCII C0 Control codes.
enum {
  _NUL = 0,    //< ASCII C0 NUL 0
  _SOH,        //< ASCII C0 NUL 1
  _STX,        //< ASCII C0 STX 2
  _ETX,        //< ASCII C0 ETX 3
  _EOT,        //< ASCII C0 EOT 4
  _ENQ,        //< ASCII C0 ENQ 5
  _ACK,        //< ASCII C0 ACK 6
  _BEL,        //< ASCII C0 BEL 7
  _BS,         //< ASCII C0 BS 8
  _TAB,        //< ASCII C0 TAB 9
  _LF,         //< ASCII C0 LF 10
  _VT,         //< ASCII C0 VT 11
  _FF,         //< ASCII C0 FF 12
  _CR,         //< ASCII C0 CR 13
  _SO,         //< ASCII C0 SO 14
  _SI,         //< ASCII C0 IS 15
  _DLE,        //< ASCII C0 DLE 16
  _DC1,        //< ASCII C0 DC1 17
  _DC2,        //< ASCII C0 DC2 18
  _DC3,        //< ASCII C0 DC3 19
  _DC4,        //< ASCII C0 DC4 20
  _NAK,        //< ASCII C0 NAK 21
  _SYN,        //< ASCII C0 SYN 22
  _ETB,        //< ASCII C0 ETB 23
  _CAN,        //< ASCII C0 CAN 24
  _EM,         //< ASCII C0 EM 25
  _SUB,        //< ASCII C0 SUB 26
  _ESC,        //< ASCII C0 ESC 27
  _FS,         //< ASCII C0 FS 28
  _GS,         //< ASCII C0 GS 29
  _RS,         //< ASCII C0 RS 30
  _US,         //< ASCII C0 US 31
  _DEL = 127,  //< ASCII C0 DEL 127
};

/* A list of the bit masks for the ASCII data types bit pattern.
| b15:b14 |  b13:b9  | b8:b7 | b6:b5 | b4:b0 |
|:-------:|:--------:|:-----:|:-----:|:-----:|
|   MB    | Map type |  SW   |  VHT  |  POD  | */
enum {
  DTVHT      = 0x0060, //< Mask for b6:b5.
  DTASW      = 0x0080, //< Mask for b7.
  DTBSW      = 0x0180, //< Mask for b8:b7.
  DTBMT      = 0x3E00, //< Mask for b13:b9.
  DTBMB      = 0xC000, //< Mask for b15:b14.
  DTASWShift = 7,      //< Bits to shift to .
  DTBSWShift = 7,      //< Bits to shift b8:b7 into LSb.
  DTBMTShift = 13,     //< Bits to shift b8:b7 into b13:b9 into LSb.
  DTBMBShift = 14,     //< Bits to shift b8:b7 into b15:b14 into LSb.
};

/* List of the 32 ASCII POD Data Types.
@link ./Spec/Data/ReadMe.md */
enum {
  NIL = 0,   //< 00. Nil/void.
  _NIL = 0,  //< 00. Nil/void.
  _IUA,      //< 01. 1-byte unsigned integer.
  _ISA,      //< 02. 1-byte signed integer.
  _CHA,      //< 03. 1-byte character.
  _FPB,      //< 04. 2-byte floating-point number.
  _IUB,      //< 05. 2-byte unsigned integer.
  _ISB,      //< 06. 2-byte signed integer.
  _CHB,      //< 07. 2-byte character.
  _FPC,      //< 08. 4-byte floating-point number.
  _IUC,      //< 09. 4-byte unsigned integer.
  _ISC,      //< 10. 4-byte signed integer.
  _CHC,      //< 11. 4-byte character.
  _FPD,      //< 15. 8-byte floating-point number.
  _IUD,      //< 13. 8-byte unsigned integer.
  _ISD,      //< 14. 8-byte signed integer.
  _TMD,      //< 15. 8-byte timestamp with ISC second and IUC sub-second tick.
  _FPE,      //< 16. 16-byte floating-point number.
  _IUE,      //< 17. 16-byte unsigned integer.
  _ISE,      //< 18. 16-byte signed integer.
  _TME,      //< 19. 16-byte Linear ID Universally Unique Identifier.
  _PCa,      //< 20. Plain Contextual Type a.
  _PCb,      //< 21. Plain Contextual Type b.
  _PCc,      //< 22. Plain Contextual Type c.
  _PCd,      //< 23. Plain Contextual Type d.
  _PCe,      //< 24. Plain Contextual Type e.
  _PCf,      //< 25. Plain Contextual Type f.
  _PCg,      //< 26. Plain Contextual Type g.
  _PCh,      //< 27. Plain Contextual Type h.
  _PCi,      //< 28. Plain Contextual Type i.
  _PCj,      //< 29. Plain Contextual Type j.
  _PCk,      //< 30. Plain Contextual Type k.
  _PCl,      //< 31. Plain Contextual Type l.
};

// Extended ASCII Types Row 1
enum {
  _VSB = 36,  //< 
  _VUB,       //< 
  _VSC,       //< 
  _VUC,       //< 
  _VSD,       //< 
  _VUD,       //< 
  _BSQ,       //< 
  _OBJ,       //< 
  _VSI,       //< 
  _VUI,       //< 
  _LS0 = 48,
  _LS1 = 49,
  _LS2 = 50
};

// Byte Types
enum {
  BT1 = 32,       //< 32 : 1-byte wide type.
  BT2 = BT1 + 32, //< 64 : 2-byte wide type.
  BT3 = BT2 + 32, //< 96 : 4-byte wide type.
  BT4 = BT3 + 32, //< 128: 8-byte wide type.
  BT5 = BT4 + 32, //< 160: 16-byte wide type.
  BT6 = BT5 + 32, //< 192: 32-byte wide type.
  BT7 = BT6 + 32, //< 224: 64-byte wide type.
  BT8 = BT7 + 32, //< 256: 128-byte wide type.
  BT9 = BT8 + 32, //< 288: 256-byte wide type.
  BTa = BT9 + 32, //< 320: 512-byte wide type.
  BTb = BTa + 32, //< 352: 1024-byte wide type.
  BTc = BTb + 32, //< 384: 2048-byte wide type.
  BTd = BTc + 32, //< 416: 4096-byte wide type.
  BTe = BTd + 32, //< 448: 8192-byte wide type.
  BTf = BTe + 32, //< 480: 16,384-byte wide type.
};

enum {
  _ISN = sizeof(ISN) == 1 ? _ISA
       : sizeof(ISN) == 2 ? _ISB
       : sizeof(ISN) == 4 ? _ISC
       : _ISD,
  _IUW = sizeof(IUW) == 1 ? _IUA
       : sizeof(IUW) == 2 ? _IUB
       : sizeof(IUW) == 4 ? _IUC
       : _IUD,
  _ISW = sizeof(ISW) == 1 ? _ISA
       : sizeof(ISW) == 2 ? _ISB
       : sizeof(ISW) == 4 ? _ISC
       : _ISD,
};

enum AEXTTypes {
  _INV = 32,   //< 32. Invalid NIL type and ASCII POD Type total.
  _BOB =  1 * ATypePODTotal,   //< 
  _PTA =  8 * ATypePODTotal,
  _PTB =  9 * ATypePODTotal,
  _PTC = 10 * ATypePODTotal,
  _PTD = 11 * ATypePODTotal,
};
enum AEXTPTypes {
  EXT_INV = 1,    //< Invalid type
  EXT_BOB,        //< 2-byte boolean type.
  EXT_BOC,        //< 4-byte boolean type.
  EXT_DTA,        //< 1-byte data type.
  EXT_DTB,        //< 2-byte data type.
  EXT_DTC,        //< 4-byte data type.
  EXT_DTD,        //< 8-byte data type.
  EXT_PTA,
  EXT_PTB,
  EXT_PTC,
  EXT_PTD,
  EXT_IXA,
  EXT_IXB,
  EXT_IXC,
  EXT_IXD,
  EXT_ERA,
  EXT_ERB,
  EXT_ERC,
  EXT_ERD,
  EXT_EOA,
  EXT_EOB,
  EXT_EOC,
  EXT_EOD,
  EXT_HXa,
  EXT_HXb,
  EXT_HXc,
  EXT_HXd,
  EXT_HXe,
  EXT_HXf,
  EXT_HXg,
  EXT_HXh,
  EXT_STG,
  EXT_STA,
  EXT_STB,
  EXT_STC,
  EXT_OBA,
  EXT_OBB,
  EXT_OBC,
  EXT_OBD,
  EXT_BSA,
  EXT_BSB,
  EXT_BSC,
  EXT_BSD,
  EXT_QUN,
  EXT_LS0,
  EXT_LS1,
  EXT_LS2,
  EXT_TB0,
  EXT_TB1,
  EXT_TB2,
  EXT_TB3,
  EXT_DI0,
  EXT_DI1,
  EXT_DI2,
  EXT_DI3,
  EXT_DI4,
  EXT_DI5,
  EXT_BO0,
  EXT_BO1,
  EXT_BO2,
  EXT_BO3,
  EXT_BO4,
  EXT_BO5,
  EXT_BO6,
  EXT_BO7,
  EXT_BO8,
  EXT_IUF,
  EXT_IUG,
  EXT_IUH,
  EXT_IUI,
  EXT_IUJ,
  EXT_IUK,
  EXT_IUL,
  EXT_IUM
};

enum {
  _STA = 0,   //< 01. Nil-terminated string Type 1 (UTF-8).
  _STB = 1,   //< 02. Nil-terminated string Type 2 (UTF-16).
  _STC = 2,   //< 03. Nil-terminated string Type 3 (UTF-32).
  _WLD = 26,  //< 26. A pointer.
  _VAL,       //< 27. A 2-word value.
  _TVT,       //< 28. A Type-Value tuple.
  _BGV,       //< 29. A 2-word value.
  _TBT,       //< 30. A Type-BigVal tuple.
  _TST,       //< 31. A Type-String tuple.
  _CH = 0,    //< Base type for CHA, CHB, and CHC.
  _FP = 0,    //< Base type for FPB, FPC, FPD, and FPE.
  _IU = 0,    //< Base type for IUA, IUB, IUC, IUD, and IUE.
  _IS = 0,    //< Base type for ISA, ISB, ISD, ISD, and ISE.
  _PTR = sizeof(void*) == 2 ? _PTB
       : sizeof(void*) == 4 ? _PTC : _PTD,
  BOLAlignMask = sizeof(BOL) - 1, //< Pointer alignment mask for BOL.
  _BOL = sizeof(BOL) == 2 ? EXT_BOB : EXT_BOC, //< System BOL Extended Type.
};

enum {
  _MDU = 0,               //< Modifier Unmodified Type.
  _MDP = 1,               //< Modifier Pointer Type.
  _MDI = 2,               //< Modifier Crabs Index Type.
  _MDC = 3,               //< Modifier User Type.
  _CNS = 1 << 15,         //< 128. Constant.
  _CNS_MDP = _CNS | (_MDP << ATypeMDBit0), //< 128. Constant Pointer.
  _CNS_MDI = _CNS | (_MDI << ATypeMDBit0), //< 128. Constant Crabs Pointer Index.
  _CNS_MDE = _CNS | (_MDC << ATypeMDBit0), //< 128. Constant Pointer to a Context Type.
  _CNS_PTR = _PTR | _CNS,   //< Constant pointer type.
  _CNS_STA = _CNS | _STA,   //< 133. Constant UTF-8 string.
  _CNS_STB = _CNS | _STB,   //< 134. Constant UTF-16 string.
  _CNS_STC = _CNS | _STC,   //< 135. Constant UTF-32 string.
};

enum {
  ATypeStringLengthMax = 15,  //< Max length of an Exended Custom or Plain Type.
  _PCaBit0 = 0,               //< Bit 0 of the 8-byte PC Remap Word.
  _PCbBit0 = 5,               //< Bit 5 of the 8-byte PC Remap Word.
  _PCcBit0 = 10,              //< Bit 10 of the 8-byte PC Remap Word.
  _PCdBit0 = 15,              //< Bit 15 of the 8-byte PC Remap Word.
  _PCeBit0 = 20,              //< Bit 20 of the 8-byte PC Remap Word.
  _PCfBit0 = 25,              //< Bit 25 of the 8-byte PC Remap Word.
  _PCgBit0 = 30,              //< Bit 30 of the 8-byte PC Remap Word.
  _PChBit0 = 35,              //< Bit 35 of the 8-byte PC Remap Word.
  _PCiBit0 = 40,              //< Bit 40 of the 8-byte PC Remap Word.
  _PCjBit0 = 45,              //< Bit 45 of the 8-byte PC Remap Word.
  _PCkBit0 = 50,              //< Bit 50 of the 8-byte PC Remap Word.
  _PClBit0 = 55,              //< Bit 55 of the 8-byte PC Remap Word.
};

enum {
  _SWA = 0,   //< 0. Class or POD type.
  _SWB = 1,   //< 1. size_width of bytes is 16-bits wide.
  _SWC = 2,   //< 2. size_width of bytes is 32-bits wide.
  _SWD = 3,   //< 3. size_width of bytes is 64-bits wide.
  _SWE = 4,   //< 4. Psudo size_width of bytes is 128-bits wide.
};

enum {
  _POD = 0,                       //< A POD type.
  _ARY = 1,                       //< Array of POD types.
  _SCK = 2,                       //< Vector of POD types.
  _MTX = 3,                       //< Matrix of POD types.
  VTPODBits = _POD << ATypeVTBit0,  //< Mask for the Vector Type POD bits. #Junk
  VTARYBits = _ARY << ATypeVTBit0,  //< Mask for the Vector Type Array bits.
  VTSCKBits = _SCK << ATypeVTBit0,  //< Mask for the Vector Type Stack bits.
  VTMTXBits = _MTX << ATypeVTBit0,  //< Mask for the Vector Type Matrix bits.
  ATypeSWAMask   = 0,                  //< Mask for the SWA bits. #Junk
  ATypeSWBMask   = 1  << ATypeSWBit0,  //< Mask for the SWB bits.
  ATypeSWCMask   = 2  << ATypeSWBit0,  //< Mask for the SWC bits.
  ATypeSWDMask   = 3  << ATypeSWBit0,  //< Mask for the SWD bits.
  ATypeVTMask    = 3  << ATypeVTBit0,  //< Mask for the VT bits.
  ATypeSWMask    = ATypeSWDMask,       //< Mask for the SW bits.
  ARAMask   = 0  << ATypeMDBit0 | VTARYBits,  //<  8-bit Array types. #Junk
  ARBMask   = 1  << ATypeMDBit0 | VTARYBits,  //< 16-bit Array types.
  ARCMask   = 2  << ATypeMDBit0 | VTARYBits,  //< 32-bit Array types.
  ARDMask   = 3  << ATypeMDBit0 | VTARYBits,  //< 64-bit Array types.
  _LST = 48,                      //< ASCII List type.
  _ARA_CHA  = ARAMask | _CHA,     //< 8-bit Loom of UTF-8 strings.
  _ARA_CHB  = ARAMask | _CHB,     //< 8-bit Loom of UTF-16 strings.
  _ARA_CHC  = ARAMask | _CHC,     //< 8-bit Loom of UTF-32 strings.
  _ARB_CHA  = ARBMask | _CHA,     //< 16-bit Loom of UTF-8 strings.
  _ARB_CHB  = ARBMask | _CHB,     //< 16-bit Loom of UTF-16 strings.
  _ARB_CHC  = ARBMask | _CHC,     //< 16-bit Loom of UTF-32 strings.
  _ARC_CHA  = ARCMask | _CHA,     //< 32-bit Loom of UTF-8 strings.
  _ARC_CHB  = ARCMask | _CHB,     //< 32-bit Loom of UTF-16 strings.
  _ARC_CHC  = ARCMask | _CHC,     //< 32-bit Loom of UTF-32 strings.
  _ARD_CHA  = ARDMask | _CHA,     //< 64-bit Loom of UTF-8 strings.
  _ARD_CHB  = ARDMask | _CHB,     //< 64-bit Loom of UTF-16 strings.
  _ARD_CHC  = ARDMask | _CHC,     //< 64-bit Loom of UTF-32 strings.
};
// Default Loom type.
#if USING_LOM
enum {
  _LOM = USING_LOM,
};
#else
enum {
  _LOM = _ARC_CHA,
};
#endif

enum {
  ACPUBytes = sizeof(void*),
  ACPUBits  = ACPUBytes * 8,
  // Mask to align to CPU word boundry.
  ACPUBytesLog2 = (ACPUBytes == 2) ? 1
                : (ACPUBytes == 4) ? 2
                : (ACPUBytes == 8) ? 3
                : 0,
  //AWordMask = ALUSize - 1,
  ACPUMask      = sizeof(void*) == 1 ? 0
                : sizeof(void*) == 2 ? 1
                : sizeof(void*) == 4 ? 3 : 7,
  ACPUAlignB    = 3,
  ACPUAlignC    = sizeof(void*) == 2 ? 1 : 3,
  ACPUAlignD    = sizeof(void*) == 2 ? 1
                : sizeof(void*) == 4 ? 3
                : sizeof(void*) == 8 ? 7 : 0,
  ACPUAlignE    = ACPUAlignD,
  NaNInt        = sizeof(ISC) == 4 ? static_cast<ISC>(0xFFFFFFFF)
                : sizeof(ISC) == 2 ? static_cast<ISC>(0xFFFF)
                : 0,
  Exit    = -1,       //< Flag to exit the Room.
  Success =  0,       //< Universal successful return value.
  PSH     = -1,       //< Flag to push an item on the top of a stack.
  PCK     = -2,       //< Flag to insert an item on the top of a stack.
  ERR     = PSH - 1,  //< Flag for unspecified error and the SCK op count.
  ANY     = -2,       //< Flag to add an item anywhere in a collection.
};

typedef ISW ERC; //< An error code.

// Enum list of Chinese Room Abstract Stack errors.
enum ASCIIError {
  ErrorNil = 0,                 //< Error 00: Nil error.
  ErrorInvalid = 1,             //< Error 01: Invalid error.
  ErrorInvalidBoofer,           //< Error 02: Invalid boofer.
  ErrorInvalidBounds,           //< Error 03: Invalid bounds.
  ErrorInvalidDoor,             //< Error 04: Invalid door.
  ErrorInvalidEnquery,          //< Error 05: Invalid enquery.
  ErrorInvalidHeader,           //< Error 06: Invalid header.
  ErrorInvalidHash,             //< Error 07: Invalid hash.
  ErrorInvalidIndex,            //< Error 08: Invalid index.

  ErrorInvalidInput,            //< Error 09: Invalid input.
  ErrorInvalidOp,               //< Error 10: Invalid op.
  ErrorInvalidOperand,          //< Error 11: Invalid operand.
  ErrorInvalidRoom,             //< Error 12: Invalid Room.
  ErrorInvalidType,             //< Error 13: Invalid type.
  ErrorInvalidUTF8,             //< Error 14: Invalid UTF-8.
  ErrorInvalidUTF16,            //< Error 15: Invalid UTF-16.

  ErrorArrayUnderflow,          //< Error 16: Array underflow.
  ErrorBooferUnderflow,         //< Error 17: Boofer underflow.
  ErrorKeysBooferUnderflow,     //< Error 18: Keys boofer underflow.
  ErrorParamUnderflow,          //< Error 19: Parameter underflow.
  ErrorStackUnderflow,          //< Error 20: Stack underflow.
  ErrorTextUnderflow,           //< Error 21: Text underflow.
  ErrorVarintUnderflow,         //< Error 22: Varint underflow.
  ErrorYourMomUnderflow,        //< Error 23: Your mom underflow.

  ErrorArrayOverflow,           //< Error 24: Array overflow.
  ErrorBooferOverflow,          //< Error 25: Boofer overflow.
  ErrorKeysBooferOverflow,      //< Error 26: Keys boofer overflow.
  ErrorParamOverflow,           //< Error 27: Parameter overflow.
  ErrorStackOverflow,           //< Error 28: Stack overflow.
  ErrorTextOverflow,            //< Error 29: Text overflow.
  ErrorVarintOverflow,          //< Error 30: Varint overflow.
  ErrorYourMomOverflow,         //< Error 31: Your mom overflow.

  ErrorParamPointer,                //< Error 32: Param is nil.
  ErrorParamIsErrorCode,        //< Error 33: Param is error code.
  ErrorParamErrorenous,         //< Error 35: Param erroneous.
  ErrorParamInvalid,            //< Error 34: Param is invalid.
  ErrorReadOnly,                //< Error 36: Read only.
  ErrorWriteOnly,               //< Error 37: Write only.
  ErrorUnauthorized,            //< Error 38: Unauthorized.
  ErrorUnallowed,               //< Error 39: Unallowed.

  ErrorUnavailable,             //< Error 40: Unavailable.
  ErrorUnavailableKey,          //< Error 41: Unavailable key.
  ErrorImplementation,          //< Error 42: Implementation.

  // Total count of Crabs errors.
  ASCIIErrorCount = ErrorImplementation,
};

enum {
  CrabsGetType = 0,             //< Code to return the ASCII Data Type.
};


/* Function that remaps a Standard Data Type to an Extended Plain or Extended
Custom Type or prints it to a SPrinter or writes it to a boofer.
Control Bits:
I have no clue what we're going to do with the control bits right now but we
have a word, we only need 16-bits, so why not reserve the entire word?
@param  begin The first byte in the CHR boofer.
@param  end   The CHR after the last char in the boofer.
@param  type  A 16-bit ASCII Type in the LSB and control bits in the MSb.
@param  value A pointer to a value to print.
@return If start is nil the remapped Extended Plain Type.
        If start and stop are not nil a pointer to the CHR after the nil term
        char upon succes. */
//typedef DTW (*ACTXHandler)(void* begin, void* end, DTW type, IUW value,
//                           IUW vmsb);
}  //< namespace _
