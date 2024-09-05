//
// Created by bryab on 23-4-14.
//

#ifndef HNN_COMMON_H
#define HNN_COMMON_H
#include <stdint.h>
#include <memory>
#include "log.h"
#include <stdlib.h>
#include "core/ErrorCode.h"
#include "core/CommonFactory.h"
#include <algorithm>
#include <cmath>
#include <float.h>

#define ALIGNMENT_32 32
typedef unsigned short float16_t;

namespace HNN {
    
void *alignedMalloc(unsigned long size, int alignment);

void alignedFree(void *aligned);

typedef enum MemoryType {
    MEM_ON_CPU,
    MEM_ON_CUDA_DEV,
    MEM_ON_CUDA_HOST
} MemoryType;

static std::unordered_map< MemoryType, std::string > DataManagerType2Name {
        {MemoryType::MEM_ON_CPU, "DataManagerCommon"},
        {MemoryType::MEM_ON_CUDA_DEV, "DataManagerCudaDev"},
        {MemoryType::MEM_ON_CUDA_HOST, "DataManagerCudaHost"}
};

}
#endif //HNN_COMMON_H
