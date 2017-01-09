#ifndef hostSample_h
#define hostSample_h

#include <stdio.h>
#include <stdlib.h>
#include <OpenCL/opencl.h>

#include "hostSampleKernel.cl.h"

namespace my_cl {
    enum {
        NUM_VALUES = 1024
    };
    
    typedef void (*Validator)(cl_float* input, cl_float* output);
    
    void hostSample(Validator validate = NULL) {
        int i;
        char name[128];
        
        dispatch_queue_t queue = gcl_create_dispatch_queue(CL_DEVICE_TYPE_GPU, NULL);
        
        if (queue == NULL) {
            queue = gcl_create_dispatch_queue(CL_DEVICE_TYPE_CPU, NULL);
        }
        
        cl_device_id gpu = gcl_get_device_id_with_dispatch_queue(queue);
        clGetDeviceInfo(gpu, CL_DEVICE_NAME, 128, name, NULL);
        fprintf(stdout, "Create dispatch queue using the %s\n", name);
        
        float* test_in = (float*)malloc(sizeof(cl_float) * NUM_VALUES);
        for(i = 0; i < NUM_VALUES; i++) {
            test_in[i] = (cl_float)i;
        }
        
        float* test_out = (float*)malloc(sizeof(cl_float) * NUM_VALUES);
        
        void* mem_in  = gcl_malloc(sizeof(cl_float) * NUM_VALUES, test_in, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR);
        void* mem_out = gcl_malloc(sizeof(cl_float) * NUM_VALUES, NULL, CL_MEM_WRITE_ONLY);
        
        dispatch_sync(queue, ^{
            size_t wgs;
            gcl_get_kernel_block_workgroup_info(square_kernel,
                                                CL_KERNEL_WORK_GROUP_SIZE,
                                                sizeof(wgs), &wgs, NULL);
            
            cl_ndrange range = {
                1, {0, 0, 0}, {NUM_VALUES, 0, 0}, {wgs, 0, 0}
            };
            
            square_kernel(&range,(cl_float*)mem_in, (cl_float*)mem_out);
            
            gcl_memcpy(test_out, mem_out, sizeof(cl_float) * NUM_VALUES);
        });
        
        if (validate != NULL) validate(test_in, test_out);
        
        gcl_free(mem_in);
        gcl_free(mem_out);
        
        free(test_in);
        free(test_out);
        
        dispatch_release(queue);
    }
}


#endif /* hostSample_h */
