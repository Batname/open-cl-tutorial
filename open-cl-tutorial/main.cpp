#include "CLProgram.hpp"

int main(int argc, const char * argv[]) {

    CLProgram myProgram("processArray.cl");
    char logBuffer[CLProgram::LOG_SIZE];
    myProgram.executeProgram("processArray", logBuffer);
    std::cout << logBuffer << std::endl;
    return 0;
}
