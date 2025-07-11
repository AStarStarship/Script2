// Copyright AStarship <https://astarship.net>.
#pragma once
#include <_Config.h>
#ifndef SCRIPT2_STRINGF_DECL
#define SCRIPT2_STRINGF_DECL 1
#include "AType.h"
namespace _ {

// Returns true if the item is printable.
BOL CHIsPrintable(CHA item);
BOL CHIsPrintable(CHB item);
BOL CHIsPrintable(CHC item);

// Returns true if the item is not printable or is whitespace.
BOL CHIsBlank(CHA item);
BOL CHIsBlank(CHB item);
BOL CHIsBlank(CHC item);

/* Gets the header to print for PrintChars(const void*, const void*). */
LIB_MEMBER const CHA* STAPrintCharsHeader();

/* Gets the header to print for PrintChars(const void*, const void*). */
LIB_MEMBER const CHA* STAPrintCharsBorder();

/* Gets the header to print for PrintHex(const void*, const void*). */
LIB_MEMBER const CHA* STAPrintHexHeader();

/* Gets the header to print for PrintHex(const void*, const void*). */
LIB_MEMBER const CHA* STAPrintHexBorder();

/* Converts a IUA into a two-IUA hex representation.
@return Returns -1 if c is not a hex IUA. */
LIB_MEMBER ISC HexToByte(IUB hex);

/* Attempts to scan a UTF-32 CHA from the given UTF-8 string.
@return  Nil upon failure or a pointer to the end of the UTF-8 CHA upon
success. */
LIB_MEMBER const CHA* SScan(const CHA* string, CHC& character);

#if USING_STB == YES_0
/* Prints a UTF-32 character to the string terminated at the stop.
@return  Nil upon failure or a pointer to the nil-term CHT upon success.
@param string    The start of the string.
@param stop      The last CHA in the string boofer.
@warning This algorithm is designed to fail if the socket is not a valid socket
with one or more bytes in it. */
LIB_MEMBER CHB* SPrint(CHB* string, CHB* stop, CHC character);

/* Attempts to scan a UTF-32 CHA from the given UTF-16 string.
@return  Nil upon failure or a pointer to the end of the UTF-8 CHA upon
success. */
LIB_MEMBER const CHB* SScan(const CHB* string, CHC& character);
#endif

#if USING_STC == YES_0
/* Prints a character to the string.
@return  Nil upon failure or a pointer to the nil-term CHT upon success.
@param stop The last character in the string boofer. */
LIB_MEMBER CHA* SPrint(CHA* string, CHA* stop, CHB character);

/* Prints a Unicode character to the given string.
@return  Nil upon failure or a pointer to the nil-term CHT upon success.
@param stop   The last CHT in the socket. */
LIB_MEMBER CHA* SPrint(CHA* string, CHA* stop, CHC character);
#endif

/* Utility class for printing numbers. */
struct LIB_MEMBER Valuef {
  ISW count;        //< Width of the item in bytes or columns.
  ATypeValue value;  //< The type and value.

  /* Constrcts a NIL item. */
  Valuef();

  /* Constructs a Valuef from the given item. */
  Valuef(const void* item, ISW count = 0);
  Valuef(void* item, ISW count = 0);
#if USING_STA == YES_0
  Valuef(CHA item, ISW count = 0);
  Valuef(const CHA* item, ISW count = 0);
#endif
#if USING_STB == YES_0
  Valuef(CHB item, ISW count = 0);
  Valuef(const CHB* item, ISW count = 0);
#endif
#if USING_STC == YES_0
  Valuef(CHC item, ISW count = 0);
  Valuef(const CHC* item, ISW count = 0);
#endif
  Valuef(ISA item, ISW count = 0);
  Valuef(IUA item, ISW count = 0);
  Valuef(ISB item, ISW count = 0);
  Valuef(IUB item, ISW count = 0);
  Valuef(ISC item, ISW count = 0);
  Valuef(IUC item, ISW count = 0);
  Valuef(ISD item, ISW count = 0);
  Valuef(IUD item, ISW count = 0);
#if USING_FPC == YES_0
  Valuef(FPC item, ISW count = 0);
#endif
#if USING_FPD == YES_0
  Valuef(FPD item, ISW count = 0);
#endif

  /* Gets the value.Type(). */
  ISW Type();

  /* Gets the count. */
  ISW Count();

  /* Gets the pointer to either the item.Ptr () or the pointer item stores. */
  void* Value();

  /* Gets the value::word_ as the specified type. */
  void* ToPtr();
  CHA* ToSTA();
  CHB* ToSTB();
  CHC* ToSTC();
  IUW ToWord();
};

/* Utility class for printing a POD type in hex.
@todo: Why is this storing the value as a negative?
*/
struct Hexf {
  Valuef element;  //< Stores the ASCII Type, it's value, and the byte count.

