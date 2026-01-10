# [SCRIPT Specification](../../)

## [ASCII Data Specification](../)

### [Map Types](./)

#### Stack

```C++
template <typename ISZ = ISN>
struct TStack {
  ISZ total,    //< Size of the Array in elements.
      count;    //< Element count.
};
```

##### Array Memory Layout

```AsciiArt
    +---------------+
    |    Buffer     |
    |---------------|
    | C-Style Array |
 ^  |---------------|
 |  |    Header     |
0xN +---------------+
```

## Requirements

[1] ./

**[<< Previous Section: Array](Array.md) | [Next Section: Matrix >>](Matrix.md)**
