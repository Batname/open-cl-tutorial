#include <gtest/gtest.h>
#include <iostream>

#include "hostSample.h"

TEST(HOST_SUMPLE, VALIDATE_FUNCTION) {
    my_cl::hostSample([](cl_float* input, cl_float* output) {
        for (int i = 0; i < my_cl::NUM_VALUES; i++) {
            EXPECT_TRUE(output[i] == (input[i] * input[i]));
        }
    });
}
