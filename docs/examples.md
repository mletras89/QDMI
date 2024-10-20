# Examples

<!-- IMPORTANT: Keep the line above as the first line. -->
<!-- This file is a static page and included in the ./CMakeLists.txt file. -->

This page contains example implementations of backends and other components of the software stack
that use QDMI. Those example implementations can serve as templates.

\tableofcontents

## Implementing a Backend {#backend}

Every backend has to provide a name, its version, and the implemented QDMI library version through
the query interface. The corresponding properties are

- @ref QDMI_NAME
- @ref QDMI_DEVICE_VERSION
- @ref QDMI_LIBRARY_VERSION

All of those properties are of type `char*` (string). Hence, they are returned by the @ref
QDMI_query_device_property_string function. Below you find the respective implementation in C and
C++.

<!-- prettier-ignore-start -->
<div class="tabbed">
- <b class="tab-title">C</b>
  \dontinclude backend.c
  \skip QDMI_query_device_property_string_dev
  \until QDMI_ERROR_INVALID_ARGUMENT
  \until }
- <b class="tab-title">C++</b>
  \dontinclude backend.cpp
  \skip QDMI_query_device_property_string_dev
  \until QDMI_ERROR_INVALID_ARGUMENT
  \until }
</div>
<!-- prettier-ignore-end -->
