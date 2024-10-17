# Development Guide

<!-- IMPORTANT: Keep the line above as the first line. -->
<!-- This file is a static page and included in the CMakeLists.txt file. -->

Ready to contribute to QDMI? This guide will help you get started.

## Initial Setup

1. Fork the [QDMI](https://github.com/Munich-Quantum-Software-Stack/QDMI) repository on GitHub (see <https://docs.github.com/en/get-started/quickstart/fork-a-repo>).

2. Clone your fork locally

   ```sh
   git clone git@github.com:your_name_here/QDMI.git
   ```
   
3. Change into the project directory

   ```sh
   cd QDMI
   ```
   
4. Create a branch for local development

   ```sh
   git checkout -b name-of-your-bugfix-or-feature
   ```
   
   Now you can make your changes locally.

5. (Optional, **highly recommended**) Install [pre-commit](https://pre-commit.com/) to automatically run a set of checks before each commit. The easiest way to install pre-commit is via [uv](https://docs.astral.sh/uv/).

   ```sh
   uv tool install pre-commit
   pre-commit install
   ```

   \note
   If you do not have `uv` installed, you can install it via
    ```sh
    curl -LsSf https://astral.sh/uv/install.sh | sh
    ```
   on macOS and Linux or
   ```sh
   powershell -c "irm https://astral.sh/uv/install.ps1 | iex"
   ```
   on Windows.

## Working on Source Code

Building the project requires a C compiler supporting _C11_ and a minimum CMake version of _3.19_.
The example backends and the tests require a C++ compiler supporting _C++17_.

### Configure and Build

QDMI uses CMake as its build system.
Building a project using CMake is a two-step process:

First, the project needs to be _configured_ by calling




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

\verbatim

/** @file
 * @brief Include all public headers for the QDMI interface.
 * @details The detailed description of the interface is provided in the 
 * @ref interface/control.h and @ref interface/query.h.
 */

\endverbatim

<div class="tabbed">

- <b class="tab-title">Tab 1</b> This is the content of tab 1
- <b class="tab-title">Tab 2</b> This is the content of tab 2

</div>

### Further Links

- For more details see the official documentation of Doxygen that can be found here:
  [https://www.doxygen.nl/manual/docblocks.html](https://www.doxygen.nl/manual/docblocks.html).
- More tags and commands can be found in the list provided here:
  [https://www.doxygen.nl/manual/commands.html#cmd_intro](https://www.doxygen.nl/manual/commands.html#cmd_intro)
