# [SCRIPT Specification](../../)

## [ASCII Data Specification](../)

### [Map Types](./)

#### Loom

ASCII Loom (LOM) is an array of UTF-8, UTF-16, or UTF-32 strings without a hash table. Strings lengths in Script are capped at type int, which gives a maximum length of 2^31 array elements; in cases where strings grow beyond this length, which is defined as extremely rare, a 64-bit Loom shall be used and the Loom shall be treated as a single long _::TString<>.

##### Sequence Memory Layout

```AsciiArt
+--------------------------+
|_______ Buffer            |
|_______ ...               |
|_______ String N          |
|_______ ...               |
|_______ String 0          |
+--------------------------+
|_______ total         |
|_______ ...               |
|_______ String offset N   |
|_______ ...               |
|        String offset 1   |
+--------------------------+
|       Loom Header        |
+==========================+ ^ 0xN
```

**[<< Previous Section: Matrix](Matrix.md) | [Next Section: Map >>](Map.md)**

## Requirements

[1] ./

## License

Copyright Kabuki Starship <<https://github.com/KabukiStarship/Script2>>.
