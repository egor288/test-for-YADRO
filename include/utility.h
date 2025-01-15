// all includes and base struct for all project

#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

static std::regex NAMEREGEX("^[a-z0-9_-]+$");
static std::regex TIMEREGEX("^([01][0-9]|2[0-3]):([0-5][0-9])$");

enum returnCode {
    SUCCESS = 0,
    FAIL = 1,
    PARSER_ERROR = 2,
    MEMORY_ERROR = 3,
    FILE_ERROR = 4
};

typedef struct {
    std::string time;
    int ID;
    std::string name;
    int PCNumber;
    std::string error;
} request;

#endif