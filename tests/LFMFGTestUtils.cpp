#include "LFMFGTest.h"
#include <fstream>
#include <sstream>
#include <filesystem>


/*=============================================================================
 |
 |  Description:  This function loads test data from a CSV file
 |
 |      Input:      &filename       - Test Data CSV file name
 |
 |    Returns:      testData        - a vector includes one or more test cases
 |                                    in SlantPathInputsAndResult Structure
 |
 *===========================================================================*/
std::vector<LFMFInputsAndResult>
    ReadLFMFInputsAndResult(const std::string &filename) {
    std::vector<LFMFInputsAndResult> testData;
    std::string dataDir = GetDirectory("data");
    std::ifstream file(dataDir + filename);
    LFMFInputsAndResult d {};  // struct to store data from a single line of CSV

    std::vector<std::vector<std::string>> csvRows = readCSV(file);
    if (csvRows.size() <= 1) {
        return testData;
    }    

    typedef std::vector<std::vector<std::string> >::size_type row_vec_size_t;
    typedef std::vector<std::string>::size_type cell_vec_size_t;
        
    for (row_vec_size_t r = 1; r < csvRows.size(); r++) {
        for (cell_vec_size_t i = 1; i < csvRows[0].size(); i++) {
            if (csvRows[0][i] == "mode") {
                if (csvRows[r][i] != "slant") {
                
                }
            }
            if (csvRows[0][i] == "f__ghz") {
                d.f__ghz = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "h_1__km") {
                d.h_1__km = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "h_2__km") {
                d.h_2__km = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "beta_1__rad") {
                d.beta_1__rad = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "atmosphere") {
                d.atmosphere = std::stod(csvRows[r][i]);
            }
            
            if (csvRows[0][i] == "rtn") {
                d.expectedReturn = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "A_gas__db") {
                d.expectedResult.A_gas__db = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "bending__rad") {
                d.expectedResult.bending__rad = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "a__km") {
                d.expectedResult.a__km = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "incident__rad") {
                d.expectedResult.incident__rad = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "delta_L__km") {
                d.expectedResult.delta_L__km = std::stod(csvRows[r][i]);
            }
        }
        testData.push_back(d);
    }

    return testData;
}

/*=============================================================================
 |
 |  Description:  This function loads test data from a CSV file
 |
 |      Input:      &filename       - Test Data CSV file name
 |
 |    Returns:      testData        - a vector includes one or more test cases
 |                                    in TerrestrialPathInputsAndResult Structure
 |
 *===========================================================================*/
std::vector<TerrestrialPathInputsAndResult> ReadP676TerrestrialPathInputsAndResult(const std::string& filename) {
    std::vector<TerrestrialPathInputsAndResult> testData;
    std::string dataDir = GetDirectory("data");
    std::ifstream file(dataDir + filename);
    TerrestrialPathInputsAndResult d{};  // struct to store data from a single line of CSV
    
    std::vector<std::vector<std::string>> csvRows = readCSV(file);
    if (csvRows.size() <= 1) {
        return testData;
    }

    typedef std::vector<std::vector<std::string> >::size_type row_vec_size_t;
    typedef std::vector<std::string>::size_type cell_vec_size_t;

    for (row_vec_size_t r = 1; r < csvRows.size(); r++) {
        for (cell_vec_size_t i = 1; i < csvRows[0].size(); i++) {
            if (csvRows[0][i] == "mode") {
                if (csvRows[r][i] != "ter") {

                } if (csvRows[r][i] != "terex") {

                }
            }
            if (csvRows[0][i] == "f__ghz") {
                d.f__ghz = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "T__kelvin") {
                d.T__kelvin = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "e__hPa") {
                d.e__hPa = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "p__hPa") {
                d.p__hPa = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "atmosphere") {
                d.atmosphere = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "r_0__km") {
                d.r_0__km = std::stod(csvRows[r][i]);
            }

            if (csvRows[0][i] == "rtn") {
                d.expectedReturn = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "A_gas__db") {
                d.expectedA_gas__db = std::stod(csvRows[r][i]);
            }
        }
        testData.push_back(d);
    }

    return testData;
}

/*=============================================================================
 |
 |  Description:  This function appends director separator based on
 |                Operating System
 |
 |        Input:  &str              - Path name
 |
 |      Outputs:  str               - Path name with director separator
 |
 |      Returns:  [void]
 |
 *===========================================================================*/
static void AppendDirectorySep(std::string& str) {
#ifdef _WIN32
    str += "\\";
#else
    str += "/";
#endif
}

/*=============================================================================
 |
 |  Description:  This function gets the full path of a given directory
 |
 |        Input:  name             - directory name
 |
 |      Returns:  dataDir          - full path of the given directory
 |
 *===========================================================================*/
static std::string GetDirectory(std::string name) {
    std::string dataDir(__FILE__);
    dataDir.resize(dataDir.find_last_of("/\\"));
    dataDir.resize(dataDir.find_last_of("/\\"));
    AppendDirectorySep(dataDir);
    dataDir += name;
    AppendDirectorySep(dataDir);
    return dataDir;
}

// Read CSV file, Excel dialect. Accept "quoted fields ""with quotes"""
enum class CSVState {
    UnquotedField,
    QuotedField,
    QuotedQuote
};

/*=============================================================================
 |
 |  Description:  This function parse a CSV row into cells
 |
 |        Input:  &row              - a CSV row in string
 |
 |      Returns:  fields            - a vector of CSV cells in string
 |
 *===========================================================================*/
std::vector<std::string> readCSVRow(const std::string& row) {
    CSVState state = CSVState::UnquotedField;
    std::vector<std::string> fields{ "" };
    size_t i = 0; // index of the current field
    for (char c : row) {
        switch (state) {
        case CSVState::UnquotedField:
            switch (c) {
            case ',': // end of field
                fields.push_back(""); i++;
                break;
            case '"': state = CSVState::QuotedField;
                break;
            default:  fields[i].push_back(c);
                break;
            }
            break;
        case CSVState::QuotedField:
            switch (c) {
            case '"': state = CSVState::QuotedQuote;
                break;
            default:  fields[i].push_back(c);
                break;
            }
            break;
        case CSVState::QuotedQuote:
            switch (c) {
            case ',': // , after closing quote
                fields.push_back(""); i++;
                state = CSVState::UnquotedField;
                break;
            case '"': // "" -> "
                fields[i].push_back('"');
                state = CSVState::QuotedField;
                break;
            default:  // end of quote
                state = CSVState::UnquotedField;
                break;
            }
            break;
        }
    }
    return fields;
}

/*=============================================================================
 |
 |  Description:  This function loads a CSV file in vector
 |
 |        Input:  &in               - Input file stream
 |
 |      Returns:  table             - A vector includes CSV file cells by row
 |
 *===========================================================================*/
std::vector<std::vector<std::string>> readCSV(std::istream& in) {
    std::vector<std::vector<std::string>> table;
    std::string row;
    while (!in.eof()) {
        std::getline(in, row);
        if (in.bad() || in.fail()) {
            break;
        }
        auto fields = readCSVRow(row);
        table.push_back(fields);
    }
    return table;
}