// Copyright AStarship <https://astarship.net>.

//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// The below macros can be override in the _Config.h file.

#ifndef SEAM
#define SEAM SCRIPT2_RELEASE
#endif

#if SCRIPT2_MAX_PARAMS < 0
#error MAX_ERRORS must be greater than 0
#else
enum {
  CrabsParamsMax = 420    //< Max items in a BSQ in a Crabs expression.
};
#endif

#ifndef SCRIPT2_MAX_WALLS
#define SCRIPT2_MAX_WALLS 65535
#endif
#ifndef SCRIPT2_MAX_ERRORS
#define SCRIPT2_MAX_ERRORS 65535
#endif
#ifndef SCRIPT2_MAX_PARAMS
#define SCRIPT2_MAX_PARAMS 65535
#endif
#ifndef SCRIPT2_COM_TIMEOUT_TICKS
#define SCRIPT2_COM_TIMEOUT_TICKS 65535
#else
#if SCRIPT2_COM_TIMEOUT_TICKS < 0
#error MAX_ERRORS must be greater than 0!
#endif
#endif
#ifndef SCRIPT2_MAX_ADDRESS_LENGTH
#define SCRIPT2_MAX_ADDRESS_LENGTH 65535
#endif
#ifndef SCRIPT2_OP_MAX_NAME_LENGTH
#define SCRIPT2_OP_MAX_NAME_LENGTH 65535
#endif
#ifndef SCRIPT2_OP_MAX_DECRABSION_LENGTH
#define SCRIPT2_OP_MAX_DECRABSION_LENGTH 65535
#endif
#ifndef SCRIPT2_TEXT_LENGTH
#define SCRIPT2_TEXT_LENGTH 65535
#endif
#ifndef SCRIPT2_BOOFER_SIZE_RX
#define SCRIPT2_BOOFER_SIZE_RX 65535
#endif
#ifndef SCRIPT2_BOOFER_SIZE_TX
#define SCRIPT2_BOOFER_SIZE_TX 65535
#endif
#ifndef SCRIPT2_WINDOW_SIZE_MIN
#define SCRIPT2_WINDOW_SIZE_MIN 512
#endif
#ifndef SCRIPT2_CPU_CACHE_LINE_SIZE
#define SCRIPT2_CPU_CACHE_LINE_SIZE 64
#endif
#ifndef SCRIPT2_BOOFER_COUNT_DEFAULT
#define SCRIPT2_BOOFER_COUNT_DEFAULT 1024
#else
#if SCRIPT2_BOOFER_COUNT_DEFAULT < 1
#define SCRIPT2_BOOFER_COUNT_DEFAULT 512
#endif
#endif
#ifndef SCRIPT2_STACK_COUNT_MAX_DEFAULT
#define SCRIPT2_STACK_COUNT_MAX_DEFAULT 32
#endif
#ifndef SCRIPT2_FLOOR_SIZE
#define SCRIPT2_FLOOR_SIZE 1024
#endif
#ifndef SCRIPT2_STACK_COUNT_MAX_DEFAULT
#define SCRIPT2_STACK_COUNT_MAX_DEFAULT 16
#endif
#ifndef SCRIPT2_OBJ_SIZE_DEFAULT
#define SCRIPT2_OBJ_SIZE_DEFAULT 256
#endif
#ifndef SCRIPT2_TOKEN_COUNT
#define SCRIPT2_TOKEN_COUNT 32
#endif
#ifndef SCRIPT2_STRING_COUNT_DEFAULT
#define SCRIPT2_STRING_COUNT_DEFAULT 28
#endif
#ifndef SCRIPT2_CIN_boofer_SIZE
#define SCRIPT2_CIN_boofer_SIZE 81
#endif
#ifndef SCRIPT2_UNICODE_VERSION_MAJOR
#define SCRIPT2_UNICODE_VERSION_MAJOR 12
#endif
#ifndef SCRIPT2_UNICODE_VERSION_MINOR
#define SCRIPT2_UNICODE_VERSION_MINOR 1
#endif
#ifndef SCRIPT2_UNICODE_ASSIGNED_CODE_POINTS
#define SCRIPT2_UNICODE_ASSIGNED_CODE_POINTS 277576
#endif
#ifndef SCRIPT2_CONSOLE_WIDTH
#define SCRIPT2_CONSOLE_WIDTH 80
#endif
#ifndef SCRIPT2_DTA_WIDTH
#define SCRIPT2_DTA_WIDTH 0
#endif
#ifndef CLOCK_EPOCH_YEAR  
#define CLOCK_EPOCH_YEAR 1970
#endif
#ifndef SLOT_SIZE_MIN
#define SLOT_SIZE_MIN SCRIPT2_CPU_CACHE_LINE_SIZE
#endif

