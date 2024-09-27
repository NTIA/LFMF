# Command-line Driver #

This document explains the use of the included command-line driver. This is a
supplemental software tool to allow a user to call the compiled propagation library
from the command-line using text files to provide inputs and store outputs.

## Input Files ##

Inputs to the command-line driver are specified in an ASCII text file using
the common `key,value` format. Each line holds a single `key,value` combination,
with the `key` representing the model input variable name and the `value` representing
its value. An example is included in this repository [here](./data/in.txt).

## Output Files ##

After parsing the inputs and running the software, the command-line driver will
generate an output report file containing the results. This file contains a record
of the input parameters, along with the model outputs, and human-readable supporting
documentation.

## Execution ##

Executing the command-line driver requires specifying input arguments, defined
in the below table:

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

```cmd
<Driver>.exe -i <input_file> -t <terrain_file> -o <output_file>
```

### Examples ###

| Input File                | Terrain File                                        | Output File                 | Arguments                                          |
|---------------------------|-----------------------------------------------------|-----------------------------|----------------------------------------------------|
| [`in.txt`](./data/in.txt) | [`terrain_profile.txt`](./data/terrain_profile.txt) | [`out.txt`](./data/out.txt) | `-i in.txt -t terrain_profile.txt -o out.txt -dbg` |

## Command-line Driver Errors ##

In addition to the return codes defined by the library itself, the command-line
driver implements the following return codes.

### General Errors ###

| Value | Const Name                     | Description                                |
|-------|--------------------------------|--------------------------------------------|
| 1000  | `DRVR__RETURN_SUCCESS`         | Successful execution                       |
| 1003  | `DRVRERR__INVALID_OPTION`      | Unknown option specified                   |
| 1007  | `DRVRERR__OPENING_OUTPUT_FILE` | Failed to open the output file for writing |

### Input File Parsing Errors ###

| Value | Const Name                    | Description                           |
|-------|-------------------------------|---------------------------------------|
| 1100  | `DRVRERR__PARSE`              | General input file parsing error      |
| 1101  | `DRVRERR__PARSE_HTX`          | Unable to parse transmitter height    |
| 1102  | `DRVRERR__PARSE_HRX`          | Unable to parse receiver height       |
| 1103  | `DRVRERR__PARSE_CLIMATE`      | Unable to parse climate               |
| 1104  | `DRVRERR__PARSE_N0`           | Unable to parse refractivity          |
| 1105  | `DRVRERR__PARSE_FREQ`         | Unable to parse frequency             |
| 1106  | `DRVRERR__PARSE_POL`          | Unable to parse polarization          |
| 1107  | `DRVRERR__PARSE_EPSILON`      | Unable to parse relative permittivity |
| 1108  | `DRVRERR__PARSE_SIGMA`        | Unable to parse conductivity          |
| 1109  | `DRVRERR__PARSE_MDVAR`        | Unable to parse mode of variability   |
| 1110  | `DRVRERR__PARSE_TIME`         | Unable to parse time                  |
| 1111  | `DRVRERR__PARSE_LOCATION`     | Unable to parse location              |
| 1112  | `DRVRERR__PARSE_SITUATION`    | Unable to parse situation             |
| 1113  | `DRVRERR__PARSE_TSTEP`        | Unable to parse terrain step size     |
| 1114  | `DRVRERR__PARSE_TERRAIN_FILE` | Unable to parse terrain data file     |

### Validation Errors ###

Driver validation errors occur when required command line arguments are missing.
These validation errors are distinct from any defined within the library itself,
which may include, e.g., parameter out-of-range errors.

| Value | Const Name                         | Description                           |
|-------|------------------------------------|---------------------------------------|
| 1202  | `DRVRERR__VALIDATION_IN_FILE`      | Input parameter file is not specified |
| 1203  | `DRVRERR__VALIDATION_OUT_FILE`     | Output file is not specified          |
| 1204  | `DRVRERR__VALIDATION_TERRAIN_FILE` | Terrain file is not specified         |
