// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef SCRIPT2_SLOT_DECL
#define SCRIPT2_SLOT_DECL
#include <_Config.h>
#if SEAM >= SCRIPT2_CRABS
namespace _ {

struct BIn;
struct BOut;
struct Op;

/* A Slot in a Door in a Chinese Room to pass messages through.
A Slot is Ring Boofer Socket similar to a TCP port. The operation of the
Slot is similar to the Text class except that it introduces two more
pointers for the (socket) origin and (data) origin of the ring socket and
you may write packed data. */
struct Slot {
  IUA* origin,  //< First byte of the ring socket.
     * start,   //< Start of the data in the ring socket.
     * stop,    //< Stop of the data in the ring socket.
     * end;     //< End of the ring socket.

  /* Initializes the ring socket with the given socket origin and size.
  @param origin Pointer to the beginning of the ring socket.
  @param size  The size of the ring socket in bytes. */
  Slot(IUW* socket, ISW size);

  /* Initializes the slot from the BIn. */
  Slot(BIn* bin);

  /* Initializes the slot from the BIn. */
  Slot(BOut* bout);

  /* Sets the ring socket to the given socket origin and size.
  @param origin Pointer to the beginning of the ring socket.
  @param size  The size of the ring socket in bytes. */
  inline BOL Set(IUW* socket, IUW size) {
    if (!socket) return true;
    IUA* begin = reinterpret_cast<IUA*>(socket);
    origin = origin = stop = begin;
    stop   = begin + size;
    return false;
  }

  /* Checks if this slot contains the given address.
  @return Returns inputed address if this Slot contains the given address
  and nil else wise. */
  void* Contains(void* address);

  /* Clears the socket without zeroing it out. */
  inline void Clear() { origin = stop = origin; }

  /* Zeros out the Slot. */
  void Wipe();

  /* Checks if there is space in the socket.
  @return True if the socket has space. */
  BOL IsWritable();

  /* Checks if there is data in the socket.
  @return True if the socket has data. */
  BOL IsReadable();

  /* Reads the given Operation input parameters from the slot to the args.
  @param slot The slot to read from.
  @param op   The Operation to get the in from.
  @param args The args array of pointers to write to.
  @return Nil upon success and an Error Operation upon failure. */
  const Op* Read(const ISC* params, void** args);

  /* Reads the given Operation input parameters from the slot to the args.
  @param slot The slot to read from.
  @param op   The Operation to get the in from.
  @param args The args array of pointers to write to.
  @return Nil upon success and an Error Operation upon failure. */
  const Op* Read(const Op& op, void** args);

  /* Writes the given Operation output parameters from the slot to the args.
  @param slot The slot to read from.
  @param op   The Operation to get the in from.
  @param args The args array of pointers to write to.
  @return Nil upon success and an Error Operation upon failure. */
  const Op* Write(const ISC* params, void** args);

  /* Writes the given Operation output parameters from the slot to the args.
  @param slot The slot to read from.
  @param op   The Operation to get the in from.
  @param args The args array of pointers to write to.
  @return Nil upon success and an Error Operation upon failure. */
  const Op* Write(const Op& op, void** args);

  /* Writes a single  to the slot socket.
  @param message The  message to send.
  @return Nil upon success and an Error Operation upon failure. */
  const Op* Write(const IUA* message);

  /* Copies the contents of the target slot into the slot. */
  const Op* Write(Slot& target);
};

}  //< namespace _

#endif
#endif