#ifndef SCRIPT2_ACTX_HANDLER_INIT
#define SCRIPT2_ACTX_HANDLER_INIT ACTXHandlerDefault
#endif

// End overridable `_Config.h` parameters.
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#ifdef ASSEMBLE_LIBRARY
#ifdef LIB_EXPORT == YES_0
#define LIB_MEMBER __declspec(dllexport)
#else
#define LIB_MEMBER __declspec(dllimport)
#endif
#else
#define LIB_MEMBER 
#endif

#if SCRIPT2_PLATFORM == OS_WINDOWS
#define APP_EXIT_SUCCESS 0
#define APP_EXIT_FAILURE 1
#else
#define APP_EXIT_SUCCESS 0
#define APP_EXIT_FAILURE 1
#endif

#ifdef __GNUC__
#if __GNUC__ >= 5
#define HAS_128_BIT_INT
typedef int128_t ISE;
typedef uint128_t IUE;
#endif
#endif

#if SEAM < SCRIPT2_COUT
#undef USING_STB
#undef USING_STC
#define USING_STB NO_0
#define USING_STC NO_0
#endif

#if SEAM < SCRIPT2_FTOS
#undef USING_FPC
#undef USING_FPD
#define USING_FPC NO_0
#define USING_FPD NO_0
#endif

#if USING_FP == 4
typedef FPC FPW;
#elif USING_FP == 8
typedef FPD FPW;
#endif

#if CPU_SIZE == CPU_2_BYTE
#define CPU_IS_LESS_THAN_32_BIT 1
#define CPU_IS_LESS_THAN_64_BIT 1
#define CPU_IS_GREATER_THAN_16_BIT 0
#define CPU_IS_GREATER_THAN_32_BIT 0
#elif CPU_SIZE == CPU_4_BYTE
#define CPU_IS_LESS_THAN_32_BIT 0
#define CPU_IS_LESS_THAN_64_BIT 1
#define CPU_IS_GREATER_THAN_16_BIT 1
#define CPU_IS_GREATER_THAN_32_BIT 0
#elif CPU_SIZE == CPU_8_BYTE
#define CPU_IS_LESS_THAN_32_BIT 0
#define CPU_IS_LESS_THAN_64_BIT 0
#define CPU_IS_GREATER_THAN_16_BIT 1
#define CPU_IS_GREATER_THAN_32_BIT 1
#endif

#if USING_STR == STRING_TYPE_A
typedef CHB CHR;
typedef CHB* STR;
#elif USING_STR == STRING_TYPE_B
typedef CHB CHR;
typedef CHB* STR;
#else
typedef CHC CHR;
typedef CHC* STR;
#endif

#if DEFAULT_INT_SIZE == ATYPE_8BIT || DEFAULT_INT_SIZE == ATYPE_16BIT
typedef ISB ISR;
typedef IUB IUR;
typedef ISA ISQ;
typedef IUA IUQ;
#elif DEFAULT_INT_SIZE == ATYPE_32BIT
typedef ISC ISR;
typedef IUC IUR;
typedef ISB ISQ;
typedef IUB IUQ;
#elif DEFAULT_INT_SIZE == ATYPE_64BIT
typedef ISD ISR;
typedef IUD IUR;
typedef ISC ISQ;
typedef IUC IUQ;
#endif

