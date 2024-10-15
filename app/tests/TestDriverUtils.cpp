#include "TestDriver.h"

TEST(ParseIntegerTest, TestParseIntegerSuccess) {
    int value;
    std::string toParse = "42";
    int rtn = ParseInteger(toParse, value);
    EXPECT_EQ(rtn, SUCCESS);
    EXPECT_EQ(value, 42);
}

TEST(ParseIntegerTest, TestParseIntegerFailure1) {
    int value;
    std::string toParse = "42.0";
    int rtn = ParseInteger(toParse, value);
    EXPECT_EQ(rtn, DRVRERR__PARSE);
}

TEST(ParseIntegerTest, TestParseIntegerFailure2) {
    int value;
    std::string toParse = "notAnInteger";
    int rtn = ParseInteger(toParse, value);
    EXPECT_EQ(rtn, DRVRERR__PARSE);
}

TEST(ParseDoubleTest, TestParseDoubleSuccess1) {
    double value;
    std::string toParse = "42.0";
    int rtn = ParseDouble(toParse, value);
    EXPECT_EQ(rtn, SUCCESS);
    EXPECT_DOUBLE_EQ(value, 42.0);
}

TEST(ParseDoubleTest, TestParseDoubleSuccess2) {
    double value;
    std::string toParse = "42";
    int rtn = ParseDouble(toParse, value);
    EXPECT_EQ(rtn, SUCCESS);
    EXPECT_DOUBLE_EQ(value, 42.0);
}

TEST(ParseDoubleTest, TestParseDoubleFailure) {
    double value;
    std::string toParse = "notADouble";
    int rtn = ParseDouble(toParse, value);
    EXPECT_EQ(rtn, DRVRERR__PARSE);
}
