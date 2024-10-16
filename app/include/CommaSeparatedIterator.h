/** @file CommaSeparatedIterator.h
 * Iterator class for reading comma-delimited input text streams.
 */
#pragma once

#include <algorithm>  // for transform
#include <cctype>     // for std::tolower
#include <fstream>    // for std::istream
#include <string>     // For std::string
#include <utility>    // for std::pair

/*******************************************************************************
 * @class CommaSeparatedIterator
 * An iterator that reads lines from an input stream, splitting each line
 * into two strings based on a comma delimiter.
 *
 * This iterator can work with both `std::stringstream` and `std::ifstream`.
 ******************************************************************************/
class CommaSeparatedIterator {
    public:
        using value_type = std::pair<std::string, std::string>;
        CommaSeparatedIterator(std::istream &stream);
        CommaSeparatedIterator &operator++();
        value_type operator*() const;
        explicit operator bool() const;
    private:
        std::istream &stream_;
        std::string line_;
        std::string first_;
        std::string second_;
};
