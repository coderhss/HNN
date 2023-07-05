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
        mSize = size;
        mData.reset((uint8_t*)newPointer, [&](uint8_t* p) {
            alignedFree(p);
            mSize = 0;
        });
        return newPointer;
    }

    void DataManagerCommon::free(void *pointer) {
        if (pointer == nullptr) {
            LOG_W("fast free ptr is null.");
        }
        mSize = 0;
        alignedFree(pointer);
        pointer = nullptr;
    }
}