# Low Frequency / Medium Frequency (LF/MF) Propagation Model

This code repository contains an the NTIA/ITS implementation of the Low Frequency / Medium Frequency (LF/MF) Propagation Model. LF/MF predicts basic transmission loss in the frequency range 0.01 - 30 MHz for propagation paths over a smooth Earth and antenna heights less than 50 meters.

## Inputs ##

| Variable          | Type   | Units | Limits       | Description  |
|-------------------|--------|-------|--------------|--------------|
| `h_tx__meter`     | double | meter | 0 <= `h_tx__meter` <= 50 | Height of the transmitter |
| `h_rx__meter`     | double | meter | 0 <= `h_rx__meter` <= 50 | Height of the receiver |
| `f__mhz`          | double | MHz   | 0.01 <= `f__mhz` <= 30 | Frequency |
| `P_tx__watt`      | double | Watt  | 0 < `P_tx__watt` | Transmitter power |
| `N_s`             | double | N-Units | 250 <= `N_s` <= 400 | Surface refractivity |
| `d__km`           | double | km    | 0 < `d__km`  | Path distance |
| `epsilon`         | double |       | 1 <= `epsilon` | Relative permittivity |
| `sigma`           | double | S/m   | 0 < `sigma` | Conductivity |
| `pol`             | int    |       |              | Polarization <ul><li>0 = Horizontal</li><li>1 = Vertical</li></ul> |

## Outputs ##

Outputs to LFMF are contained within a defined `Result` structure.

| Variable      | Type   | Units | Description |
|---------------|--------|-------|-------------|
| `A_btl__db`   | double | dB    | Basic transmission loss |
| `E_dBuVm`     | double | dB(uV/m) | Electrice field strength |
| `P_rx__dbm`   | double | dBm   | Received power |
| `method`      | int    |       | Solution method <ul><li>0 = Flat earth with curve correction</li><li>1 = Residue series</li></ul> |

## Return Codes ##

Possible return codes, including the corresponding defined constant name as defined in `LFMF.h`:

| Value | Const Name                       | Description  |
| ------|----------------------------------|--------------|
|     0 | `SUCCESS`                        | Successful execution |
|  1000 | `ERROR__TX_TERMINAL_HEIGHT`      | TX terminal height is out of range |
|  1001 | `ERROR__RX_TERMINAL_HEIGHT`      | RX terminal height is out of range |
|  1002 | `ERROR__FREQUENCY`               | Frequency is out of range |
|  1003 | `ERROR__TX_POWER`                | Transmit power is out of range |
|  1004 | `ERROR__SURFACE_REFRACTIVITY`    | Surface refractivity is out of range |
|  1005 | `ERROR__PATH_DISTANCE`           | Path distance is out of range |
|  1006 | `ERROR__EPSILON`                 | Epsilon is out of range |
|  1007 | `ERROR__SIGMA`                   | Sigma is out of range |
|  1008 | `ERROR__POLARIZATION`            | Invalid value for polarization |

## Example Values ##

A set of example inputs and outputs are provided for testing purposes.  This is not a comprehensive validation test set.  The test set can be found in [LFMF_Examples.csv](LFMF_Examples.csv).

## Notes on Code Style ##

* In general, variables follow the naming convention in which a single underscore denotes a subscript (pseudo-LaTeX format), where a double underscore is followed by the units, i.e. h_tx__meter.
* Variables are named to match their corresponding mathematical variables from their publication text.
* Wherever possible, equation numbers are provided.

## Configure and Build ##

### C++ Software

The software is designed to be built into a DLL (or corresponding library for non-Windows systems). The source code can be built for any OS that supports the standard C++ libraries. A Visual Studio 2022 project file is provided for Windows users to support the build process and configuration.

### C#/.NET Wrapper Software

The .NET support of LFMF consists of a simple pass-through wrapper around the native DLL.  It is compiled to target .NET Framework 4.8.1.  Distribution and updates are provided through the published NuGet package.

## References ##

* Bremmer, H. "Terrestrial Radio Waves" _Elsevier_, 1949. 
* DeMinco, N. "Medium Frequency Propagation Prediction Techniques and Antenna Modeling for Intelligent Transportation Systems (ITS) Broadcast Applications", [_NTIA Report 99-368_](https://www.its.bldrdoc.gov/publications/2399.aspx), August 1999
* DeMinco, N. "Ground-wave Analysis Model For MF Broadcast System", [_NTIA Report 86-203_](https://www.its.bldrdoc.gov/publications/2226.aspx), September 1986
* Sommerfeld, A. "The propagation of waves in wireless telegraphy", _Ann. Phys._, 1909, 28, p.665
* Wait, J. "Radiation From a Vertical Antenna Over a Curved Stratified Ground", _Journal of Research of the National Bureau of Standards_.  Vol 56, No. 4, April 1956. Research Paper 2671

## Contact ##

For questions, contact Nick DeMinco, (303) 497-3660, NDeminco@ntia.gov
