#include <utility>
#include "parser.h"
#include "taskHandler.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <input_file>\n";
        return FAIL;
    }

    std::vector<request> requests;
    int price, tableCount;
    std::string startTime, endTime;
    returnCode result = parseFile(argv[1], requests, price, tableCount, startTime, endTime);
    if (result == FILE_ERROR) {
        std::cout << "Error: File not found\n";
        return result;
    }
    if (result == PARSER_ERROR) {
        std::cout << "Error: Parser error\n";
        return result;
    }

    taskHandler* tasks = new taskHandler(requests, price, tableCount, startTime, endTime);
    tasks->executeTasks();
    std::vector<request> res = tasks->retrunResult();
    std::vector<computerStatus> computers = tasks->returnComputers();

    std::cout << startTime << '\n';
    for (request ans : res) {
       std::cout << ans.time << ' ' << ans.ID << ' ' << ans.name << ' ';
        if (ans.PCNumber > 0 && ans.ID != 13) {
            std::cout << ans.PCNumber << ' ';
        }
        std::cout << ans.error << '\n';
    }

    std::cout << endTime << '\n';

    for (computerStatus computer : computers) {
        std::cout << computer.PCNumber << ' ' 
              << computer.totalRevenu << ' ' 
              << std::setw(2) << std::setfill('0') << computer.totalTime / 60 << ':' 
              << std::setw(2) << std::setfill('0') << computer.totalTime % 60 << '\n';

    }
    
    return 0;
}