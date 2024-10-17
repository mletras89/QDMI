# Development Guide

<!-- IMPORTANT: Keep the line above as the first line. -->
<!-- This file is a static page and included in the CMakeLists.txt file. -->

## Build Instructions

### Documentation

The documentation can be built with the CMake target `qdmi_docs`. After building this target, with

```sh
cmake -S . -B build
cmake --build build --target qdmi_docs
```

the generated webpage can be inspected by opening the file in `docs/html/index.html` in the CMake
build directory.

## Working on Source Code

<!-- TODO -->

### Format for Comments

For the information to be displayed correctly on the webpage, it is essential that the comments
follow the format required by Doxygen. Below you find some tags, that are commonly used within the
documentation of a function:

- `@brief` For a brief, one-line description of the function
- `@details` For a longer, detailed description of the function. Note: In the current setting, the
  long description is always prepended with the brief description. So there is no need to repeat the
  brief description in the details.
- `@param` To explain the usage of a parameter
- `@return` To explain the return value

## Working on Documentation

### Static Content

The generated webpage contains also four static sites, namely the main page, the support page, the
FAQ page, and this development guide. The respective markdown files that serve as the source for
those sites are contained in `docs/` where `index.md` contains the content of the main page.

### Dynamic Content

In order to include source files to be listed among the menu item `API Reference/Files`, these files
must be marked as documented. This is accomplished by adding a comment like the following to the top
of the file. Right now, this is done for all files in the include directory.

```C
/** @file
 * @brief Include all public headers for the QDMI interface.
 * @details The detailed description of the interface is provided in the @ref
 * interface/control.h and @ref interface/query.h.
 */
```

### Further Links

- For more details see the official documentation of Doxygen that can be found here:
  [https://www.doxygen.nl/manual/docblocks.html](https://www.doxygen.nl/manual/docblocks.html).
- More tags and commands can be found in the list provided here:
  [https://www.doxygen.nl/manual/commands.html#cmd_intro](https://www.doxygen.nl/manual/commands.html#cmd_intro)
