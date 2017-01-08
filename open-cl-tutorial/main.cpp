#include <iostream>
#include <vector>
#include <cassert>

#include <OpenCL/OpenCL.h>

// #include "first.cl.h"
// or upload file

#define LOG_SIZE 128

using namespace std;

int main(int argc, const char * argv[]) {

    cl_uint platformIdCount;
    cl_uint deviceIdCount = 0;
    char logInfoBuf[LOG_SIZE];
    
    clGetPlatformIDs(1, nullptr, &platformIdCount);
    vector<cl_platform_id> platformIds(platformIdCount);
    clGetPlatformIDs(platformIdCount, platformIds.data(), nullptr);
    assert(platformIds.size() > 0);
    
    clGetDeviceIDs(platformIds[0], CL_DEVICE_TYPE_ALL, 0, nullptr, &deviceIdCount);
    vector<cl_device_id> devicesIds(platformIdCount);
    clGetDeviceIDs(platformIds[0], CL_DEVICE_TYPE_ALL, deviceIdCount, devicesIds.data(), nullptr);
    assert(devicesIds.size() > 0);
    
    for(auto &device : devicesIds) {
        clGetDeviceInfo(device, CL_DEVICE_VENDOR, LOG_SIZE, logInfoBuf, NULL);
        cout << logInfoBuf << endl;
        clGetDeviceInfo(device, CL_DEVICE_VERSION, LOG_SIZE, logInfoBuf, NULL);
        cout << logInfoBuf << endl;
    }

    return 0;
}
