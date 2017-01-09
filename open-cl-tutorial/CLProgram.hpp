#ifndef CLProgram_hpp
#define CLProgram_hpp

#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <sstream>

#include <OpenCL/OpenCL.h>

class CLProgram {
public:
    enum Constants {
        MEM_SIZE = 128,
        LOG_SIZE = 128,
        MAX_SOURCE_SIZE = 0x100000
    };
    
    CLProgram(const char * progtamFilePath);
    ~CLProgram();
    
    void executeProgram(const char* programName, char* logBuffer);
private:
    cl_device_id device_id = NULL;
    cl_context context = NULL;
    cl_command_queue command_queue = NULL;
    cl_mem memobj = NULL;
    cl_program program = NULL;
    cl_kernel kernel = NULL;
    cl_platform_id platform_id = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret;
};

#endif /* CLProgram_hpp */
