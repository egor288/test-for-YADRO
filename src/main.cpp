#include "../include/utility.h"
#include "parser.h"
#include "taskHandler.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <input_file>\n";
        return FAIL;
    }

    std::vector<request> requests;
    int price, tableCount;
    std::string sartTime, endTime;
    returnCode result = parseFile(argv[1], requests, price, tableCount, sartTime, endTime);
    if (result == FILE_ERROR) {
        std::cout << "Error: File not found\n";
        return result;
    }
    if (result == PARSER_ERROR) {
        std::cout << "Error: Parser error\n";
        return result;
    }
    
    return 0;
}