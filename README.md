# NTIA/ITS Propagation Library Template Project #
<!-- TODO-TEMPLATE: Update software name above -->
<!-- TODO-TEMPLATE: README BADGES

- The first badge links to the PropLib Wiki and does not need to be edited
- The second badge automatically displays and links to the most recent GitHub Release.
    - Make sure to update the [gh-releases-badge] and [gh-releases-link] URLs with your repo name
- The third badge is the CMake/CTest GitHub actions status.
    - Update the repository name in [gh-actions-test-badge] and [gh-actions-test-link]
- The fourth badge is the Doxygen github actions status.
    - Update the repository name in [gh-actions-docs-badge]
    - Update the repository name in [gh-pages-docs-link]
- The fifth badge displays open GitHub Issues
    - Update the repository name in [gh-issues-badge]
    - Update the repository name in [gh-issues-link]
- The sixth badge displays and links the Zenodo DOI
    - Get your repository ID from https://api.github.com/repos/NTIA/{repo}
    - Or, if private, follow: https://stackoverflow.com/a/47223479
    - Populate the repository ID in [doi-link] and [doi-badge]
-->
[![NTIA/ITS PropLib][proplib-badge]][proplib-link]
<!-- TODO-TEMPLATE: Add badges. See above for details.
[![GitHub Release][gh-releases-badge]][gh-releases-link]
[![GitHub Actions Unit Test Status][gh-actions-test-badge]][gh-actions-test-link]
[![C++ API Reference][gh-actions-docs-badge]][gh-pages-docs-link]
[![GitHub Issues][gh-issues-badge]][gh-issues-link]
[![DOI][doi-badge]][doi-link]
-->
[proplib-badge]: https://img.shields.io/badge/PropLib-badge?label=%F0%9F%87%BA%F0%9F%87%B8%20NTIA%2FITS&labelColor=162E51&color=D63E04
[proplib-link]: https://ntia.github.io/propagation-library-wiki
[gh-actions-test-badge]: https://img.shields.io/github/actions/workflow/status/NTIA/proplib-template/ctest.yml?branch=main&logo=cmake&label=Build%2FTests&labelColor=162E51
[gh-actions-test-link]: https://github.com/NTIA/proplib-template/actions/workflows/ctest.yml
[gh-actions-docs-badge]: https://img.shields.io/github/actions/workflow/status/NTIA/proplib-template/doxygen.yml?branch=main&logo=c%2B%2B&label=Docs&labelColor=162E51
[gh-pages-docs-link]: https://ntia.github.io/proplib-template
[gh-releases-badge]: https://img.shields.io/github/v/release/NTIA/proplib-template?logo=github&label=Release&labelColor=162E51&color=D63E04
[gh-releases-link]: https://github.com/NTIA/proplib-template/releases
[gh-issues-badge]: https://img.shields.io/github/issues/NTIA/proplib-template?logo=github&label=Issues&labelColor=162E51
[gh-issues-link]: https://github.com/NTIA/proplib-template/issues
[doi-badge]: https://zenodo.org/badge/TODO-TEMPLATE.svg
[doi-link]: https://zenodo.org/badge/latestdoi/TODO-TEMPLATE

<!-- TODO-TEMPLATE: Replace the below description with one for your software -->
This code repository is a template repository for software in the NTIA/ITS
Propagation Library (PropLib). This template is intended for developers wishing
to develop a cross-platform C++ library as part of PropLib. Instructions on how
to use this repository are found in its [GitHub Wiki](https://github.com/NTIA/proplib-template/wiki).

Additional template repositories exist for building .NET, MATLAB, and Python
wrappers for PropLib C++ libraries. Finally, another template is available as
an example of a submodule repository to provide common test data to all versions
of the software. See:

- [NTIA/proplib-template-dotnet](https://github.com/NTIA/proplib-template-dotnet)
- [NTIA/proplib-template-matlab](https://github.com/NTIA/proplib-template-matlab)
- [NTIA/proplib-template-python](https://github.com/NTIA/proplib-template-python)
- [NTIA/proplib-template-test-data](https://github.com/NTIA/proplib-template-test-data)

## Contact ##

For questions about using this template repository, contact <aromaniello@ntia.gov>

<!-- TODO-TEMPLATE: Create the README contents. Boilerplate provided below.

Additional bindings to the shared library built from this repository are provided
for .NET, MATLAB, and Python in the following repositories:

- [NTIA/TODO-TEMPLATE-dotnet](https://github.com/NTIA/TODO-TEMPLATE-dotnet)
- [NTIA/TODO-TEMPLATE-matlab](https://github.com/NTIA/TODO-TEMPLATE-matlab)
- [NTIA/TODO-TEMPLATE-python](https://github.com/NTIA/TODO-TEMPLATE-python)

## Getting Started ##

TODO-TEMPLATE: Update links in this section, if applicable
TODO-TEMPLATE: Otherwise, add correct "getting started" information here.

To get started using this library, refer to
[its page on the **NTIA/ITS Propagation Library Wiki**](https://ntia.github.io/propagation-library-wiki/models/TODO-TEMPLATE/).
There, you will find installation instructions, usage information, and code
examples for all supported languages.

An executable is also provided which can be used to run the functions provided
by this library using plain text input and output files. Installation and usage
details for the command-line driver are provided in [its own README](./app/README.md).

If you're a developer and would like to contribute to or extend this repository,
you will find comprehensive documentation of this C++ code
[here](https://ntia.github.io/TODO-TEMPLATE), and a guide for contributors
[here](CONTRIBUTING.md).

## Configure and Build ##

The software is designed to be built into a DLL (or corresponding `.so` or `.dylib`
library for non-Windows systems). A CMake build configuration and presets are
provided for cross-platform builds. Presets provide default sets of compiler flags,
and additional set default CMake options to control which parts of the project are
build. Below are a few examples of how this project can be built using provided presets.

```cmd
# From this repository's root directory, try one of the following command pairs:

# "Release" configurations compile the library and driver, build docs, and configure tests:
cmake --preset release64
cmake --build --preset release64

# "Debug" configurations skip building the docs, driver, and driver tests:
cmake --preset debug64
cmake --build --preset debug64

# Additional options can override presets:
cmake --preset debug64 -DBUILD_DRIVER=ON

# "DocsOnly" configurations only build the docs:
cmake --preset docsOnly
cmake --build --preset docsOnly
```

Note that this repository makes use of several
[Git submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules)
to reference dependencies used for running unit tests and building documentation.
In order to do either, ensure the required submodules are cloned by running:

```cmd
# From this repository's root directory
git submodule init
git submodule update
```

## Running Tests ##

TODO-TEMPLATE: Update this section if needed, based on tests in the repo
TODO-TEMPLATE: Add any other testing info, such as links to available data

If you've configured tests when building the project, for example by using one of
the "Release" or "Debug" CMake presets, you can run the included unit tests as follows:

```cmd
ctest --preset release
```

## References ##

TODO-TEMPLATE: Add refs to, e.g., publications related to the software
TODO-TEMPLATE: Update or remove the link here to the Doxygen docs

* [ITS Propagation Library Wiki](https://ntia.github.io/propagation-library-wiki)
* [`ITS.TODO-TEMPLATE.THIS-LIBRARY` C++ API Reference](https://ntia.github.io/TODO-TEMPLATE)

## Contact ##

For technical questions, contact <code@ntia.gov>.

-->
