// all includes and base struct for all project

#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

enum returnCode
{
    SUCCESS = 0,
    FAIL = 1,
    PARSER_ERROR = 2,
    MEMORY_ERROR = 3
};


typedef struct {
    std::string time;
    int ID;
    std::string name;
    int PCNumber;
    std::string error;
} request;

#endif