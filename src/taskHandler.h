#ifndef _TASKHANDLER_H_
#define _TASKHANDLER_H_
#include "../include/utility.h"

class taskHandler {
    private:
        int price, tableCount;
        std::string startTime, endTime;
        std::vector<request> requests, result;
        std::vector<computerStatus> computerStatuses;
        std::queue<std::string> queue;
        std::unordered_map<std::string, int> allClients;
    public:
    taskHandler();

    taskHandler(std::vector<request>& requests, int price, int tableCount, std::string startTime, std::string endTime);

    bool ifAnyFree();

    bool ifInPlace(std::string name);

    int countTime(std::string name);

    returnCode executeTasks();

    returnCode freeAll();

    std::vector<request> retrunResult();
};

#endif