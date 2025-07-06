// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef SCRIPT2_BSEQ_DECL
#define SCRIPT2_BSEQ_DECL
#include "AType.h"
#if SEAM >= SCRIPT2_CRABS
namespace _ {

/*< Returns the requested parameter number_. */
LIB_MEMBER ISC BSeqParamNumber(const ISN* bsq, ISN param_number);

}  //< namespace _

#endif
#endif
