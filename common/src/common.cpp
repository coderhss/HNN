//
// Created by bryab on 23-4-16.
//
#include "common.h"
#include <mutex>

static std::mutex mtx;
void *alignedMalloc(unsigned long size, int alignment) {
    const int pointerSize = sizeof(void *);
    const int requestSize = size + alignment - 1 + pointerSize;
    void *raw = malloc(requestSize);
    if (raw == nullptr) {
        LOG_E("aligned malloc is null.");
        return nullptr;
    }
    void** aligned = (void **)(((size_t)raw + alignment - 1 + pointerSize) & ~(alignment - 1));
    if (aligned == nullptr) {
        LOG_E("aligned malloc aligned ptr is null.");
        return nullptr;
    }
    aligned[-1] = raw;
    return aligned;
}

void alignedFree(void *aligned) {
    std::unique_lock< std::mutex >lck(mtx);
    if (aligned == nullptr) {
        LOG_W("aligned mem free aligned pointer is null.");
        return;
    }
    void* raw = ((void**)aligned)[-1];
    if (raw != nullptr) {
        free(raw);
    } else {
        LOG_W("aligned mem free raw pointer is null.");
    }
    aligned = nullptr;
}