  Hexf(const void* item, ISW size);
  /* Stores the given item to the boofer and stores the size. */
  Hexf(const void* item);
  Hexf(ISA item);
  Hexf(IUA item);
  Hexf(CHA item);
  Hexf(ISB item);
  Hexf(IUB item);
  Hexf(CHB item);
  Hexf(ISC item);
  Hexf(IUC item);
  Hexf(CHC item);
  Hexf(ISD item);
  Hexf(IUD item);
#if USING_FPC == YES_0
  Hexf(FPC item);
#endif
#if USING_FPD == YES_0
  Hexf(FPD item);
#endif
};

/* Utility class for printing a POD type in binary. */
struct LIB_MEMBER Binaryf {
  Valuef element;  //< Stores the ASCII Type, it's value, and the byte count.

  /* Stores the given item to the boofer and store the size. */
  Binaryf(const void* item);
  Binaryf(const void* item, ISW size);
  Binaryf(ISA item);
  Binaryf(IUA item);
  Binaryf(ISB item);
  Binaryf(IUB item);
  Binaryf(ISC item);
  Binaryf(IUC item);
  Binaryf(ISD item);
  Binaryf(IUD item);
#if USING_FPC == YES_0
  Binaryf(FPC item);
#endif
#if USING_FPD == YES_0
  Binaryf(FPD item);
#endif
};

/* Utility class for printing blocks of characters to the console with
operator<<. */
struct LIB_MEMBER Charsf {
  Valuef element;  //< The type, value and CHA, CHB, or CHC count.

  /* Constructs the value from the delta between start and stop. */
  Charsf(const void* start, const void* stop);
  Charsf(const void* start, ISW count);
#if USING_STB == YES_0
  Charsf(const CHB* start, const CHB* stop);
  Charsf(const CHB* start, ISW count);
#endif
#if USING_STC == YES_0
  Charsf(const CHC* start, const CHC* stop);
  Charsf(const CHC* start, ISW count);
#endif
};

/* Utility class for formatting text with operator<<, most commonly right and
center aligned.
@warning Stringf cannot be const because we need to write to it on the stack 
frame in chained operator overloads.
*/
class LIB_MEMBER Stringf {
 public:
  enum {
    // Max length of the boofer in ALU words.
    BooferWordCount = (sizeof(void*) == 2) ? 5
                    : (sizeof(void*) == 4) ? 6 
                    : (sizeof(void*) == 8) ? 5 : 1,
    // Max length of a string in characters.
    LengthMax = BooferWordCount * sizeof(void*) - 1,
  };

 private:
  const void* string_;  // Pointer to a string or the boofer_.
  ISW count_;           //< The character count.
  DTW type_;            //< The ASCII string Type, STA, STB, or STC.
  IUW boofer_[BooferWordCount];  //< String boofer for the token.

 public:
  /* Default constructor sets the count but doesn't write a nil-term char
  to the boofer. */
  Stringf();

  /* Sets the String_ to the given pointer and stores the count. */
  Stringf(const CHA* item);
#if USING_STB == YES_0
  Stringf(const CHB* item);
#endif
#if USING_STC == YES_0
  Stringf(const CHC* item);
#endif

  /* Prints the item to the boofer_, stores the count, and sets the String_ to
  the boofer_. */
  Stringf(CHA item);
  Stringf(CHB item);
  Stringf(CHC item);
  Stringf(ISC item);
  Stringf(IUC item);
  Stringf(ISD item);
  Stringf(IUD item);
#if USING_FPC == YES_0
  Stringf(FPC item);
#endif
#if USING_FPD == YES_0
  Stringf(FPD item);
#endif

  /* Sets the String_ to the given pointer and stores the count. */
  Stringf(const CHA* item, ISW count);
#if USING_STB == YES_0
  Stringf(const CHB* item, ISW count);
#endif
#if USING_STC == YES_0
  Stringf(const CHC* item, ISW count);
#endif

  /* Prints the item to the boofer_, stores the count, and sets the String_ to
  the boofer_. */
  Stringf(CHA item, ISW count);
  Stringf(CHB item, ISW count);
  Stringf(CHC item, ISW count);
  Stringf(ISC item, ISW count);
  Stringf(IUC item, ISW count);
  Stringf(ISD item, ISW count);
  Stringf(IUD item, ISW count);
#if USING_FPC == YES_0
  Stringf(FPC item, ISW count);
#endif
#if USING_FPD == YES_0
  Stringf(FPD item, ISW count);
#endif
  //Stringf(ATypef item, ISW count = AConsoleWidth);
  //Stringf(TypeValue item, ISW count = AConsoleWidth);

  IUW Word();

  /* Gets a void pointer to the value_. */
  void* Value();

