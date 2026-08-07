# Creating Repositories from `proplib-template`

This guide is the checklist for turning `proplib-template` into a real
PropLib C++ repository.

## 1. Create the New Repository

1. Create a new repository from this template.
2. Rename the repository to the target software name.
3. Update the default branch policy and protection rules as needed.

## 2. Replace Required Placeholders

Search the repository for `TODO-TEMPLATE` and replace each occurrence with
project-specific content. At minimum, review these files:

- `README.md`
- `CMakeLists.txt`
- `.zenodo.json`
- `GitHubRepoPublicReleaseApproval.md`
- `.github/workflows/*.yml`
- `include/PropLibTemplate.h`
- `src/ReturnCodes.cpp`
- `app/` and `tests/` sources

## 3. Rename Library-Facing Identifiers

Update the template library names and exported interface identifiers:

- rename `include/PropLibTemplate.h` to the real public header name
- update `LIB_NAME`, `project(...)`, namespaces, and exported symbol names
- replace placeholder return codes, constants, and API declarations
- update driver help text and argument handling in `app/`

## 4. Review Build and Test Scaffolding

1. Replace template source lists in `src/CMakeLists.txt`, `tests/CMakeLists.txt`,
   and `app/tests/CMakeLists.txt`.
2. Remove placeholder tests and add model-specific tests.
3. Add any required test-data submodule references to workflows and docs.
4. Verify the `release.yml` header artifact path matches the renamed public header.

## 5. Review Documentation and Metadata

Before public release, ensure:

- README badges and links point at the new repository
- PropLib wiki and Doxygen links target the real model pages
- `.zenodo.json` contains correct title, creators, identifiers, and version
- `GitHubRepoPublicReleaseApproval.md` is completed with placeholders removed
- release notes and companion wrapper repository links are correct

## 6. Review Companion Repositories

If the software will have language bindings or shared test data, create and
customize the companion repositories as needed:

- `proplib-template-dotnet`
- `proplib-template-matlab`
- `proplib-template-python`
- `proplib-template-test-data`

## 7. Validate Before First Release

Run the project workflows or equivalent local commands and confirm:

```cmd
cmake --preset release64
cmake --build --preset release64
ctest --preset release64
```

Also verify that:

- Doxygen builds successfully
- release workflows upload the expected binaries and header artifacts
- template/example comments have been removed where no longer useful
- public-facing docs no longer describe the repository as a template
