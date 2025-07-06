// Copyright AStarship <https://astarship.net>.
#pragma once
#ifndef SCRIPT2_MATRIX_HPP
#define SCRIPT2_MATRIX_HPP 1
#include <_Config.h>
#if SEAM >= 1 //SCRIPT2_MATRIX
#include "Stack.hpp"
#define MTX_A typename T = ISW, typename ISZ = ISN
#define MTX_P T, ISZ
#define MTX TMatrix<T, ISZ>
namespace _ {

/* @ingroup AsciiMatrix
Please see the ASCII Data Specificaiton for DRY documentation.
@link ./Spec/Data/vector_types/matrix.md
*/

/* A multi-dimensional array of homogeneous types with a Stack of dimensions.
Please see the ASCII Data Specificaiton for DRY documentation.
@link ./Spec/Data/vector_types/matrix.md

***Memory Layout***

@code
    +-----------------+
    |  C-Style Array  |
    |-----------------|
    | Dimension Stack |
 ^  |-----------------|
 |  |     Header      |
0xN +-----------------+
@endcode
*/
template<MTX_A>
struct TMatrix {
  ISZ bytes,      //< Size in bytes.
      elems;      //< Total number of matrix elements.
  TStack<SCK_P> dimensions; //< Stack of dimensions.
};

/* Max number of elements that can fit in the given ISZ. */
template<typename T = ISW, typename ISZ = ISN>
constexpr ISZ TMatrixElementTotal() {
  return (TSignedMax<ISZ>() - sizeof(TStack<SCK_P>)) / sizeof(T);
}

/* Calculates the size of the Dimensions Stack with the TMatrix header. */
template<typename I = ISN>
inline I TMatrixHeaderSize(I dimensions_total) {
  return sizeof(TMatrix<I>) + dimensions_total * sizeof(I);
}

// Checks if the 
template<typename T = ISW, typename ISZ = ISN>
inline ISZ TMatrixArraySizeMax(ISZ dimensions_total) {
  return ~ISW(0) - TMatrixHeaderSize<ISZ>(dimensions_total);
}

/* Prints the TMatrix to the UTF. */
template<typename Printer, typename T = ISW, typename ISZ = ISN>
Printer& TMatrixPrint(Printer& o, TMatrix<ISZ>* matrix) {
  A_ASSERT(matrix);
  ISZ size = matrix->bytes, 
      dimension_size  = matrix->dimensions.total,
      dimension_count = matrix->dimensions.count;

  o << "\n\nArray: size:" << size << " dimensions:{" << dimension_count;

  ISZ *dimensions = TStackBegin<ISZ, ISZ>(&matrix->dimensions),
      *dimensions_end = dimensions + dimension_count - 1;
  ISZ element_count = *dimensions++;

  while (dimensions < dimensions_end) {
    ISZ dimension = *dimensions++;
    element_count *= dimension;
    if (dimensions == dimensions_end)
      o << dimension << '\n';
    else
      o << dimension << ", ";
  }
  o << '}';

  return o;
}

/* Returns the required size of the given array. */
template<typename T = ISW, typename ISZ = ISN>
ISZ TMatrixElementCount(const ISZ* dimensions) {
  D_ASSERT(dimensions);
  ISZ dimension_count = *dimensions++, 
      element_count   = *dimensions++;
  while (--dimension_count > 0) {
    ISZ current_dimension = *dimensions++;
    if (current_dimension < 1) return -1;
    element_count *= current_dimension;
  }
  if (element_count > TMatrixArraySizeMax<T, ISZ>()) return -1;
  return element_count(T);
}

/* Returns the size in bytes of the given matrix dimensions.
@return -1 if the dimension_count or dimensions are < 0, >=0 othersize. */
template<typename T = ISW, typename ISZ = ISN>
ISZ TMatrixSize(const ISZ* dimensions) {
  D_ASSERT(dimensions);
  ISZ dimension_count = *dimensions++;
  D_ASSERT(dimension_count >= 0);
  if (dimension_count <= 0) return -1;
  ISZ element_count = *dimensions++;
  while (--dimension_count > 0) {
    ISZ dimension = *dimensions++;
    if (dimension <= 0) return -1;
    element_count *= dimension;
  }
  if (element_count > TMatrixArraySizeMax<T, ISZ>()) return -1;
  return sizeof(TStack<SCK_P>) + element_count * sizeof(T);
}

/* Returns the required size of the given array.
@return -1 if the dimension_count or dimensions are < 0, >=0 othersize. */
template<typename T = ISW, typename ISZ = ISN>
ISZ TMatrixSize(const ISZ* dimensions, const ISZ* delta) {
  D_ASSERT(dimensions);
  ISZ dimension_count = *dimensions++;
  if (dimension_count != *delta++) return -1;
  D_ASSERT(dimension_count >= 0);
  if (dimension_count <= 0) return 0;
  ISZ element_count = *dimensions++ + *delta++;
  while (--dimension_count > 0) {
    ISZ dimension = *dimensions++ + *delta++;
    if (dimension <= 0) return -1;
    element_count *= dimension;
  }
  if (element_count > TMatrixArraySizeMax<T, ISZ>()) return -1;
  return sizeof(TStack<SCK_P>) + element_count * sizeof(T);
}

/* Returns the required size of the given array. */
template<typename T = ISW, typename ISZ = ISN>
ISZ TMatrixSize(const TMatrix<ISZ>* matrix) {
  D_ASSERT(matrix);
  return ISZ(sizeof(TMatrix<ISZ>)) + matrix->bytes * sizeof(T) + 
         matrix->dimensions->total * sizeof(ISZ);
}

template<typename T, typename ISZ>
inline ISZ TMatrixDimensionTotal(ISZ total) {
  total += sizeof(TStack<SCK_P>) >> CBitCount<ISZ>();
  return TAlignUpArray<ISZ>(total);
}

template<typename T, typename ISZ, ISZ AlignementMask = sizeof(T) - 1>
ISZ TMatrixSize(ISZ dimension_total, ISZ element_count) {
  ISZ bytes = TMatrixHeaderSize<ISZ>(dimension_total) +
                   sizeof(T) * element_count;
  return AlignUp(bytes, AlignementMask);
}

/* Initializes an stack of n elements of the given type.
@param socket An stack of bytes large enough to fit the stack. */
template<typename T = ISW, typename ISZ = ISN>
TMatrix<ISZ>* TMatrixInit(const ISZ* dimensions) {
  A_ASSERT(dimensions);
  ISZ dimension_count = *dimensions;
  if (dimension_count < 0) return NILP;
  ISZ size = (ISZ)sizeof(TStack<SCK_P>) + dimension_count * sizeof(T);
  IUW* socket = new IUW[size >> ALUSizeLog2];
  TStack<SCK_P>* stack = TPtr<TStack<SCK_P>>(socket);
  stack->size_array = 0;
  stack->size_stack = size;
  stack->total = dimension_count;
  stack->count = 0;
  return stack;
}

/* Gets the address of the packed array.
@param obj ASCII Array data structure.
@return Pointer to the first element in the array. */
template<typename T, typename ISZ = ISN>
inline T* TMatrixStart(TMatrix<ISZ>* obj) {
  return TPtr<T>(TStackBegin<ISZ, ISZ>(&obj->dimensions) + obj->bytes);
}

/* Creates a immutable array of dimensions. */
template<typename ISZ, const ISZ... N>
inline const ISZ* TDim() {
  static const ISZ Count = (ISZ)sizeof...(N), kList[sizeof...(N)] = {N...};
  return &Count;
}

/* Creates a immutable array of ISB dimensions. */
template<const ISB... N>
inline const ISB* TDimB() {
  static const ISB Count = (ISB)sizeof...(N), kList[sizeof...(N)] = {N...};
  return &Count;
}

/* Creates a immutable array of ISC dimensions. */
template<const ISC... N>
inline const ISC* TDimC() {
  static const ISC Count = (ISC)sizeof...(N), kList[sizeof...(N)] = {N...};
  return &Count;
}

/* Creates a static array of ISD dimensions. */
template<const ISD... N>
inline const ISD* TDimD() {
  static const ISD Count = (ISD)sizeof...(N), kList[sizeof...(N)] = {N...};
  return &Count;
}

template<typename ISZ>
inline TMatrix<ISZ>* TMatrixPtr(IUW* origin) {
  return TPtr<TMatrix<ISZ>>(origin);
}

template<typename ISZ>
inline TMatrix<ISZ>* TMatrixPtr(Autoject& ajt) {
  return TMatrix<ISZ>(ajt.origin);
}

template<typename ISZ = ISN>
inline void TMatrixWriteDims(TMatrix<ISZ>* matrix, const ISZ* dims, 
                             ISZ dim_count) {
  ISZ* cursor = &matrix->dimensions->count;
  *cursor++ = dim_count;
  while (dim_count > 0) *cursor++ = *dims++;
}

template<typename T = ISW, typename ISZ = ISN>
inline TMatrix<ISZ>* TMatrixClone(T* start_a, ISZ dim_count_a, const ISZ* dim_a,
                                  T* start_b, ISZ dim_count_b, const ISZ* dim_b) {
  
}

template<typename T = ISW, typename ISZ = ISN>
inline TMatrix<ISZ>* TMatrixCloneDelta(Autoject& ajt, 
  const ISZ* dimensions_delta) {
  auto matrix = TMatrixPtr<ISZ>(ajt);
  TMatrix<ISZ>* matrix = TMatrixPtr<ISZ>(ajt.origin);
  ISZ* a_dimensions = &matrix->dimensions.count;
  ISZ dimension_count = *a_dimensions;
  if (!dimensions_delta || dimension_count == 0) {
    ISZ bytes = TMatrixSize<T, ISZ>(matrix);
    if (bytes < 0) return NILP;
    IUW* origin_new = ajt.ram(NILP, bytes);
    if (!origin_new) return NILP;
    IUW* origin = ajt.origin;
    ISZ bytes = TMatrixSize<T, ISZ>(&matrix->dimensions.count);
    ArrayCopy(origin_new, TPtr<CHA>(origin_new) + bytes, 
              origin, TPtr<CHA>(origin) + bytes);
    return TPtr<TMatrix<ISZ>>(origin_new);
  }
  ISZ dimensions_delta_count = *dimensions_delta++;
  if (dimension_count != dimensions_delta_count) return -1;
  if (dimension_count == 1) {
    return NILP;
  }
  ISZ bytes = TMatrixSize<T, ISZ>(dimensions_delta);
  if (bytes < 0) return NILP;
  IUW* origin_new = ajt.ram(NILP, bytes);
  const ISZ* b_dimensions = 0,
           * a_cursor = a_dimensions,
           * b_cursor = dimensions_delta_count;
  a_dimensions += dimension_count;
  dimensions_delta += dimension_count;
  T* ary = TMatrixStart<T, ISZ>(matrix);
  ISZ dimensions_new[dimension_count];
  ISZ* dimensions_new_ptr = dimensions_new;
  ISZ dimensions_counter = dimension_count;
  ISZ dimension_last;
  while (dimensions_counter-- > 0) {
    dimension_last = *++a_cursor + *++b_cursor;
    *dimensions_new_ptr++ = dimension_last;
  }
  while (a_cursor > a_dimensions)
  return TMatrixPtr<ISZ>(origin_new);
}

template<typename T = ISW, typename ISZ = ISN>
inline TMatrix<ISZ>* TMatrixResize(Autoject& ajt, const ISZ* dimensions_delta) {
  auto matrix = TMatrixCloneDelta<ISZ>(ajt, dimensions_delta);
  if (!matrix) return matrix;
  ajt.origin = TPtr<IUW>(matrix);
  return matrix;
}

template<typename T = ISW, typename ISZ = ISN>
inline IUW* TMatrixCopy(TMatrix<ISZ>* destination, TMatrix<ISZ>* source) {
  ISZ size_destination = TMatrixSize<T, ISZ>(destination),
      size_source      = TMatrixSize<T, ISZ>(source);
  if (size_destination < size_source) return NILP;
  /* I'm not sure if I even want to try to copy the dimensions and array blocks
  seprataly because in practice the dimensions stack size will never be very 
  much.
  ArrayCopy(destination, TStackTop<T, ISZ>(destination->dimensions), 
            source     , TStackTop<T, ISZ>(source->dimensions));
  ArrayCopy(TMatrixStart<T, ISZ>(destination), 
            TPtr<CHA>(destination) + SizeDestination, 
            TMatrixStart<T, ISZ>(source), 
            TPtr<CHA>(source) + SizeSource); */
  ArrayCopy(destination, TPtr<CHA>(destination) + size_destination, 
            source, TPtr<CHA>(source) + size_source);
  return destination;
}

/* A multi-dimensional array Ascii Object. */
template<typename T = ISW, typename ISZ = ISN, typename BOF = Nil>
class AMatrix {
  AArray<ISZ> obj_;  //< The Auto-array.