  /* Gets the pointer contained in value_[0]. */
  void* Ptr();

  /* Gets the String_. */
  const CHA* STA();
  const CHB* STB();
  const CHC* STC();

  /* Gets the type_. */
  ISW Type();

  /* Gets the count_. */
  ISW Count();

  /* Saves the pointer to the String_. */
  void Print(const CHA* item);
#if USING_STB == YES_0
  void Print(const CHB* item);
#endif
#if USING_STC == YES_0
  void Print(const CHC* item);
#endif

  /* Prints the given item to the boofer_. */
  void Print(CHA item);
#if USING_STB == YES_0
  void Print(CHB item);
#endif
#if USING_STC == YES_0
  void Print(CHC item);
#endif
  void Print(ISC item);
  void Print(IUC item);
  void Print(ISD item);
  void Print(IUD item);
#if USING_FPC == YES_0
  void Print(FPC item);
#endif
#if USING_FPD == YES_0
  void Print(FPD item);
#endif

  /* Prints a timestamp to the boofer_. */
  //void PrintTMC(TMC item);
  //void PrintTME(TMC item, IUC subsecond_tick);
  //void PrintTMD(TMD item);

  //void Print(TypeValue item);

  /* Stores the item to the first word of the boofer and the negative of the
  count. */
  void Hex(CHA item, ISW count = 80);
#if USING_STB == YES_0
  void Hex(CHB item, ISW count = 80);
#endif
#if USING_STC == YES_0
  void Hex(CHC item, ISW count = 80);
#endif
  void Hex(ISA item, ISW count = 80);
  void Hex(IUA item, ISW count = 80);
  void Hex(ISB item, ISW count = 80);
  void Hex(IUB item, ISW count = 80);
  void Hex(ISC item, ISW count = 80);
  void Hex(IUC item, ISW count = 80);
  void Hex(ISD item, ISW count = 80);
  void Hex(IUD item, ISW count = 80);
#if USING_FPC == YES_0
  void Hex(FPC item, ISW count = 80);
#endif
#if USING_FPD == YES_0
  void Hex(FPD item, ISW count = 80);
#endif
};

/* Utility class for printing hex with operator<<. */
struct LIB_MEMBER Centerf {
  Stringf element;  //< Pointer to a pointer to utf.

  /* Does nothing. */
  Centerf();

  /* Prints the item to the value. */
  Centerf(CHA item, ISW count = AConsoleWidth);
  Centerf(const CHA* start, ISW count = AConsoleWidth);
#if USING_STB == YES_0
  Centerf(CHB item, ISW count = AConsoleWidth);
  Centerf(const CHB* item, ISW count = AConsoleWidth);
#endif
#if USING_STC == YES_0
  Centerf(CHC item, ISW count = AConsoleWidth);
  Centerf(const CHC* item, ISW count = AConsoleWidth);
#endif
  Centerf(ISC item, ISW count = AConsoleWidth);

  Centerf(IUC item, ISW count = AConsoleWidth);
  Centerf(ISD item, ISW count = AConsoleWidth);
  Centerf(IUD item, ISW count = AConsoleWidth);

#if USING_FPC == YES_0
  Centerf(FPC item, ISW count = AConsoleWidth);
#endif
#if USING_FPD == YES_0
  Centerf(FPD item, ISW count = AConsoleWidth);
#endif

  /* Stores the item to the first word of the boofer and the negative of the
  count. */
  Centerf& Hex(CHA item, ISW count = 80);
#if USING_STB == YES_0
  Centerf& Hex(CHB item, ISW count = 80);
#endif
#if USING_STC == YES_0
  Centerf& Hex(CHC item, ISW count = 80);
#endif
  Centerf& Hex(ISA item, ISW count = 80);
  Centerf& Hex(IUA item, ISW count = 80);
  Centerf& Hex(ISB item, ISW count = 80);
  Centerf& Hex(IUB item, ISW count = 80);
  Centerf& Hex(ISC item, ISW count = 80);
  Centerf& Hex(IUC item, ISW count = 80);
  Centerf& Hex(ISD item, ISW count = 80);
  Centerf& Hex(IUD item, ISW count = 80);
#if USING_FPC == YES_0
  Centerf& Hex(FPC item, ISW count = 80);
#endif
#if USING_FPD == YES_0
  Centerf& Hex(FPD item, ISW count = 80);
#endif
};

/* Utility class for printing hex with operator<<. */
struct LIB_MEMBER Rightf {
  Stringf element;  //< Pointer to a pointer to utf.

  /* Does nothing. */
  Rightf();

