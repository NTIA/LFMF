# Low Frequency / Medium Frequency (LF/MF) Propagation Model #

<!-- TODO-TEMPLATE: README BADGES

- The first badge links to the PropLib Wiki and does not need to be edited
- The second badge automatically displays and links to the most recent GitHub Release.
    - Make sure to update the [gh-releases-badge] and [gh-releases-link] URLs with your repo name
- The third badge links to the zenodo DOI page. Only include this badge if a DOI exists for a release.
    - Update the [doi-link] using the "id" from https://api.github.com/repos/ntia/{repo_name}. For example, the
      [doi-link] for ITM would be https://zenodo.org/badge/latestdoi/218981682. Using the repository ID in this link
      will automatically make the link always point to the most recent DOI for the repository, so this won't need to be
      edited every time a new release is made.
    - Update the [doi-badge] to include the "all versions" DOI which always points to the latest version. This can be found
      when creating the DOI in zenodo. The slash in the DOI must be replaced with "%2F" to render in the badge. For example,
      the P2108 DOI is 10.5281/zenodo.7114033 which must be input as "10.5281%2Fzenodo.7114033"
- The fourth badge is the CMake/CTest GitHub actions status.
    - Update the repository name in [gh-actions-test-badge] and [gh-actions-test-link]
- The fifth badge is the Doxygen github actions status.
    - Update the repository name in [gh-actions-docs-badge]
    - Update the repository name in [gh-pages-docs-link]
- The sixth badge displays open GitHub Issues
    - Update the repository name in [gh-issues-badge]
    - Update the repository name in [gh-issues-link]
-->
[![NTIA/ITS PropLib][proplib-badge]][proplib-link]
[![GitHub Release][gh-releases-badge]][gh-releases-link]
[![DOI][doi-badge]][doi-link]
[![GitHub Actions Unit Test Status][gh-actions-test-badge]][gh-actions-test-link]
[![C++ API Reference][gh-actions-docs-badge]][gh-pages-docs-link]
[![GitHub Issues][gh-issues-badge]][gh-issues-link]

[proplib-badge]: https://img.shields.io/badge/PropLib-badge?label=%F0%9F%87%BA%F0%9F%87%B8%20NTIA%2FITS&labelColor=162E51&color=D63E04
[proplib-link]: https://ntia.github.io/propagation-library-wiki
[gh-actions-test-badge]: https://img.shields.io/github/actions/workflow/status/NTIA/LFMF/ctest.yml?branch=main&logo=cmake&label=Build%2FTests&labelColor=162E51
[gh-actions-test-link]: https://github.com/NTIA/LFMF/actions/workflows/ctest.yml
[gh-actions-docs-badge]: https://img.shields.io/github/actions/workflow/status/NTIA/LFMF/doxygen.yml?branch=main&logo=c%2B%2B&label=Docs&labelColor=162E51
[gh-pages-docs-link]: https://ntia.github.io/LFMF
[gh-releases-badge]: https://img.shields.io/github/v/release/NTIA/LFMF?logo=github&label=Release&labelColor=162E51&color=D63E04
[gh-releases-link]: https://github.com/NTIA/LFMF/releases
[gh-issues-badge]: https://img.shields.io/github/issues/NTIA/LFMF?logo=github&label=Issues&labelColor=162E51
[gh-issues-link]: https://github.com/NTIA/LFMF/issues
[doi-badge]: https://img.shields.io/badge/{TODO-ALL-VERSIONS-DOI}-x?logo=doi&logoColor=ffffff&labelColor=162E51&color=D63E04
[doi-link]: https://zenodo.org/badge/latestdoi/{TODO-REPOSITORY-ID}

This code repository contains the U.S. Reference Software Implementation of
Low Frequency / Medium Frequency (LF/MF) Propagation Model.

## Getting Started ##

To get started using this model, refer to
[its page on the **NTIA/ITS Propagation Library Wiki**](https://ntia.github.io/propagation-library-wiki/models/LFMF/).
There, you will find installation instructions, usage information, and code
examples for all supported languages.

If you're a developer and would like to contribute to or extend this repository,
you will find comprehensive documentation of this C++ code
[here](https://ntia.github.io/LFMF), and a guide for contributors
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

If you've configured tests when building the project, for example by using one of
the "Release" or "Debug" CMake presets, you can run the included unit tests as follows:

```cmd
ctest --preset release -C Release
```

## References ##

* [ITS Propagation Library Wiki](https://ntia.github.io/propagation-library-wiki)
* [LFMF Wiki Page](https://ntia.github.io/propagation-library-wiki/models/LFMF)
* [`ITS.Propagation.LFMF` C++ API Reference](https://ntia.github.io/LFMF)

## Contact ##

For technical questions, contact <code@ntia.gov>.
