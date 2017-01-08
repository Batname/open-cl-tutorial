#ifndef printDevices_h
#define printDevices_h

#include <iostream>
#include <vector>
#include <cassert>

#include <OpenCL/OpenCL.h>

// #include "first.cl.h"
// or upload file

using namespace std;

void printDevices() {
    int LOG_SIZE = 128;
    cl_uint platformIdCount;
    cl_uint deviceIdCount = 0;
    char logInfoBuf[LOG_SIZE];
    
    clGetPlatformIDs(1, nullptr, &platformIdCount);
    vector<cl_platform_id> platformIds(platformIdCount);
    clGetPlatformIDs(platformIdCount, platformIds.data(), nullptr);
    assert(platformIds.size() > 0);
    
    clGetDeviceIDs(platformIds[0], CL_DEVICE_TYPE_ALL, 0, NULL, &deviceIdCount);
    // cl_device_id* devicesIds = (cl_device_id*)calloc(sizeof(cl_device_id), deviceIdCount);
    vector<cl_device_id> devicesIds(deviceIdCount);
    clGetDeviceIDs(platformIds[0], CL_DEVICE_TYPE_ALL, deviceIdCount, devicesIds.data(), NULL);
    
    assert(devicesIds.size() > 0);
    
    for(auto &device : devicesIds) {
        clGetDeviceInfo(device, CL_DEVICE_NAME, LOG_SIZE, logInfoBuf, NULL);
        cout << logInfoBuf << endl;
        clGetDeviceInfo(device, CL_DEVICE_VERSION, LOG_SIZE, logInfoBuf, NULL);
        cout << logInfoBuf << endl;
    }
}

#endif /* printDevices_h */
