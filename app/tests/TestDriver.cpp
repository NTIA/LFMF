/** @file TestDriver.cpp
 * The main entrypoint for the TestDriver executable
 */
#include "TestDriver.h"

int main() {
    // Driver executable needs to be in the same directory as this executable
    std::string executable = std::string(DRIVER_NAME);

#ifdef _WIN32
    executable += ".exe";
#endif

    std::string command;
    int rtn;

    // TODO-TEMPLATE
    // Implement the set of arguments to use when test-running the driver. The last
    // argument should be the expected return code. Example: if calling
    // `MyDriver.exe -i input.txt -o output.txt` is expected to return 0, the vector
    // argument would be: `{"-i", "input.txt", "-o", "output.txt", "0"}`

    // Input files must exist in the directory of this executable
    std::vector<std::vector<std::string>> argSet = {
        {"-i", "input.txt", "-o", "output.txt", "0"},
    };

    int expected_rtn;

    for (auto args : argSet) {
        expected_rtn = ParseInteger(args.back());
        args.pop_back();
        command = executable + " " + joinArguments(args);
        std::cout << "Running command: " << command << std::endl;
        rtn = std::system(command.c_str());
        if (rtn != expected_rtn) {
            std::cout << "[FAILURE] Returned " << rtn << ", expected "
                      << expected_rtn << std::endl;
        } else {
            std::cout << "[SUCCESS] Returned " << rtn << std::endl;
        }
        std::cout << std::endl;
    }

    return SUCCESS;
}