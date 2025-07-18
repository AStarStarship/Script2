// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef SCRIPT2_MIRROR_DECL
#define SCRIPT2_MIRROR_DECL 1
#include <_Config.h>
#if SEAM >= SCRIPT2_ROOM
#include "BIn.h"
#include "BOut.h"
#include "Op.h"
namespace _ {

/* A Mirror in a Chinese Room.
A Mirror */
struct LIB_MEMBER Mirror {
  ISC size,    //< The size of the socket.
      origin,  //< The starting index of the ring socket data.
      stop,    //< The stopping index of the ring socket data.
      read;    //< The read variable.
};

const Op* MirrorResult(Mirror* mirror, Error error);
const Op* MirrorResult(Mirror* mirror, Error error);

enum {
  cMirrorHeaderSize = 4 * sizeof(ISC)  //< Size of a Mirror Header.
};

static const IUW kMaxMirrorSize = ~((IUW)0);

/* Calculates the used ring socket space.
@param Start The origin of the data.
@param Stop  The stop of the data.
@param Size The size of the socket. */
LIB_MEMBER ISC MirrorLength(CHA* origin, CHA* stop, ISC size);

/* Calculates the space left in the given ring socket.
@param Start The origin of the data.
@param Stop  The stop of the data.
@param Size  The size of the socket. */
LIB_MEMBER ISC MirrorSpace(CHA* origin, CHA* stop, ISC size);

/* Checks if the given slot contains the specified address. */
LIB_MEMBER void* MirrorContains(Mirror* mirror, void* address);

/* Clears the ring socket by writing zeros to it. */
LIB_MEMBER void MirrorWipe(Mirror* mirror);

/* Copies a block from a ring-socket to the given destination. */
// LIB_MEMBER CHA* MirrorWrite (Mirror* mirror, void* source, ISW size);

/* Copies a block from a ring-socket to the given destination. */
// LIB_MEMBER CHA* MirrorRead (Mirror* mirror, void* source, ISW size);

/* Gets the args from the b-sequence. */
LIB_MEMBER const Op* MirrorRead(Mirror* mirror, const ISC* params, void** args);

/* Posts a evaluated result to the b-sequence. */
// LIB_MEMBER const Op* MirrorWrite (Mirror* mirror, const ISC* params,
//                                   void** args);

LIB_MEMBER BOL MirrorIsReadable(Mirror* mirror);

/* Used to return an erroneous result from a B-Input.
@param bin     The source Mirror.
@param error   The error type.
@param header  The B-Sequence Header.
@param offset  The offset to the type in error in the B-Sequence.
@param address The address of the IUA in error.
@return         Returns a Static Error Operation Result. */
LIB_MEMBER const Op* MirrorResult(Mirror* mirror, Error error,
                                  const ISC* header);
/* Used to return an erroneous result from a B-Input.
@param bin     The source Mirror.
@param error   The error type.
@param header  The B-Sequence Header.
@param offset  The offset to the type in error in the B-Sequence.
@param address The address of the IUA in error.
@return         Returns a Static Error Operation Result. */
LIB_MEMBER const Op* MirrorResult(Mirror* mirror, Error error,
                                  const ISC* header);

/* Used to return an erroneous result from a B-Input.
@param bin     The source Mirror.
@param error   The error type.
@param header  The B-Sequence Header.
@param offset  The offset to the type in error in the B-Sequence.
@param address The address of the IUA in error.
@return         Returns a Static Error Operation Result. */
LIB_MEMBER const Op* MirrorResult(Mirror* mirror, Error error,
                                  const ISC* header, IUA offset);

/* Used to return an erroneous result from a B-Input.
@param bin     The source Mirror.
@param error   The error type.
@param header  The B-Sequence Header.
@param offset  The offset to the type in error in the B-Sequence.
@param address The address of the IUA in error.
@return         Returns a Static Error Operation Result. */
// LIB_MEMBER const Op* MirrorResult (Mirror* mirror, Error error,
//                                   const ISC* header,
//                                   ISC offset);

/* Used to return an erroneous result from a B-Input.
@param bin     The source Mirror.
@param error   The error type.
@param header  The B-Sequence Header.
@param offset  The offset to the type in error in the B-Sequence.
@param address The address of the IUA in error.
@return         Returns a Static Error Operation Result. */
LIB_MEMBER const Op* MirrorResult(Mirror* mirror, Error error,
                                  const ISC* header, ISC offset, CHA* address);

/* Used to return an erroneous result from a B-Input.
@param bin     The source Mirror.
@param error   The error type.
@param header  The B-Sequence Header.
@param offset  The offset to the type in error in the B-Sequence.
@param address The address of the IUA in error.
@return         Returns a Static Error Operation Result. */
LIB_MEMBER const Op* MirrorResult(Mirror* mirror, Error error,
                                  const ISC* header, ISC offset, CHA* address);

}  //< namespace _
#endif  //< #if SEAM >= SCRIPT2_DIC
#endif
