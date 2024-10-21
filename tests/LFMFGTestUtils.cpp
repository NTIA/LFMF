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
        for (cell_vec_size_t i = 0; i < csvRows[0].size(); i++) {
            if (csvRows[0][i] == "h_tx__meter") {
                d.h_tx__meter = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "h_rx__meter") {
                d.h_rx__meter = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "f__mhz") {
                d.f__mhz = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "P_tx__watt") {
                d.P_tx__watt = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "N_s") {
                d.N_s = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "d__km") {
                d.d__km = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "epsilon") {
                d.epsilon = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "sigma") {
                d.sigma = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "pol") {
                d.pol = std::stoi(csvRows[r][i]);
            }

            if (csvRows[0][i] == "rtn") {
                d.expectedReturn = std::stoi(csvRows[r][i]);
            }
            if (csvRows[0][i] == "A_btl__db") {
                d.expectedResult.A_btl__db = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "E_dBuVm") {
                d.expectedResult.E_dBuVm = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "P_rx__dbm") {
                d.expectedResult.P_rx__dbm = std::stod(csvRows[r][i]);
            }
            if (csvRows[0][i] == "method") {
                d.expectedResult.method = std::stoi(csvRows[r][i]);
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
    //dataDir.resize(dataDir.find_last_of("/\\"));
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