// all includes and base struct for all project

#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

static std::regex NAMEREGEX("^[a-z0-9_-]+$");
static std::regex TIMEREGEX("^([01][0-9]|2[0-3]):([0-5][0-9])$");

static bool compareTime(const std::string& time1, const std::string& time2);

enum returnCode {
    SUCCESS = 0,
    FAIL = 1,
    PARSER_ERROR = 2,
    MEMORY_ERROR = 3,
    FILE_ERROR = 4
};

struct request {
    request() : ID(-1), PCNumber(-1) {}
    std::string time;
    int ID;
    std::string name;
    int PCNumber;
    std::string error;
};

struct computerStatus{
    computerStatus(int PCNumber) : PCNumber(PCNumber), isFree(true), clientID(-1), totalTime(0) {}
    int PCNumber;
    bool isFree;
    int clientID;
    int totalTime;
};

#endif