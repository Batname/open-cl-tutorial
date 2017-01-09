#include "CLProgram.hpp"

int main(int argc, const char * argv[]) {

    CLProgram myProgram("processArray.cl");
    std::cout << myProgram.executeProgram("processArray") << std::endl;
    return 0;
}