 public:
  /* Constructs an empty Matrix with 4 reserved dimensions and 64 elements. */
  AMatrix() : obj_(TMatrixSize<T, ISZ>(4, 64)) {}

  /* Initializes an array of n elements of the given type.
  @param max_elements The max number_ of elements in the array socket.
  AMatrix(ISZ x, const T* elements = NILP) : obj_(TMatrixNew<T, ISZ>(x)) {
    D_ASSERT(x >= 0);
  } */

  /* Initializes an array of n elements of the given type.
  @param max_elements The max number_ of elements in the array socket. */
  AMatrix(ISZ x, ISZ y, const T* elements = NILP)
      : obj_(TMatrixSize<T, ISZ>(2, x * y)) {
    D_ASSERT(x >= 0 && y >= 0);
  }

  /* Initializes an array of n elements of the given type.
  @param max_elements The max number_ of elements in the array socket. */
  AMatrix(ISZ x, ISZ y, ISZ z, const T* elements = NILP)
      : obj_(TMatrixSize<T, ISZ>(3, x * y * z)) {
    D_ASSERT(x >= 0 && y >= 0 && z >= 0);
  }

  /* Initializes an array of n elements of the given type.
  @param max_elements The max number_ of elements in the array socket. */
  AMatrix(ISZ w, ISZ x, ISZ y, ISZ z, const T* elements = NILP)
      : obj_(TMatrixSize<T, ISZ>(4, w * x * y * z)) {}

