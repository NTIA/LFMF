#include "TestUtils.h"

#include <string>  // for std::string

// TODO-TEMPLATE: populate this file with common utilities for tests

void appendDirectorySep(std::string &str) {
#ifdef _WIN32
    str += "\\";
#else
    str += "/";
#endif
}

std::string getDataDirectory() {
    std::string dataDir(__FILE__);
    dataDir.resize(dataDir.find_last_of("/\\"));
    dataDir.resize(dataDir.find_last_of("/\\"));
    appendDirectorySep(dataDir);
    dataDir += "extern";
    appendDirectorySep(dataDir);
    dataDir += "TODO-TEMPLATE";  // Name of data directory as cloned in the `extern` directory
    appendDirectorySep(dataDir);
    return dataDir;
}