#include "taskHandler.h"

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

class taskHandler {
private:
    int price, tableCount;
    std::string startTime, endTime;
    std::vector<request> requests, result;
    std::vector<computerStatus> computerStatuses;
    std::queue<std::string> queue;
    std::unordered_map<std::string, int> allClients;
public:
    taskHandler() : price(-1), tableCount(-1) {}
    taskHandler(std::vector<request>& requests, int price, int tableCount, std::string startTime, std::string endTime) 
    : requests(requests), price(price), tableCount(tableCount), startTime(startTime), endTime(endTime) {
        for (int i = 0; i < tableCount; i++) {
            computerStatuses.push_back(computerStatus(i + 1));
        }
    }
    
    returnCode executeTasks(std::vector<request> requests, int price, int tableCount) {
        for(request req : requests) {
            switch (req.ID) {
            case 1:
                if (compareTime(startTime, req.time) && !compareTime(endTime, req.time)) {
                    if (allClients.find(req.name) != allClients.end()) {
                        queue.push(req.name);
                    } else {
                        request res = req;
                        res.ID = 13;
                        res.error = "YouShallNotPass";
                        res.name = "";
                        result.push_back(res);
                    }
                } else {
                    request res = req;
                        res.ID = 13;
                        res.error = "NotOpenYet";
                        res.name = "";
                        result.push_back(res);
                }
                break;
            case 2:
                if (computerStatuses[req.PCNumber].isFree) {

                }
            default:
                break;
            }
        }
    };
};