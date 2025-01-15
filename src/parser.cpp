#include "parser.h"

bool compareTime(const std::string& time1, const std::string& time2) {
    size_t pos1 = time1.find(':');
    size_t pos2 = time2.find(':');
    if (pos1 == std::string::npos || pos2 == std::string::npos) {
        return false;
    }

    int hours1 = std::stoi(time1.substr(0, pos1));
    int minutes1 = std::stoi(time1.substr(pos1 + 1));
    int hours2 = std::stoi(time2.substr(0, pos2));
    int minutes2 = std::stoi(time2.substr(pos2 + 1));

    if (hours1 < hours2) {
        return true;
    } else if (hours1 > hours2) {
        return false;
    } else {
        return minutes1 < minutes2;
    }
}

returnCode parseFile(std::string fileName, std::vector<request>& result, int& price) {
    std::ifstream file(fileName);
    if (!file) {
        return FILE_ERROR;
    }
    
    int tableCounter = -1;
    std::string startTime = "", endTime = "";
    price = -1;

    std::string line;
    std::getline(file, line);
    tableCounter = std::stoi(line);
    std::getline(file, line, ' ');
    startTime = line;
    std::getline(file, line);
    endTime = line;
    std::getline(file, line);
    price = std::stoi(line);


    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        request request;
        int iter = 0;
        while (std::getline(ss, token, ' ')) {
            switch (iter) {
            case 0:
                if (result.empty()) {
                    request.time = token;
                    break;
                };

                if (std::regex_match(token, TIMEREGEX) && compareTime(result[result.size() - 1].time, token) && 
                compareTime(token, endTime) && compareTime(startTime, token))
                    request.time = token;
                else {
                    std::cout << line;
                    return PARSER_ERROR;
                }
                break;

            case 1:
                request.ID = std::stoi(token);
                break;

            case 2:
                if (std::regex_match(token, NAMEREGEX))
                    request.name = token;
                else {
                    std::cout << line;
                    return PARSER_ERROR;
                }
                break;

            case 3:
                if (std::stoi(token) > tableCounter) {
                    std::cout << line;
                    return PARSER_ERROR;
                }
                request.PCNumber = std::stoi(token);
                break;
            
            default:
                break;
            }
            iter++;
        }
        result.push_back(request);
    }
    return SUCCESS;
}