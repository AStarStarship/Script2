// Copyright Kabuki Starship <kabukistarship.com>.
#include "Error.hpp"
#if SEAM >= SCRIPT2_STACK
namespace _ {
const CHA* ASCIIErrorSTA() {
  return TAErrors<CHA>();
}

const CHA* ASCIIErrorSTR(ISA error) {
  error = error < 0 ? -error : error;
  if (error > ASCIIErrorCount) error = ASCIIErrorCount;
  return &TAErrors<CHA>()[error * 32];
}
const CHA* ASCIIErrorSTR(ISB error) {
  return ASCIIErrorSTR(ISA(error));
}
const CHA* ASCIIErrorSTR(ISC error) {
  return ASCIIErrorSTR(ISA(error));
}
const CHA* ASCIIErrorSTR(ISD error) {
  return ASCIIErrorSTR(ISA(error));
}

BOL AIsError(const void* result) {
  return TDelta<IUW>(result) < ASCIIErrorCount;
}

}  //< namespace _
#endif
