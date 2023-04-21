//
// Created by bryab on 23-4-21.
//
#include "DataManagerCommon.h"

namespace HNN {
    void *DataManagerCommon::malloc(const uint32_t size) {
        void *newPointer = alignedMalloc(size, ALIGNMENT_32);
        if (newPointer == nullptr) {
            LOG_E("fast malloc ptr is null.");
        }
        return newPointer;
    }

    void DataManagerCommon::free(void *pointer) {
        std::unique_lock< std::mutex > lck(mtx);
        if (pointer == nullptr) {
            LOG_W("fast free ptr is null.");
        }
        alignedFree(pointer);
        pointer = nullptr;
    }
}