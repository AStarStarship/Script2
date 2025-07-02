// Copyright Kabuki Starship <kabukistarship.com>.
#include "File.h"
#if SEAM >= SCRIPT2_FILE
#include <sys/stat.h>
#include <sys/types.h>
#ifndef WIN32
#include <unistd.h>
#endif
#ifdef WIN32
#define stat _stat
#endif

namespace _ {
File::File(const CHR* uri) : uri_(uri_) {}

const CHR* File::URI() { return uri_; }

const CHR* File::URISet(const CHR* uri) {
  if (!uri) return uri;

  uri_ = uri;

  return uri;
}

TMS File::LastTimeModified() {
  struct stat result;
  if (stat(uri_, &result) == 0) {
    return result.st_mtime;
  }
  return 0;
}

TMS File::HasBeenModified() {
  TMS last_time_modified = LastTimeModified();
  if (last_time_modified == last_time_modified_) return 0;
  last_time_modified_ = last_time_modified;
  return last_time_modified;
}

BOL File::Exists() { return false; }

BOL File::IsOpen() { return false; }

ISN File::Open() { return 0; }

void File::Close() {}

}  // namespace

::_::File& operator<<(::_::File& o, CHA item) { return o.Print(item); }
::_::File& operator<<(::_::File& o, const CHA* item) { return o.Print(item); }
#if USING_STB == YES_0
::_::File& operator<<(::_::File& o, CHB item) { return o.Print(item); }
::_::File& operator<<(::_::File& o, const CHB* item) { return o.Print(item); }
#endif
#if USING_STC == YES_0
::_::File& operator<<(::_::File& o, CHC item) { return o.Print(item); }
::_::File& operator<<(::_::File& o, const CHC* item) { return o.Print(item); }
#endif
::_::File& operator<<(::_::File& o, ISC item) { return o.Print(item); }
::_::File& operator<<(::_::File& o, IUC item) { return o.Print(item); }
::_::File& operator<<(::_::File& o, ISD item) { return o.Print(item); }
::_::File& operator<<(::_::File& o, IUD item) { return o.Print(item); }
#if USING_FPC == YES_0
::_::File& operator<<(::_::File& o, FPC item) { return o.Print(item); }
#endif
#if USING_FPD == YES_0
::_::File& operator<<(::_::File& o, FPD item) { return o.Print(item); }
#endif
::_::File& operator<<(::_::File& o, ::_::Hexf item) { return o.Print(item); }
::_::File& operator<<(::_::File& o, ::_::Binaryf item) { return o.Print(item); }
::_::File& operator<<(::_::File& o, ::_::Centerf item) { return o.Print(item); }
::_::File& operator<<(::_::File& o, ::_::Rightf item) { return o.Print(item); }
::_::File& operator<<(::_::File& o, ::_::Linef item) { return o.Print(item); }
::_::File& operator<<(::_::File& o, ::_::Headingf item) { return o.Print(item); }
::_::File& operator<<(::_::File& o, ::_::Indentf item) { return o.Print(item); }
::_::File& operator<<(::_::File& o, ::_::Charsf item) { return o.Print(item); }
::_::File& operator<<(::_::File& o, ::_::File item) { return o; }
#endif
