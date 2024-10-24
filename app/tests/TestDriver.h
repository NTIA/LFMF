/** @file TestDriver.h
 * Primary header and test fixture for command line driver tests.
 */
#pragma once

#include "Driver.h"
#include "TempTextFile.h"

#include <algorithm>      // for std::replace
#include <cstdio>         // for std::remove
#include <cstdlib>        // for std::system
#include <gtest/gtest.h>  // GoogleTest
#include <iostream>       // for std::cout, std::endl
#include <string>         // for std::string


/*******************************************************************************
 * @class DriverTest
 * Test fixture for running the driver executable tests.
 * 
 * This class extends the Google Test framework's Test class and provides
 * utilities to set up, execute, and manage the output of the driver executable.
 ******************************************************************************/
class DriverTest: public ::testing::Test {
    protected:
        /***********************************************************************
         * Sets up the test environment.
         * 
         * Initializes the executable path based on the platform. On Windows,
         * it adjusts the path separators and appends the ".exe" extension.
         **********************************************************************/
        void SetUp() override {
            // Get the name of the executable to test
            executable = std::string(DRIVER_LOCATION);
            executable += "/" + std::string(DRIVER_NAME);
#ifdef _WIN32
            std::replace(executable.begin(), executable.end(), '/', '\\');
            executable += ".exe";
#else
            executable = "./" + executable;
#endif
        }

        /***********************************************************************
         * Suppresses the output of the command.
         * 
         * Appends redirection to suppress standard output and error based on
         * the platform.
         * 
         * @param[in, out] cmd  The command string to modify
         **********************************************************************/
        void SuppressOutputs(std::string &cmd) {
#ifdef _WIN32
            cmd += " > nul";
#else
            cmd += " > /dev/null";
#endif
            cmd += " 2>&1";
        }

        /***********************************************************************
         * Builds the command string to run the driver.
         * 
         * Constructs a command string using the provided input file, model,
         * and output file. Optionally suppresses outputs.
         * 
         * @param[in] inFile          The input file path
         * @param[in] debug           The debug flag
         * @param[in] outFile         The output file path
         * @param[in] suppressOutputs Whether to suppress outputs (default: true)
         * @return                    The constructed command string
         **********************************************************************/
        std::string BuildCommand(
            const std::string &inFile,
            const bool debug,
            const std::string &outFile,
            const bool suppressOutputs = true
        ) {
            // TODO-TEMPLATE: Modify this function to accept all necessary
            // parameters to construct a string to call the driver under test.

            // Construct command from parameters
            std::string command = executable;
            command += " -i " + inFile;
            if (debug) {
                command += " -DBG";
            }
            command += " -o " + outFile;

            // Suppress text output of the driver, to avoid cluttering
            // test outputs.
            if (suppressOutputs) {
                SuppressOutputs(command);
            }
            // Return the full command string
            return command;
        }

        /***********************************************************************
         * Runs the driver executable.
         * 
         * @param[in] inFile   The input file path
         * @param[in] debug    The debug flag value
         * @param[in] outFile  The output file path
         * @return             The return code from the driver execution
         **********************************************************************/
        int RunDriver(
            const std::string &inFile,
            const bool debug,
            const std::string &outFile
        ) {
            // TODO update this to use DrvrParams
            // TODO-TEMPLATE: Update this function based on required driver inputs
            std::string cmd = BuildCommand(inFile, debug, outFile);
            int rtn = std::system(cmd.c_str());
            return rtn;
        }

        /***********************************************************************
         * Runs the driver using the specified input file contents.
         * 
         * Creates a temporary file with the given contents and executes the
         * driver, then cleans up the output file.
         * 
         * @param[in] inFileContents  The contents to write to the input file
         * @param[in] debug           The debug flag value
         * @param[in] outFile         Output file path (default is "tmp_out.txt")
         * @return                    Return code from the driver execution
         **********************************************************************/
        int RunDriverWithInputFile(
            const std::string &inFileContents,
            const bool debug,
            const std::string &outFile = "tmp_out.txt"
        ) {
            // TODO update this to use drvrparams
            TempTextFile tempFile(inFileContents);
            std::string inFile = tempFile.getFileName();
            int rtn = RunDriver(inFile, debug, outFile);
            // Cleanup: delete output file if it was created
            DeleteOutputFile(outFile);
            return rtn;
        }

        /***********************************************************************
         * Deletes the specified output file if it exists.
         * 
         * Checks if the file exists and attempts to delete it. Reports any
         * errors encountered during deletion.
         * 
         * @param[in] fileName  The name of the file to delete.
         **********************************************************************/
        void DeleteOutputFile(const std::string &fileName) {
            bool fileExists = false;
#ifdef _WIN32
            fileExists = _access(fileName.c_str(), 0) == 0;
#else
            fileExists = access(fileName.c_str(), F_OK) == 0;
#endif
            if (fileExists) {
                if (std::remove(fileName.c_str()) != 0) {
                    std::perror("Error deleting output file");
                }
            }
        }

        // Holds the platform-dependent string to call the executable
        std::string executable;
};
