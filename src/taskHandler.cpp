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

int timeDif(const std::string& time1, const std::string& time2) {
    size_t pos1 = time1.find(':');
    size_t pos2 = time2.find(':');
    

    int hours1 = std::stoi(time1.substr(0, pos1));
    int minutes1 = std::stoi(time1.substr(pos1 + 1));
    int hours2 = std::stoi(time2.substr(0, pos2));
    int minutes2 = std::stoi(time2.substr(pos2 + 1));

    // Преобразование времени в общее количество минут
    int startTotalMinutes = hours1 * 60 + minutes1;
    int endTotalMinutes = hours2 * 60 + minutes2;

    // Если time2 меньше time1, это значит, что time2 находится на следующий день
    if (endTotalMinutes < startTotalMinutes) {
        endTotalMinutes += 24 * 60; // Добавляем 24 часа в минуты
    }
    return endTotalMinutes - startTotalMinutes; // Возвращаем разницу в минутах
}

bool isNameInQueue(std::queue<std::string> q, const std::string& name) {
    while (!q.empty()) {
        if (q.front() == name) {
            return true;
        }
        q.pop();
    }
    return false;
}

    taskHandler::taskHandler() : price(-1), tableCount(-1) {}
    taskHandler::taskHandler(std::vector<request>& requests, int price, int tableCount, std::string startTime, std::string endTime) 
    : requests(requests), price(price), tableCount(tableCount), startTime(startTime), endTime(endTime) {
        computerStatuses.reserve(tableCount);
        for (int i = 0; i < tableCount; i++) {
            computerStatuses.push_back(computerStatus(i + 1));
        }
    }

    bool taskHandler::ifAnyFree() {
        for (computerStatus computer : this->computerStatuses) {
            if (computer.isFree) {
                return true;
            }
        }
        return false;
    }

    bool taskHandler::ifInPlace(std::string name) {
        for (computerStatus computer : this->computerStatuses) {
            if (computer.clientName == name) {
                return true;
            }
        }
        return isNameInQueue(this->queue, name);
    }

    int taskHandler::countTime(std::string name) {
        std::string start = "", end = "";
        for (request event : result) {
            if (event.name == name && (event.ID == 2 || event.ID == 12)) 
                start = event.time;
            if (event.name == name && (event.ID == 4 || event.ID == 11)) {
                end = event.time;
                break;
            }
        }
        return timeDif(start, end);
    }

    returnCode taskHandler::executeTasks() {
        for(request req : requests) {
            switch (req.ID) {
            case 1:
                result.push_back(req);
                if (compareTime(startTime, req.time) && !compareTime(endTime, req.time)) {
                    if (allClients.find(req.name) == allClients.end()) {
                        queue.push(req.name);
                        allClients[req.name] = 0;
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
                result.push_back(req);
                if (isNameInQueue(queue, req.name)) {
                    if (computerStatuses[req.PCNumber -1].isFree) {
                        queue.pop();
                        computerStatuses[req.PCNumber - 1].clientName = req.name;
                        computerStatuses[req.PCNumber - 1].isFree = false;
                        allClients[req.name] = req.PCNumber;
                    } else {
                        request res = req;
                        res.ID = 13;
                        res.error = "PlaceIsBusy";
                        res.name = "";
                        result.push_back(res);
                    }
                } else {
                    request res = req;
                    res.ID = 13;
                    res.error = "ClientUnknown";
                    res.name = "";
                    result.push_back(res);
                }
                break;
            case 3:
                result.push_back(req);
                if (ifAnyFree()) {
                    request res = req;
                    res.ID = 13;
                    res.error = "ICanWaitNoLonger!";
                    res.name = "";
                    result.push_back(res);
                } else if (queue.size() > tableCount) {
                    request res = req;
                    res.ID = 11;
                    result.push_back(res);
                }
                break;
            case 4:
                result.push_back(req);
                if (ifInPlace(req.name)) {
                    for (computerStatus& computer : computerStatuses) {
                        if (computer.clientName == req.name) {
                            computer.clientName = "";
                            computer.isFree = true;
                            computer.totalTime += countTime(req.name);
                            computer.totalRevenu += price * std::ceil(static_cast<float>(countTime(req.name)) / 60);
                            break;
                        }
                    }
                    if (!queue.empty()) {
                        request res = req;
                        res.ID = 12;
                        res.name = queue.front();
                        queue.pop();
                        res.PCNumber = allClients[result.back().name];
                        allClients[res.name] = req.PCNumber;
                        computerStatuses[res.PCNumber - 1].clientName = res.name;
                        computerStatuses[res.PCNumber - 1].isFree = false;
                        result.push_back(res);
                    }
                } else {
                    request res = req;
                    res.ID = 13;
                    res.error = "ClientUnknown";
                    res.name = "";
                    result.push_back(res);
                }
                break;

            default:
                return PARSER_ERROR;
            }
        }
        freeAll();
        return SUCCESS;
    };

    returnCode taskHandler::freeAll() {
        for (computerStatus& computer : computerStatuses) {
            if (!computer.isFree) {
                request res;
                res.ID = 11;
                res.name = computer.clientName;
                res.time = endTime;
                result.push_back(res);
                computer.clientName = "";
                computer.isFree = true;
                computer.totalTime += countTime(res.name);
                computer.totalRevenu += price * std::ceil(static_cast<float>(countTime(res.name)) / 60);
            }
        }
        return SUCCESS;
    }

    std::vector<computerStatus> taskHandler::returnComputers() {
        return computerStatuses;
    }

    std::vector<request> taskHandler::retrunResult() {
        return result;
    }