# Examples

<!-- IMPORTANT: Keep the line above as the first line. -->
<!-- This file is a static page and included in the ./CMakeLists.txt file. -->

This page contains example implementations of backends and other components of the software stack
that use QDMI. Those example implementations can serve as templates. All examples distributed with
QDMI are contained in the `examples/` directory in the repository.

\tableofcontents

## Implementing a Backend {#backend}

Below you find a mock implementation of two QDMI backends: One is implemented in C and the other one
in C++. Keep in mind, that even though the backend can be implemented in C++ it has to provide a C
interface.

### Basic String Properties {#backend-string}

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

### Double and Integer Properties {#backend-double-int}

Following two examples for returning `double` and `int` properties.

<!-- prettier-ignore-start -->
<div class="tabbed">
- <b class="tab-title">C</b>
  \dontinclude backend.c
  \skip QDMI_query_device_property_double_dev
  \until QDMI_query_device_property_int_dev
  \until QDMI_ERROR_INVALID_ARGUMENT
  \until }
- <b class="tab-title">C++</b>
  \dontinclude backend.cpp
  \skip QDMI_query_device_property_double_dev
  \until QDMI_query_device_property_int_dev
  \until QDMI_ERROR_INVALID_ARGUMENT
  \until }
</div>
<!-- prettier-ignore-end -->

### List Properties {#backend-list}

Some properties are returned as a list of the various data type. The following example shows how to
return the list of available gates which are represented as strings, i.e., `char*` in the C
language.

<!-- prettier-ignore-start -->
<div class="tabbed">
- <b class="tab-title">C</b>
  \dontinclude backend.c
  \skip QDMI_query_device_property_string_list_dev
  \until QDMI_ERROR_INVALID_ARGUMENT
  \until }
- <b class="tab-title">C++</b>
  \dontinclude backend.cpp
  \skip QDMI_query_device_property_string_list_dev
  \until QDMI_ERROR_INVALID_ARGUMENT
  \until }
</div>
<!-- prettier-ignore-end -->

Another example is the coupling map which is represented as a list of pairs of integers.

<!-- prettier-ignore-start -->
<div class="tabbed">
- <b class="tab-title">C</b>
  \dontinclude backend.c
  \skip QDMI_query_device_property_int_list_dev
  \until QDMI_ERROR_INVALID_ARGUMENT
  \until }
- <b class="tab-title">C++</b>
  \dontinclude backend.cpp
  \skip QDMI_query_device_property_int_list_dev
  \until QDMI_ERROR_INVALID_ARGUMENT
  \until }
</div>
<!-- prettier-ignore-end -->
