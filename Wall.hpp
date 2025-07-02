// Copyright Kabuki Starship <kabukistarship.com>; all rights reserved.
#pragma once
#ifndef SCRIPT2_WALL_INLINE_CODE
#define SCRIPT2_WALL_INLINE_CODE 1
#include <_Config.h>
#if SEAM >= SCRIPT2_DIC
#include "Door.hpp"
#include "Op.hpp"
#include "Array.hpp"
#define WAL_A typename T = ISW, typename ISZ = ISN
#define WAL_P T, ISZ
#define WAL TWall<T, ISZ>
namespace _ {
  
/* A group of Doors that share the same Extended Types.
Only one single wall is required for a Chinese Room, but when more memory is
needed a new Wall may be created and destroyed dynamically.

@code
+--------------+
|  Terminals   |
|      v       |
|vvvvvvvvvvvvvv|
|    Boofer    |
|^^^^^^^^^^^^^^|
|      ^       |
|  TStack of   |
|    Doors     |
|   Offsets    |
|--------------|
|    Header    |
+--------------+
@endcode */
template<typename ISZ = ISM, typename ISY = ISN>
class TWall : public Operand {
 public:
  enum {
    BytesMin = 512,  //< Min functional Wall size.
  };

private:
  IUD         et_map_; //< Extended Type remap word from EPa-EPl to types 0-19.
  SCK doors_;  //< The doors in the room.

  virtual ~TWall() {
    if (is_dynamic_) {
      CHA* socket = TPtr<CHA>(&doors_);
      delete[] socket;
    }
  }

  /* Constructs a wall from the given socket. */
  TWall(ISW bytes = BytesMin) : is_dynamic_(true) {
    bytes = bytes < BytesMin ? (ISC)BytesMin : bytes;
    bytes = TAlignUp<ISD, ISW>(bytes);
    ISW size_words = (bytes >> sizeof(void*)) + 3;
    IUW *socket = new IUW[size_words],
        *aligned_boofer = TPtrUp<IUW>(socket);
    //< Shift 3 to divide by 8. The extra 3 elements are for aligning memory
    //< on 16 and 32-bit systems.
    bytes -= sizeof(IUW) * (aligned_boofer - socket);
    origin = socket;
    doors_ = TPtr<SCK>(aligned_boofer);
    TStackInit(socket, bytes >> sizeof(IUW));
  }

  /* Constructs a wall from the given socket. */
  TWall(IUW* socket, ISW bytes) {
    IUW* aligned_boofer = TPtrUp<IUW>(socket);
    //< Shift 3 to divide by 8. The extra 3 elements are for aligning memory
    //< on 16 and 32-bit systems.
    bytes -= sizeof(IUW) * (aligned_boofer - socket);
    origin = socket;
    doors_ = TPtr<SCK>(aligned_boofer);
    TStackInit(socket, bytes >> sizeof(IUW));
  }

  /* Gets the size of the wall in bytes. */
  ISW GetSizeBytes() {
    return bytes_;
  }
  /* Gets a pointer to the array of pointers to Door(). */
  SCK* Doors() {
    return &doors_;
  }

  /* Gets the Door from the Door at the given index. */
  TDoor<ISZ> GetDoor(ISY index) { return 0; }

  /* Adds a Door to the slot.
  @return Returns nil if the Door is full and a pointer to the Door in the
          socket upon success. */
  ISC OpenDoor(Door * door) { return 0; }

  /* Deletes the Door from the Door at the given index. */
  BOL CloseDoor(ISY index) { return false; }

  /* Prints the given Door to the stream. */
  template<typename Printer>
  Printer& PrintTo(Printer & o) {
    return o;
  }
};

}  //< namespace _
#endif
#endif
