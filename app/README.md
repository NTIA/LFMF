# Command-line Driver #

This document explains the use of the included command-line driver. This is a
supplemental software tool to allow a user to call the compiled propagation library
from the command-line using text files to provide inputs and store outputs.

## Input Files ##

Inputs to the command-line driver are specified in an ASCII text file using
the common `key,value` format. Each line holds a single `key,value` combination,
with the `key` representing the model input variable name and the `value` representing
its value. An example is included in this repository [here](./data/in.txt).
(TODO-TEMPLATE update the above example data info/link)

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
| `-i`   | string | True     | File specifying model input parameters in `key,value` format          |
| `-o`   | string | True     | Filename where output results should be written                       |
| `-t`   | string | True     | File containing comma-delimited terrain elevation data along the path |
| `-dbg` | N/A    | False    | If specified, intermediate values will be written to the output file  |

Additional arguments are available to print help text and version information:

| Flag | Description                                            |
|------|--------------------------------------------------------|
| `-h` | Display help text                                      |
| `-v` | Display version information for the library and driver |

Input arguments are not case sensitive and do not have to be specified in a certain
order. A generic example of calling the command-line driver on Windows is:

(TODO-TEMPLATE: update example driver command below)
```cmd
<Driver>.exe -i <input_file> -t <terrain_file> -o <output_file>
```

### Examples ###

(TODO-TEMPLATE: Provide all included examples in the table below)
| Input File                | Terrain File                                        | Output File                 | Arguments                                          |
|---------------------------|-----------------------------------------------------|-----------------------------|----------------------------------------------------|
| [`in.txt`](./data/in.txt) | [`terrain_profile.txt`](./data/terrain_profile.txt) | [`out.txt`](./data/out.txt) | `-i in.txt -t terrain_profile.txt -o out.txt -dbg` |

## Command-line Driver Errors ##

(TODO-TEMPLATE: Update the below tables with your driver errors. Align with app/Errors.h)

In addition to the return codes defined by the library itself, the command-line
driver implements the following return codes.

### General Errors ###

| Value | Const Name                     | Description                                |
|-------|--------------------------------|--------------------------------------------|
| 1000  | `DRVR__RETURN_SUCCESS`         | Internal driver success code               |
| 1001  | `DRVRERR__MISSING_OPTION`      | No value provided for given argument       | 
| 1002  | `DRVRERR__INVALID_OPTION`      | Unknown option specified                   |
| 1003  | `DRVRERR__OPENING_INPUT_FILE`  | Failed to open the input file for reading  |
| 1004  | `DRVRERR__OPENING_OUTPUT_FILE` | Failed to open the output file for writing |

### Input File Parsing Errors ###

| Value | Const Name                    | Description                           |
|-------|-------------------------------|---------------------------------------|
| 1100  | `DRVRERR__PARSE`              | General input file parsing error      |

### Validation Errors ###

Driver validation errors occur when required command line arguments are missing.
These validation errors are distinct from any defined within the library itself,
which may include, e.g., parameter out-of-range errors.

| Value | Const Name                         | Description                      |
|-------|------------------------------------|----------------------------------|
| 1200  | `DRVRERR__VALIDATION_IN_FILE`      | Input file not specified         |
| 1201  | `DRVRERR__VALIDATION_OUT_FILE`     | Output file  not specified       |