namespace _ {
// Default character type.
#if USING_STR == STRING_TYPE_A
enum {
  // Default String type is UTF-8.
  STR_ = (_ARY << (ATypePODBits - 1)) | _CHA,
};
#elif USING_STR == STRING_TYPE_B
enum {
  // Default String type is UTF-8.
  STR_ = (_ARY << (TypePODBitCount - 1)) | _CHB,
};
#elif USING_STR == STRING_TYPE_C
enum {
  // Default String type is UTF-8.
  STR_ = (_ARY << (TypePODBitCount - 1)) | _CHC,
};
#else
#error Invalid string type.
#endif
enum {
  // Address type, which is the same as the default string type for the system.
  _ADR = STR_,
  _STR = 1,                       //< ASCII, UTF-8, UTF-16, or UTF-32 string.
};

//< The Largest char.
#if LARGEST_CHAR == STRING_TYPE_B
#if USING_STB == YES_0
typedef CHB CHL;
#else
#error You must set the LARGEST_CHAR to  STRING_TYPE_A.
#endif
#elif LARGEST_CHAR == STRING_TYPE_C
#if USING_STC == YES_0
typedef CHC CHL;
#else
#error You must set the LARGEST_CHAR to  STRING_TYPE_A or STRING_TYPE_B.
#endif
#else
typedef CHA CHL;
#endif

#if CPU_SIZE == CPU_8_BYTE
typedef ISB ISM;  //< Half of ISN type
typedef IUB UIL;  //< Half of IUN type
typedef ISW ISX;  //< Signed double-word int.
typedef IUW IUX;  //< Unsigned double-word int.
typedef ISW ISV;  //< Signed half-word int.
typedef IUW IUV;  //< Unsigned half-word int.
#if COMPILER_SUPPORTS_16_BYTE_INTEGERS
#define LARGEST_POD_TYPE 16
#else
#define LARGEST_POD_TYPE 8
#endif
#elif CPU_SIZE == CPU_4_BYTE
typedef ISC ISX;  //< Signed double-word int.
typedef IUC IUX;  //< Unsigned double-word int.
typedef ISB ISM;  //< Signed half-word int.
typedef ISB ISV;  //< Signed half-word int.
typedef IUB UIL;  //< Unsigned half-word int.
typedef IUB IUV;  //< Unsigned half-word int.
#define LARGEST_POD_TYPE 8
#elif CPU_SIZE == CPU_2_BYTE
typedef ISB ISO;  //< Signed double-word int.
typedef ISB ISX;  //< Signed double-word int.
typedef IUB IUO;  //< Unsigned double-word int.
typedef IUB IUX;  //< Unsigned double-word int.
typedef ISA ISV;  //< Signed half-word int.
typedef ISA ISM;  //< Signed half-word int.
typedef IUA IUV;  //< Unsigned half-word int.
typedef IUA UIL;  //< Unsigned half-word int.
#else
#define LARGEST_POD_TYPE 4
#endif

#if ETE_STOP > 19 && ETE_STOP < 32
#if CT5_STOP > CT4_STOP
#error CT5 is invalid.
#endif
#define USING_CT5 1
typedef IUE CT5;
enum {
  _CT5 = CT5_STOP
};
#undefine CT5_STOP
#undefine CT5_STOP
#else
enum {
  _ECE = 19
};
#endif

#if ETD_STOP != ETE_STOP
#if CT4_STOP > CT5_STOP
#error CT4 is invalid.
#endif
#define USING_CT4 1
typedef IUD CT4;
enum {
  _CT4 = CT4_STOP
};
#undefine CT4_STOP
#else
enum {
  _ECD = _ECE
};
#endif

#if ETC_STOP != ETD_STOP
#if CT3_STOP > CT4_STOP
#error CT3 is invalid.
#endif
#define USING_CT3 1
typedef IUC CT3;
enum {
  _CT3 = CT3_STOP
};
#undefine CT3_STOP
#else
enum {
  _ECC = _ECD,
  BOLSizeLog2 = (sizeof(BOL) == 2) ? 1
              : (sizeof(BOL) == 4) ? 2
              : (sizeof(BOL) == 8) ? 3
              : 0
};
#endif

#if ECB_STOP != ETC_STOP
#if ECB_STOP > CT3_STOP
#error CT2 is invalid.
#endif
#define USING_CT2 1
typedef IUB CT2;
enum {
  _CT2 = ECB_STOP
};
#undefine ECB_STOP
#else
enum {
  _ECB = _ECC
};
#endif
enum {
  _ECA = 31
};

#define PRIME_LARGEST_IUB 65521
#define PRIME_LARGEST_UI4 4294967291
#define PRIME_LARGEST_UI8 18446744073709551557

#define SIZEOF_ARRAY(type) ((CHA*)(&type + 1) - (CHA*)(&type))

enum {
  CRSlotSizeMin = SLOT_SIZE_MIN,        //< Min size of a Slot.
  AClockEpochInit = CLOCK_EPOCH_YEAR,   //< Timestamp epoch year, default: 1970.
  ACPUCacheLineSize = SCRIPT2_CPU_CACHE_LINE_SIZE,    //< CPU Cache line size.
  CRMaxFloorsCount = SCRIPT2_MAX_WALLS, //< Size of the Room Floor (socket).
  CRErrorTotal = SCRIPT2_MAX_ERRORS, //< Max errors before blowing up.
  CRParamTotal = SCRIPT2_MAX_PARAMS, //< Max number_ of parameters.
  CRTimeoutMicroseconds = SCRIPT2_COM_TIMEOUT_TICKS,  //< Sub-second ticks.
  CRAddressLengthMax =
      SCRIPT2_MAX_ADDRESS_LENGTH,  //< Max address (_ADR) length.
  CROpNameLengthMax = SCRIPT2_OP_MAX_NAME_LENGTH,
  // Max length of a Op description .
  CROpDescriptionLengthMax = SCRIPT2_OP_MAX_DECRABSION_LENGTH,
  // Max length of a Text.
  ACharCount = SCRIPT2_TEXT_LENGTH,