  /* Prints the item to the value. */
  Rightf(CHA item, ISW count = AConsoleWidth);
  Rightf(const CHA* item, ISW count = AConsoleWidth);
#if USING_STB == YES_0
  Rightf(CHB item, ISW count = AConsoleWidth);
  Rightf(const CHB* item, ISW count = AConsoleWidth);
#endif
#if USING_STC == YES_0
  Rightf(CHC item, ISW count = AConsoleWidth);
  Rightf(const CHC* item, ISW count = AConsoleWidth);
#endif
  Rightf(ISC item, ISW count = AConsoleWidth);
  Rightf(IUC item, ISW count = AConsoleWidth);
  Rightf(ISD item, ISW count = AConsoleWidth);
  Rightf(IUD item, ISW count = AConsoleWidth);

#if USING_FPC == YES_0
  Rightf(FPC item, ISW count = AConsoleWidth);
#endif
#if USING_FPD == YES_0
  Rightf(FPD item, ISW count = AConsoleWidth);
#endif

  /* Stores the item to the first word of the boofer and the negative of the
  count. */
  Rightf& Hex(CHA item, ISW count = 80);
#if USING_STB == YES_0
  Rightf& Hex(CHB item, ISW count = 80);
#endif
#if USING_STC == YES_0
  Rightf& Hex(CHC item, ISW count = 80);
#endif
  Rightf& Hex(ISA item, ISW count = 80);
  Rightf& Hex(IUA item, ISW count = 80);
  Rightf& Hex(ISB item, ISW count = 80);
  Rightf& Hex(IUB item, ISW count = 80);
  Rightf& Hex(ISC item, ISW count = 80);
  Rightf& Hex(IUC item, ISW count = 80);
  Rightf& Hex(ISD item, ISW count = 80);
  Rightf& Hex(IUD item, ISW count = 80);
#if USING_FPC == YES_0
  Rightf& Hex(FPC item, ISW count = 80);
#endif
#if USING_FPD == YES_0
  Rightf& Hex(FPD item, ISW count = 80);
#endif
};

/* Utility class for printing a horizontal line with operator<<. */
struct LIB_MEMBER Linef {
  Valuef element;     //< Pointer to a pointer to utf.
  CHA string[5];      //< Used to create a string in Linef(CHA,ISW).

  /* Constructors a horizontal line of the character. */
  Linef(CHA item, ISW count = AConsoleWidth);

  /* Constructors a horizontal line of the given string. */
  Linef(const CHA* start = NILP, ISW count = AConsoleWidth);
};

/* Utility class for printing a Heading with formatting with operator<<. */
struct LIB_MEMBER Headingf {
  Stringf element;
  const CHA *style, *caption2, *caption3;

  /* Saves the parameters to the corresponding data members. */
  Headingf(const CHA* caption);

  /* Saves the parameters to the corresponding data members. */
  Headingf(const CHA* caption, const CHA* caption2);

  /* Saves the parameters to the corresponding data members. */
  Headingf(const CHA* caption, const CHA* caption2,
           const CHA* caption3 = NILP, const CHA* style = NILP,
           ISW count = AConsoleWidth);
};

/* Utility class for indenting text with operator<<. */
struct LIB_MEMBER Indentf {
  ISW indent_count;  //< Number of spaces to indent.

  /* Constructs the value from the delta between start and stop. */
  Indentf(ISW indent_count);
};

/* Utility class for indicating the size or count of an item. */
struct Sizef {
  ISW size;  //< The size of the item.

  Sizef(ISA size);
  Sizef(ISB size);
  Sizef(ISC size);
  Sizef(ISD size);
};

/* Utility class for printing an ASCII type-value one-liner. */
struct LIB_MEMBER ATypef {
  DTW type,   //< The item type.
      count;  //< The number of chars to print.

  ATypef(DTB type, Sizef count = { -1 });
  ATypef(DTC type, Sizef count = { -1 });
  ATypef(DTD type, Sizef count = { -1 });
  //ATypef(DTE type, Sizef count = { -1 });
  ATypef(DTB pod, DTB vt, Sizef count = { -1 });
  ATypef(DTB pod, DTB vt, DTB sw, Sizef count = { -1 });
  ATypef(DTB pod, DTB vt, DTB sw, DTB map, Sizef count = { -1 });
  ATypef(DTB pod, DTB vt, DTB sw, DTB map, DTB mod, Sizef count = { -1 });

  // Center aligns this to the given character count.
  Centerf Center(ISW count);

  // Right aligns this to the given character count.
  Rightf Right(ISW count);
};

/* Utility class for printing an ASCII type-value one-liner. */
struct LIB_MEMBER AValuef {
};

// Utility class for printing an ASCII Error Code.
struct LIB_MEMBER AErrorf {
  ISW error;                //< Error code.
  const CHA* message; //< Error message.

  AErrorf(ISW error, const CHA* message = NILP);
};
}  //< namespace _
#endif
