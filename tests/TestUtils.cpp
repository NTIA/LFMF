/** @file TestUtils.cpp
 * Primary implementations for fixtures or common functions used by unit tests.
 */
#include "TestUtils.h"

#include <string>  // for std::string

// TODO-TEMPLATE: populate this file with common utilities for tests

/*******************************************************************************
 * Append a directory separator ('/' or '\') to a string, based on the
 * current operating system.
 *
 *  @param[in, out] str  String to which the character will be appended.
 *****************************************************************************/
void AppendDirectorySep(std::string &str) {
#ifdef _WIN32
    str += "\\";
#else
    str += "/";
#endif
}

/******************************************************************************
 * Get the full path of the directory containing test data files.
 * 
 * @return The path of the test data directory.
 *****************************************************************************/
std::string GetDataDirectory() {
    std::string dataDir(__FILE__);
    dataDir.resize(dataDir.find_last_of("/\\"));
    dataDir.resize(dataDir.find_last_of("/\\"));
    AppendDirectorySep(dataDir);
    dataDir += "extern";
    AppendDirectorySep(dataDir);
    dataDir
        += "test-data";  // Name of data directory as cloned in the `extern` directory
    AppendDirectorySep(dataDir);
    return dataDir;
}

// TODO-TEMPLATE: Remove this test and write your own in other files.
// This is included to verify test discovery is functional in the template.
TEST(TemplateTest, TestTemplate) {
    EXPECT_EQ(1, 1);
}
