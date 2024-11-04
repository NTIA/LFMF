# Command-line Driver #

This document explains the use of the included command-line driver. This is a
supplemental software tool to allow a user to call the compiled propagation library
from the command-line using text files to provide inputs and store outputs.

## Input Files ##

Inputs to the command-line driver are specified in an ASCII text file using
the common `key,value` format. Each line holds a single `key,value` combination,
with the `key` representing the model input variable name and the `value` representing
its value.

## Output Files ##

After parsing the inputs and running the software, the command-line driver will
generate an output report file containing the results. This file contains a record
of the input parameters, along with the model outputs, and human-readable supporting
documentation.

## Execution ##

Executing the command-line driver requires specifying input arguments, defined
in the below table:

(TODO-TEMPLATE review and update the flags below)

| Flag   | Type   | Required | Description                                                           |
|--------|--------|----------|-----------------------------------------------------------------------|
| `-i`   | string | true     | File specifying model input parameters in `key,value` format          |
| `-o`   | string | true     | Filename where output results should be written                       |
| `-dbg` | N/A    | false    | If specified, intermediate values will be written to the output file  |

Additional arguments are available to print help text and version information:

| Flag | Description                                            |
|------|--------------------------------------------------------|
| `-h` | Display help text                                      |
| `-v` | Display version information for the library and driver |

Input arguments are not case sensitive and do not have to be specified in a certain
order. A generic example of calling the command-line driver on Windows is:

(TODO-TEMPLATE: update example driver command below)

```cmd
<Driver>.exe -i <input_file> -dbg -o <output_file>
```

### Examples ###

The following files are included as references for the functionality of this software.
Using these input files and the commands specified should produce outputs identical
to the provided corresponding output files.

(TODO-TEMPLATE: Provide all included examples in the table below)

| Input File                | Terrain File                                        | Output File                 | Arguments                                          |
|---------------------------|-----------------------------------------------------|-----------------------------|----------------------------------------------------|
| [`in.txt`](./data/in.txt) | [`terrain_profile.txt`](./data/terrain_profile.txt) | [`out.txt`](./data/out.txt) | `-i in.txt -t terrain_profile.txt -o out.txt -dbg` |

## Command-line Driver Errors ##

In addition to the return codes defined by the library itself, the command-line
driver implements its own set of return codes in [`app/include/ReturnCodes.h`](./include/ReturnCodes.h).
A helper function to map human-readable status messages to these codes in
[`app/src/ReturnCodes.cpp`](./src/ReturnCodes.cpp).
