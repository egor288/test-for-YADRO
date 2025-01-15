#ifndef _PARSER_H_
#define _PARSER_H_
#include "../include/utility.h"

returnCode parseFile(std::string fileName, std::vector<request>& result, int& price);
bool compareTime(const std::string& time1, const std::string& time2);

#endif