  /* Initializes an array of n elements of the given type.
  @param max_elements The max number_ of elements in the array socket. */
  AMatrix(const AMatrix& other) : obj_(other.Obj()) {}

  /* Destructs nothing. */
  ~AMatrix() { 
    Delete(AJT());
  }

  /* Clones the other object; up-sizing the socket only if required. */
  inline TMatrix<ISZ>* Resize(const ISZ* dimension_delta) {
    TMatrixResize<T, ISZ>(AJT(), dimension_delta);
    return this;
  }

  /* Clones the other object; up-sizing the socket only if required. */
  inline TMatrix<ISZ>* Copy(AMatrix<T, ISZ>& other,
                            RAMFactory ram = obj_.AJT().ram) {
    return TMatrixCopy<T, ISZ>(obj_.Obj(), other, ram);
  }

  /* Gets the number_ of dimensions. */
  inline ISZ DimensionCount() { return This().dimensions->count; }

  /* Gets the dimensions array. */
  inline T* Dimension() { return TStackBegin<T, ISZ>(This()->dimensions); }

  /* Gets the underlying array. */
  inline T* Start() { return TMatrixStart<T, ISZ>(This()); }

  /* Returns the Autoject-Array. */
  inline AArray<ISZ>& AJT_ARY() { return obj_; }

  /* Returns the Autoject. */
  inline Autoject& AJT() { return obj_.AJT(); }

  /* Returns the Autoject::origin cased as a TMap<ISZ>. */
  inline TMatrix<ISZ>* This() { return TPtr<TMatrix<ISZ>>(AJT().origin);
  }

  /* Returns the Auto-Array. */
  inline AArray<T, ISZ, BOF>& Array() { return obj_; }

  template<typename Printer = COut>
  inline Printer& PrintTo(Printer& o) {
    return TMatrixPrint<Printer, T, ISZ>(o, This());
  }

  /* Operator= overload. */
  inline AMatrix<T, ISZ>& operator=(AMatrix<T, ISZ>& other) {
    Clone(other);
    return *this;
  }
};

}  //< namespace _
#endif
#endif
