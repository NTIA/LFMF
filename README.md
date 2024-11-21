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
-->
[![NTIA/ITS PropLib][proplib-badge]][proplib-link]
<!-- TODO-TEMPLATE: Add badges. See above for details.
[![GitHub Release][gh-releases-badge]][gh-releases-link]
[![GitHub Actions Unit Test Status][gh-actions-test-badge]][gh-actions-test-link]
[![C++ API Reference][gh-actions-docs-badge]][gh-pages-docs-link]
[![GitHub Issues][gh-issues-badge]][gh-issues-link]
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

<!-- TODO-TEMPLATE: Replace the below description with one for your software -->
This code repository is a template repository for software in the NTIA/ITS
Propagation Library (PropLib). This template is intended for developers wishing
to develop a cross-platform C++ library as part of PropLib. Instructions on how
to use this repository are found in its [GitHub Wiki](https://github.com/NTIA/proplib-template/wiki).

Additional template repositories exist for building .NET, MATLAB, and Python
wrappers for PropLib C++ libraries. See:

- [NTIA/proplib-template-dotnet](https://github.com/NTIA/proplib-template-dotnet)
- [NTIA/proplib-template-matlab](https://github.com/NTIA/proplib-template-matlab)
- [NTIA/proplib-template-python](https://github.com/NTIA/proplib-template-python)

## Contact ##

For questions about using this template repository, contact <aromaniello@ntia.gov>

<!-- TODO-TEMPLATE: Create the README contents. Boilerplate provided below.

## Getting Started ##

TODO-TEMPLATE: Update links in this section, if applicable
TODO-TEMPLATE: Otherwise, add correct "getting started" information here.

To get started using this model, refer to
[its page on the **NTIA/ITS Propagation Library Wiki**](https://ntia.github.io/propagation-library-wiki/models/TODO-TEMPLATE/).
There, you will find installation instructions, usage information, and code
examples for all supported languages.

If you're a developer and would like to contribute to or extend this repository,
you will find comprehensive documentation of this C++ code
[here](https://ntia.github.io/TODO-TEMPLATE), and a guide for contributors
[here](CONTRIBUTING.md).

## Configure and Build ##

The software is designed to be built into a DLL (or corresponding `.so` or `.dylib`
library for non-Windows systems). A CMake build configuration and presets are
provided for cross-platform builds, which can be carried out, for example, by:

```cmd
# From this repository's root directory, try one of the following command pairs:

# "Release" configurations compile the library, build docs, and configure tests:
cmake --preset release
cmake --build --preset release

# "Debug" configurations skip building the docs:
cmake --preset debug
cmake --build --preset debug

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
