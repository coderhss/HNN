//
// Created by bryab on 23-4-16.
//
#include "Allocator.h"
#include "common.h"

namespace HNN {

    void* Allocator::fastMalloc(int size) {
        void *newPointer = alignedMalloc(size, ALIGNMENT_32);
        if (newPointer == nullptr) {
            LOG_E("fast malloc ptr is null.");
        }
        return newPointer;
    }

    void Allocator::fastFree(void *pointer) {
        std::unique_lock< std::mutex > lck(mtx);
        if (pointer == nullptr) {
            LOG_W("fast free ptr is null.");
            return;
        }
        alignedFree(pointer);
        pointer = nullptr;
    }
}