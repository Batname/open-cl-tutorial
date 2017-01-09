#include "CLProgram.hpp"

using namespace std;

CLProgram::CLProgram(const char * progtamFilePath) {
    char logBuf[LOG_SIZE];
    
    FILE *fp;
    char* sourceCode;
    size_t sourceSize;
    
    /* Load the source file code from text file */
    fp = fopen(progtamFilePath, "r");
    assert(fp && "Failed to open file");
    sourceCode = (char*)malloc(MAX_SOURCE_SIZE);
    sourceSize = fread(sourceCode, 1, MAX_SOURCE_SIZE, fp);
    fclose(fp);
    
    /* Get platform and Device info */
    ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
    
    assert(ret_num_devices > 0);
    
    /* print device info */
    clGetDeviceInfo(device_id, CL_DEVICE_NAME, LOG_SIZE, logBuf, NULL);
    cout << logBuf << endl;
    clGetDeviceInfo(device_id, CL_DEVICE_VERSION, LOG_SIZE, logBuf, NULL);
    cout << logBuf << endl;
    
    /* Create OpenCL context */
    context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
    
    /* Create Command Queue */
    command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
    
    /* Create memory buffer */
    memobj = clCreateBuffer(context, CL_MEM_READ_WRITE,MEM_SIZE * sizeof(char), NULL, &ret);

    /* Create Kernel Program from the source */
    program = clCreateProgramWithSource(context, 1, (const char**)&sourceCode, (const size_t*)&sourceSize, &ret);
    
    /* Build Kernel Program */
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
    
    free(sourceCode);
}

void CLProgram::executeProgram(const char* programName, char* logBuffer) {
    
    /* Create OpenCL Kernel */
    kernel = clCreateKernel(program, programName, &ret);
    
    /* Set OpenCL Kernel Parameters */
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj);
    
    /* Execute OpenCL Kernel */
    ret = clEnqueueTask(command_queue, kernel, 0, NULL,NULL);
    
    /* Copy results from the memory buffer */
    ret = clEnqueueReadBuffer(command_queue, memobj, CL_TRUE, 0,
                              MEM_SIZE * sizeof(char), logBuffer, 0, NULL, NULL);
}


CLProgram::~CLProgram() {
    /* Finalization */
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(memobj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
}
