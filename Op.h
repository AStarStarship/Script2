// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef SCRIPT2_OP_DECL
#define SCRIPT2_OP_DECL
#include <_Config.h>
#if SEAM >= SCRIPT2_CRABS
namespace _ {

struct BIn;
struct BOut;
struct Op;

// enum {
//    CROpPush          = 0, //< Operation Type 0: Stack push .
//    CROpOperation     = 1, //< Operation Type 1: Abstract Operation.
//    CROpOperationPush = 2, //< Operation Type 2: Operation with stack push.
//};
/* An expression Operation with name key, multiple input params,
result, and optional description of a data set.
@code
static const Op This = { "Key",
    Params<1, 2>::Header, Params<1, 2>::Header,
    "Description", '}', ';', ' ', NILP, "-", NILP };

static const Op OpExample =   { "Key2",
    NumOps (0), FirstOp ('A'),
    "Description", '}', ';', ' ', true, NILP, "-", NILP };
@endcode */
struct LIB_MEMBER Op {
  const CHA* name;          //< Op name.
  const ISC* in,            //< Input _BSQ params or OpFirst.
      * out;                //< Output _BSQ params or OpLast.
  const CHA* description;   //< Op description.
  CHC pop,                  //< Index of the Pop Operation.
      close,                //< Index of the Close Operation.
      default_op;           //< Index of the Default Operation.
  BOL using_numbers;        //< Flag for if tokens may use numbers.
  const CHA* ignore_chars,  //< String of chars to ignore.
           * allowed_chars; //< String of allowed symbols.
  const BOut* evaluation;   //< Evaluated expression Slot.
};

const Op* OpError(ERC error);

}  //< namespace _

#endif
#endif
