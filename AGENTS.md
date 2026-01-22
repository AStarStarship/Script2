# Agent Rules for Script2

This file contains rules and guidelines for AI agents operating in the Script2 repository.

## 1. Build, Lint, and Test Commands

### Build
- **Compile:** `g++ -g -o Script2 _Seams/_main.cpp`
- **Output Binary:** `Script2` (Windows: `Script2.exe`)

### Test
The project uses a custom seam testing framework located in `_Seams/`. Tests are tree-based. You change the SEAM macro to one of the seams in the `_Seams.h` file

- **Run All Tests:** `./Script2` (Runs the compiled executable)
- **Run Specific Seam:** Tests are organized in a tree structure. To debug a specific area, you may need to modify `_Seams/_main.cpp` or set breakpoints in `Test.hpp` as described in `ReadMe.md`.
- **Debugging:**
  - Breakpoints: `Test.hpp` contains a `TBRK` function intended for breakpoints.
  - Setup: Copy `_Seams` directory to workspace if needed (per `ReadMe.md`).

### Lint / Standards
- **Style Check:** There is no automated linter configured (e.g., clang-format) visible in the root. Adhere strictly to the manual [Style Guide](./_StyleGuide/ReadMe.md).

## 2. Code Style & Conventions

Script2 uses a **divergent fork of the Google C++ Style Guide** known as the **ASCII C++ Style Guide**. You MUST follow these unique conventions.

### General Philosophy
- **ASCII Data Types:** The project uses custom [ASCII Data Types](./_Spec/Data) (e.g., `ISN`, `BOL`, `CHR`, `IUW`, `DTW`) instead of standard C++ types like `int`, `bool`, `char`.
  - **Mapping:**
    - `ISN` -> Signed Integer (likely platform dependent width, often `int` or `long long`)
    - `BOL` -> Boolean
    - `CHR`, `CHA` -> char (ASCII)
    - `IUW` -> Unsigned Integer Word (machine word size)
    - `DTW` -> Data Type Word
- **Minimal Standard Library:** The project aims to replace the C++ std library. Avoid `#include <string>`, `<vector>`, `<iostream>` unless explicitly allowed or wrapping legacy code. Use project-specific containers (`Array`, `List`, `Stack`, `String`) instead.
- **Kabuki Module Format:** Follow the module structure: `.h` (Contains the decl), `.hpp` (Contains all code that uses templates), `.hxx` (contains the impl usually found in .ccp files because we use only one translation unit to compile as fast as possible).

### Naming Conventions
This naming convention is called Chimera case due to the mix of snake_case and PascalCase.,
- **Types:** PascalCase (`MyExcitingClass`, `UrlTable`).
- **Variables:** snake_case (`my_local_variable`, `num_errors`).
- **Class Members:** snake_case with trailing underscore (`table_name_`).
- **Struct Members:** snake_case *without* trailing underscore (`name`, `num_entries`).
- **Constants/Globals:** `c` prefix + CamelCase (`cDaysInAWeek`, `cFoo`).
- **Enums:**
  - Type Name: PascalCase (`UrlTableErrors`).
  - Enumerators: `c` prefix + CamelCase (`cErrorOutOfMemory`) OR Macro_Style (`OUT_OF_MEMORY`).
- **Functions:** PascalCase (`StartRpc()`, `OpenFileOrDie()`).
  - Accessors/Mutators: snake_case allowed (`count()`, `set_count()`).
- **Namespaces:** snake_case, top-level matches project/team. No nested `std`.
- **Macros:** UPPER_CASE_WITH_UNDERSCORES (Macros are mostly used for changing seams/unit tests).

### Formatting
- **Indentation:** 2 spaces (inferred from `AType.h`).
- **Braces:** K&R style / Google style (attached to the line definition).
- **Line Length:** generally 80 chars, but be reasonable.
- **Pointer/Ref:** Attached to type or variable? `AType.h` shows `void* begin` (attached to type).
- **Control Flow:** `if`, `for`, `while`, `switch` have a space between keyword and parenthesis. `else` goes on same line as closing brace.

### File Structure
- **Headers:** `.h` for declarations.
- **Implementation:** `.hpp` or `.hxx` (often included at bottom of `.h` or compiled separately).
- **Guards:** `#ifndef SCRIPT2_SEAM_H` style.
- **Copyright:** Include `// Copyright AStarship <https://astarship.net>.` at the top followed by one blank line.
- **Includes:** Use `""` for local project files, `<>` for system/config files (e.g., `#include <_Config.h>`).

### Error Handling
- **No Exceptions:** The project likely relies on error codes or assertions (`IsError`).
- **Debugging:** Use `TBRK()` for breakpoints. Use `StdOut()` (wrapped) for logging if strictly necessary, but prefer the "Seam" test structure.

### Specific Types (from `AType.h` and `_Spec/Data`)
- `DTW`, `DTB`: Data Type Word/Byte.
- `IUW`, `IUE`, `IUD`: Unsigned Integer Word/128-bit/64-bit.
- `ISW`, `ISE`: Signed Integer Word/128-bit.
- `FPC`, `FPD`, `FPE`: Floating Point types.
- `PTR`: Pointer macros or wrappers may exist.

### Classes
- **Constructors:** Do no work in constructors that can fail. Use `Init()` if needed.
- **Explicit:** Mark single-arg constructors `explicit`.
- **Copy/Move:** Explicitly declare or delete copy/move operations (`= default`, `= delete`) in public section.
- **Structs vs Classes:** Use `struct` only for passive data (public members, no logic). Use `class` for everything else (private data with trailing underscore).
- **Inheritance:** Public inheritance only. Composition preferred.

### Autojects and RAMFactory
- **Autoject:** An "Automatic Object" that manages memory dynamically via a `RAMFactory`. It consists of a pointer (`origin`) and a memory management function (`ram`).
- **RAMFactory:** A function pointer type (`IUW* (*RAMFactory)(IUW* origin, ISW bytes)`) used to allocate, resize, or delete memory.
- **Seam Injection:** The `Autoject` design facilitates dependency injection and testing "seams" by allowing you to swap out the memory factory (`RAMFactory`) or the underlying data buffer (`origin`). This is crucial for isolating components during testing.

## 3. Important Directories
- `_Seams/`: Test suites (Seams).
- `_StyleGuide/`: Definitive source for coding standards.
- `_Config.h`: Project configuration.

## 4. AI Behavior Rules
- **Verify before Implement:** Always read `_StyleGuide` files if unsure about a naming or structural convention.
- **Mimic Context:** The codebase uses heavily customized types. Do NOT introduce standard `int`, `char`, `float` without checking if a project specific type (`ISN`, `CHR`, `FPC`) should be used instead.
- **Seam Tests:** When adding functionality, look for the corresponding "Seam" (test file) in `_Seams/` and add a test case there.
