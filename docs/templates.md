# Template

<!-- IMPORTANT: Keep the line above as the first line. -->
<!-- This file is a static page and included in the ./CMakeLists.txt file. -->

Together with QDMI we provide a template that is meant to kick-start the implementation of a new
device. The following sections describe how to use and setup the template.

\tableofcontents

## Creating new Project {#template-create}

The template is contained in the `template/` directory. However, this is the wrong place to start a
new implementation of a device. Instead, perform the following CMake command. Keep in mind to
replace the prefix and the path as desired. To comply with the style standard of the code in QDMI,
choose a prefix with uppercase letters.

```sh
cmake -DCONFIGURE_TEMPLATE=ON \     # activate template creation
    -DTEMPLATE_PREFIX="PREFIX" \    # set your prefix here
    -DTEMPLATE_PATH="path/to/dir" \ # set the path to your project
    -S . -B build
```

If this option is not given it will be placed in `PREFIX_qdmi_device` relative to the parent
directory where QDMI was cloned in. After this step you can directly start implementing your device
in C++. If you want to implement in C, see also the next section. See \ref examples.md examples for
concrete implementation examples.

## Configuring the Template {#template-configure}

The default template is setup with the specified prefix and as a C++ project. You can easily switch
the project to a purely C project by setting the option `CXX_DEVICE` to `OFF`.

For stability, we recommend to fix the commit hash of QDMI that you use during your implementation.
To this end, change the line 18 in `cmake/ExternalDependecies.cmake` as follows where you replace
the commit hash with the commit hash you want to use for your implementation:

```diff
-   set(QDMI_REV "develop"
+   set(QDMI_REV "123456789"
```

When you want to change the prefix after creation of the template, you need to change the prefix in
a couple of places. We want to give you some hints where you have to change it but depending on your
personal project setup they might be different or there might be more than the listed once. All
paths are given relative to the root of the template project directory.

- `CMakeLists.txt`, line 12
- `src/CMakeLists.txt`: the target `prefix_qdmi` and `prefix_qdmi.cpp`
- Rename `src/prefix_qdmi.cpp` accordingly
- `src/prefix_qdmi.cpp`: adopt the includes and the prefix of each function
- Rename `test/test_prefix_qdmi.cpp` accordingly
- `test/test_prefix_qdmi.cpp`: adopt the includes and the prefix of each function

## Working with the Template {#template-working}

The template is structured into three directories and the top-level `CMakeLists.txt`. The top-level
`CMakeLists.txt` contains settings for the entire project. Some additional CMake code that imports
required dependencies is outsourced into `cmake/`.

The most important directory for your implementation is `src/` and the `.cpp` file located in that
directory. Here you find stubs for all functions that have to be implemented by a device. For every
function the `return QDMI_NOT_IMPLEMENTED;` should be replaced by a proper implementation of the
function. In particular, there should not be any computation path at the end anymore that returns
`QDMI_NOT_IMPLEMENTED`, instead some other error code should be returned in an erroneous state.

The implementation in the `src/` directory is complemented with a testing framework in `test/`. The
`.cpp` source file already contains some examples for test. They are meant to serve as an
inspiration and more tests should be covered to cover everything of your device implementation.

## Building the Template and Running the Tests

Before to start working on the implementation, the CMake project should be configured once to
resolve all references. All of the following commands are meant to be executed from the root
directory of the template. For that run the following CMake command:

\note You need internet connection for this step as QDMI will be fetched in this step.

```sh
cmake -S . -B build
```

This command should add a directory `build/` to your project where all the build files are stored.
The configure step above only needs to be performed once. After that, when you want to build your
implementation, run the following command:

```sh
cmake --build build
```

If you only want to build a specific target, you can append, e.g., `--target prefix_device_test` to
the command above. This will build the tests. There is another target `prefix_qdmi` to build only
the implementation not the tests.

To run the tests perform the following command:

```sh
ctest --test-dir build
```

For more details on the development process, also check out the \ref guide.md "Development Guide".
