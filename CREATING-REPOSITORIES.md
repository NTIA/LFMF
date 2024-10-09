# Guide to Creating a PropLib Repository from this Template Repository

Sketching a PropLib template repository

**TODO**: Add high-level text on how to use this repository and document. Mention
searchable `TODO-TEMPLATE` text throughout repository.

## Merging Template Updates into Downstream Repositories

When changes are made at the template level, it is possible to merge them into
downstream repositories created from the template using the following steps. This
appears to be only possible from the CLI, and not from GitHub Desktop.

```cmd
# In the downstream repository where you wish to merge the changes:

# Add the template repository as a remote
git remote add proplib-template https://github.com/NTIA/proplib-template

# Update the changes
git fetch --all

# Merge the updated template branch into the current branch
git merge proplib-template/[branch to merge] --allow-unrelated-histories

# Then resolve any merge conflicts and finish the merge commit!
```

## Top-Level `CMakeLists.txt`

Fill in project metadata, including the namespace and name of the library. Here
is a complete example of the populated fields for the Irregular Terrain Model (ITM):

```cmake
set(LIB_NAME "ITM")                   # Name of library/target
set(LIB_NAMESPACE "ITS.Propagation")  # Namespace for the named library
project(
    "${LIB_NAMESPACE}.${LIB_NAME}"
    VERSION 1.0.0
    DESCRIPTION "The ITS Irregular Terrain Model"
    HOMEPAGE_URL "https://ntia.github.io/propagation-library-wiki/models/ITM"
    LANGUAGES "CXX"
)
```

### Notes on Namespaces

All ITS Propagation Library software should exist within the `ITS` namespace.
Further, hierarchical namespaces exist within `ITS` for implementations of ITS
propagation models and ITU-R Recommendations. For example, the full namespace for
the ITU-R P.2108 model implementation is `ITS.ITU.PSeries.P2108` and the full
namespace for the ITS Irregular Terrain Model is `ITS.Propagation.ITM`.

## Top-level `README.md`

Carefully parse through the provided template and add information related to
your project. "TODO-TEMPLATE" comments are provided to help point out important
places where template information must be replaced.

## Other Top-level Files

### `.clang-format`

This file contains the ITS PropLib clang-format configuration, which should be
used to autoformat all committed C++ code.

### `CMakePresets.json`

This file defines various presets for CMake. This includes default release and
debug configurations for both 32- and 64-bit. An additional preset is provided
to build documentation with Doxygen without compiling the code.

### `CONTRIBUTING.md` and `LICENSE.md`

These files, respectively, include contribution guidelines for PropLib and the
NTIA software license. You should not need to modify these unless the basic license
is not correct for your code. Ensure the correct license is used in your repository
before publishing it.

## The `app` Directory

This directory should be deleted if your library does not include an accompanying
command-line driver. If your library does include a command-line driver, you will
need to add the source and header files inside this `app/` directory, update the
`app/CMakeLists.txt` file, and update the `app/README.md` document as follows.

Populate the `app/` directory with your command-line driver's source and header files.
Some boilerplate files are provided to help in writing the driver, but these may
be discarded and replaced if desired.

Modify `app/CMakeLists.txt` so that all of the driver source and header files are
named in the `add_executable()` function arguments. There is no need to add the
source or header files from the library itself, since this will be linked to the
driver at compile time. By default, the driver version number is set to automatically
match the library version (i.e., the one you set in the top-level `CMakeLists.txt`
project metadata). However, you can override this here to get a different version
number for the driver:

```cmake
# In app/CMakeLists.txt
set(DRIVER_VERSION "1.5.0")
```

Next, proceed to develop the command line driver application. A number of `TODO-TEMPLATE`
comments are placed throughout the boilerplate code to assist, but this effort
will be largely unique for each project. Once you're done, be sure to add all your
source and header files to `app/CMakeLists.txt` and then write documentation in `app/README.md`.

## The `docs` Directory

This directory includes various files and a `CMakeLists.txt` which are used to
build the Doxygen documentation static website. All of these should work out-of-the-box,
without modification. However, if you wish to alter the Doxygen configuration for
your project, this can be done in `docs/CMakeLists.txt`. If you find a need to change
something in this configuration, consider whether the change is specific to your
project or if it should be made here in the template and applied across the
Propagation Library.

The included `doxy_mainpage.md` file provides content for the home page of the
Doxygen site. The included file is written such that it is agnostic to the software
being documented, however you may choose to modify this file for your project if
you wish to provide information on the home page which is specific to your project.

## The `extern` Directory