  // Size of the Display Print Slot.
  ASlotBooferSizeRx = SCRIPT2_BOOFER_SIZE_RX,

  // Size of the KeyboardInBoofer.
  ASlotBooferSizeTx = SCRIPT2_BOOFER_SIZE_TX,

  AWindowSizeMin = SCRIPT2_WINDOW_SIZE_MIN,

  ABooferSizeDefault = SCRIPT2_BOOFER_COUNT_DEFAULT,
  AFloorSize = SCRIPT2_FLOOR_SIZE,  //< Size, or initial size, of the Floor.
  AStackTotalDefault = SCRIPT2_STACK_COUNT_MAX_DEFAULT,
  AObjSizeDefault = SCRIPT2_OBJ_SIZE_DEFAULT,

  // Extra reserved memory at the stop of BOut.
  ABOutOverflowSize = 32,

  APrintC0Offset = 176,  //< Value add to values 0-32 when printing.
  ATokenLongest  = 31,   //< Max length of a token plus one.
  AMinStackSize  = 1,    //< Min Crabs stack size.
  ABooferSizeDefaultWords =
      ABooferSizeDefault / sizeof(ISW) + ABooferSizeDefault % sizeof(ISW) ? 1
                                                                          : 0,
  ASTRCount = SCRIPT2_STRING_COUNT_DEFAULT,
  AConsoleWidth = SCRIPT2_CONSOLE_WIDTH,
  CInBooferSize =
      SCRIPT2_CIN_boofer_SIZE,         //< Preallocated CIn boofer char count.
  AKeyEnter = 0,                       //< The keyboard value for enter.
  ATypeLargestPOD = LARGEST_POD_TYPE,  //< The largest POD type.
};


enum {
  SZA     = 0,
  SZB     = 1,
  SZC     = 2,
  SZD     = 3,
  SZE     = 4,
};

}  //< namespace _

#undef MAX_ERRORS
#undef MAX_NUM_PARAMS
#undef MAX_STRING_LENGTH
#undef COM_TIMEOUT_TICKS
#undef SCRIPT2_LOG_SIZE
#undef OPERATION_MAX_NAME_LENGTH
#undef OPERATION_MAX_DECRABSION_LENGTH
#undef SCRIPT2_TEXT_LENGTH
#undef SCRIPT2_BOOFER_SIZE_RX
#undef SCRIPT2_BOOFER_SIZE_TX
#undef SCRIPT2_WINDOW_SIZE_MIN
#undef SCRIPT2_BOOFER_COUNT_DEFAULT
#undef SCRIPT2_STACK_COUNT_MAX_DEFAULT
#undef SCRIPT2_FLOOR_SIZE
#undef SCRIPT2_STACK_COUNT_MAX_DEFAULT
#undef SCRIPT2_OBJ_SIZE_DEFAULT
#undef SCRIPT2_TOKEN_COUNT
#undef SCRIPT2_CPU_CACHE_LINE_SIZE
#undef SCRIPT2_STRING_COUNT_DEFAULT
