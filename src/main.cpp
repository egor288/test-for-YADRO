#include "../include/utility.h"
#include "parser.h"
#include "taskHandler.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <input_file>\n";
        return FAIL;
    }
    return 0;
}