This directory holds external components required by the software. Included in
this template are two Git submodules which link to external dependencies:
[doxygen-awesome-css](https://github.com/jothepro/doxygen-awesome-css) and
[googletest](https://github.com/google/googletest). The `doxygen-awesome-css`
module is used to apply custom styling to the Doxygen-generated C++ documentation.
The `googletest` module is recommended for implementing C++ unit tests.

If your project requires additional external dependencies, it is recommended to
place them here. If it makes sense for your dependency and project, consider adding
external dependencies as Git submodules, to best integrate with the workflow design
of this template repository.

## The `include` Directory

This is the location for the C++ library's header files. You must create
a subdirectory in this location with your project's namespace and name. More specifically,
the subdirectory name should be exactly the same as the project name defined in
the top-level `CMakeLists.txt` file, i.e., `"${LIB_NAMESPACE}.${LIB_NAME}"`. Then,
your library's primary interface header should be named the same as the library.
For instance, the library `ITS.Propagation.ITM` will have a structure like this:

```cmake
# In top-level CMakeLists.txt
set(LIB_NAME "ITM")                   # Name of library/target
set(LIB_NAMESPACE "ITS.Propagation")  # Namespace for the named library
```

```cmd
include/
  ITS.Propagation.ITM/
    ITM.h       # The primary interface header
    Errors.h    # Other headers also reside here
    ...
```

### Cross-Platform "EXPORTED"

In your library's interface header, you should use a cross-platform compatible
macro to export the functions of the shared library. It is recommended to copy
and use this snippet of code:

```cpp
// Define cross-platform EXPORTED
#ifndef DOXYGEN_SHOULD_SKIP
    #ifdef _WIN32
        #define EXPORTED extern "C" __declspec(dllexport)
    #else
        #define EXPORTED extern "C"
    #endif
#endif
```

Example usage of this macro would be as follows.

```cpp
EXPORTED int ModelEntryPoint(double someParam, double anotherParam, ...);
```

### Include Guards

It is recommended to use the following preprocessor directive at the beginning of
every header file in your project to prevent them from being included multiple
times during compilation.

```cpp
#pragma once
```

## The `src` Directory

This directory contains the primary source code for the C++ library. The template
includes a `CMakeLists.txt` file in this directory, which you must modify before
being able to compile your project. In this file, you must add the names of all source
files to the `add_library()` arguments. Here is an example project source folder:

```cmd
include/
  ITS.Propagation.SomeModel/
    SomeModel.h
    OtherHeader.h
src/
  CMakeLists.txt
  SomeModel.cpp
  OtherSourceFile.cpp
  AnotherFile.cpp
```

and the corresponding correctly-populated `add_library()` call in `src/CMakeLists.txt`:

```cmake
add_library(
    ${LIB_NAME} SHARED
    "SomeModel.cpp"
    "OtherSourceFile.cpp"
    "AnotherFile.cpp"
    "${PROJECT_HEADERS}/${LIB_NAME}.h"  # Resolves to the SomeModel.h header location!
    "${PROJECT_HEADERS}/OtherHeader.h"
)
```

Note the use of CMake project metadata variables which you set in the top-level
`CMakeLists.txt`. This provides a shortcut `${PROJECT_HEADERS}` for the subdirectory
you created in the `include/` directory. Note that when new source or header files
are added to the project, you must revist and update this file accordingly.

The rest of the `src/CMakeLists.txt` file likely does not require modification, but
feel free to review the other settings applied therein and modify them based on
the needs of your project.

### Documenting Your Code

The Doxygen configuration used by PropLib projects requires that all source code
be documented using Doxygen comments. The recommended style is Javadoc style, and
an example of documented macros, structs, and functions are provided for reference
here. These example include some embedded $\LaTeX$ formatting, which you may consider
using if you wish to tie variables in your code to mathematical variables in supporting
texts. This can also be used to include nicely-formatted equations in your function
documentation.

```cpp
constexpr double a_0__meter = 6370e3;  /**< The actual earth radius, documented inline */

/*******************************************************************************
 * @f$ Z_0 @f$, the speed of light in vacuum multiplied by the vacuum
 * permeability.
 *
 * This block comment includes a brief definition of the constant as well as
 * this longer description. You can use LaTeX and Markdown formatting in both!
 ******************************************************************************/
constexpr double Z_0__ohm = 376.730313667;

/** Valid RF polarizations for use of this model */
enum class Polarization {
    NOT_SET = -1,   /**< Invalid initialization value */
    HORIZONTAL = 0, /**< Horizontal polarization */
    VERTICAL = 1    /**< Vertical polarization */
};

/*******************************************************************************
 * Compute the free space basic transmission loss equation.
 *
 * @param[in] d__meter  Path distance, in meters
 * @param[in] f__mhz    Frequency, in MHz
 * @return              Free space basic transmission loss, in dB
 ******************************************************************************/
double FreeSpaceLoss(const double d__meter, const double f__mhz) {
    return 20.0 * (log10(f__mhz) + log10(d__meter)) - 27.5522168;
}
```

## The `tests` Directory

This directory is used to hold unit test source and header files, along with any
data files required by the test suite. It is recommended to use GoogleTest to write
C++ unit tests and test fixtures. It is also recommended to put test data in a
subdirectory `tests/data`. A final recommendation is to create a single test file
for each source file in your project. An example of what this all might look like
is shown below.

```cmd
src/
  CMakeLists.txt
  SomeSource.cpp
  AnotherSource.cpp
tests/
  data/
    DataForTesting.csv
  CMakeLists.txt
  TestSomeSource.cpp  # Contains tests and fixtures related to SomeSource.cpp
  TestAnotherSource.cpp
  TestUtils.cpp  # Contains, e.g., utility functions used by multiple unit tests
  TestUtils.h    # Contains, e.g., macros/includes/structs used by multiple tests
```

```cmake
# In tests/CMakeLists.txt
add_executable(
    ${TEST_NAME}      # Template sets this to "Test${LIB_NAME}"
    "TestSomeSource.cpp"
    "TestAnotherSource.cpp"
    "TestUtils.cpp"
    "TestUtils.h"
    # Note: no need to include the library source files here!
)
```

## The `wrap` Directory

This directory is meant to contain multi-language wrapper software for the C++
library. The boilerplate configuration supports adding Python, MATLAB, and C#/.NET
wrappers in this directory as follows:

```cmd
wrap/
   dotnet/
   matlab/
   python/
   CMakeLists.txt
```

The provided boilerplate `CMakeLists.txt` should not need to be modified unless
adding different wrappers than these three. This simple `CMakeLists.txt` file looks
for, and runs if found, `CMakeLists.txt` files in the wrapper submodule directories.
These are primarily used to copy the compiled C++ library into the location expected
by the wrapper modules, but can be used for other purposes as well. Additional
configuration related to looking for wrappers is found in the top-level
`CMakeLists.txt` file.
