// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef SCRIPT2_FILE_DECL
#define SCRIPT2_FILE_DECL 1
#include <_Config.h>
#if SEAM >= SCRIPT2_FILE
#include "Uniprinter.hpp"
namespace _ {

#undef  TARGS
#define TARGS
#undef  TPARAMS
#define TPARAMS
/* A file in a filesystem. */
class File {
 public:

  /* Constructs a File from the given URI string. */
  File(const CHR* uri);

  /* Gets the Uniform Resource Identifier. */
  const CHR* URI();
  
  /* Sets the Uniform Resource Identifier. */
  const CHR* URISet(const CHR* uri);

  /* Checks to see if the given file exists. */
  BOL Exists();

  /* Checks to see if the file is closed. */
  BOL IsOpen();

  /* Opens the file. */
  ISN Open();

  /* Closes the file. */
  void Close();

  /* Gets the last time this file was modified. */
  TME LastTimeModified();
  
  /* Checks to see if the file has been modified by comparing the last time it 
  was modified. */
  BOL HasBeenModified();

 private:
  const CHR* uri_;          //< Uniform Resource Identifier.
  TME last_time_modified_;  //< Last time the URL was modified.
};

}  //< namespace _
/* Prints the given item to the File. */
::_::File& operator<<(::_::File& o, CHA item);
::_::File& operator<<(::_::File& o, const CHA* item);

#if USING_STB == YES_0
::_::File& operator<<(::_::File& o, CHB item);
::_::File& operator<<(::_::File& o, const CHB* item);
#endif
#if USING_STC == YES_0
::_::File& operator<<(::_::File& o, CHC item);
::_::File& operator<<(::_::File& o, const CHC* item);
#endif
::_::File& operator<<(::_::File& o, ISC item);
::_::File& operator<<(::_::File& o, IUC item);
::_::File& operator<<(::_::File& o, ISD item);
::_::File& operator<<(::_::File& o, IUD item);
#if USING_FPC == YES_0
::_::File& operator<<(::_::File& o, FPC item);
#endif
#if USING_FPD == YES_0
::_::File& operator<<(::_::File& o, FPD item);
#endif
::_::File& operator<<(::_::File& o, ::_::Hexf item);
::_::File& operator<<(::_::File& o, ::_::Binaryf item);
::_::File& operator<<(::_::File& o, ::_::Centerf item);
::_::File& operator<<(::_::File& o, ::_::Rightf item);
::_::File& operator<<(::_::File& o, ::_::Linef item);
::_::File& operator<<(::_::File& o, ::_::Headingf item);
::_::File& operator<<(::_::File& o, ::_::Indentf item);
::_::File& operator<<(::_::File& o, ::_::Charsf item);
::_::File& operator<<(::_::File& o, ::_::File item);
#endif
#endif
