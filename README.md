# NTIA/ITS Propagation Library Template Project #
<!-- TODO-TEMPLATE: Update software name above -->

<!-- TODO-TEMPLATE: Uncomment these if your repository has tests/docs actions -->
<!-- [![Unit Tests Status][gh-actions-test-badge]][gh-actions-test-link] -->
<!-- [![C++ API Reference][gh-actions-docs-badge]][gh-actions-docs-link] -->
![GitHub Release][gh-releases-badge]
![GitHub Issues][gh-issues-badge]
<!-- TODO-TEMPLATE: Only include the DOI badge if a DOI exists for a release. -->
<!-- [![DOI][doi-badge]][doi-link] -->

<!-- TODO-TEMPLATE: Update repository links (and action names if needed) below -->
<!-- [gh-actions-test-link]: https://github.com/NTIA/TODO-TEMPLATE/actions/workflows/ctest.yml
[gh-actions-test-badge]: https://github.com/NTIA/TODO-TEMPLATE/actions/workflows/ctest.yml/badge.svg?branch=main -->
<!-- [gh-actions-docs-link]: https://github.com/NTIA/TODO-TEMPLATE/actions/workflows/doxygen.yml
[gh-actions-docs-badge]: https://github.com/NTIA/TODO-TEMPLATE/actions/workflows/doxygen.yml/badge.svg?branch=main -->
[gh-releases-badge]: https://img.shields.io/github/v/release/NTIA/TODO-TEMPLATE
[gh-issues-badge]: https://img.shields.io/github/issues/NTIA/TODO-TEMPLATE
<!-- TODO-TEMPLATE: Only create a DOI for versioned public releases -->
<!-- [doi-badge]: https://zenodo.org/badge/DOI/TODO-TEMPLATE/zenodo.TODO-TEMPLATE.svg
[doi-link]: https://doi.org/TODO-TEMPLATE/zenodo.TODO-TEMPLATE -->

<!-- TODO-TEMPLATE: Replace the below description with one for your software -->
This code repository is a template repository for software in the NTIA/ITS
Propagation Library (PropLib). This template is intended for developers wishing
to develop a cross-platform C++ library as part of PropLib. Instructions on how
to use this repository are found in [CREATING-REPOSITORIES.md](./CREATING-REPOSITORIES.md).

## Getting Started ##

<!-- TODO-TEMPLATE: Update links in this section, if applicable -->
<!-- TODO-TEMPLATE: Otherwise, add correct "getting started" information here. -->
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
git submodule init extern/googletest           # Required to run tests
git submodule init extern/doxygen-awesome-css  # Required to build docs
git submodule update                           # Clones the initialized submodules
```

## Running Tests ##
<!-- TODO-TEMPLATE: Update this section if needed, based on tests in the repo -->
<!-- TODO-TEMPLATE: Add any other testing info, such as links to available data -->

If you've configured tests when building the project, for example by using one of
the "Release" or "Debug" CMake presets, you can run the included unit tests as follows:

```cmd
ctest --preset release
```

## References ##

<!-- TODO-TEMPLATE: Add refs to, e.g., publications related to the software -->
<!-- TODO-TEMPLATE: Update or remove the link here to the Doxygen docs -->

* [ITS Propagation Library Wiki](https://ntia.github.io/propagation-library-wiki)
* [`ITS.TODO-TEMPLATE.THIS-LIBRARY` C++ API Reference](https://ntia.github.io/TODO-TEMPLATE)

## Contact ##

For technical questions, contact <code@ntia.gov>.
