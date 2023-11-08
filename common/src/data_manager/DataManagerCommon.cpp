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

    void* DataManagerCommon::setPtr(void* virt, void* phy_ptr, uint32_t size) {
        if (virt == nullptr || size == 0) {
            LOG_E("set ptr err {}", size);
            return nullptr;
        }
        // 外部传入的指针不要在内部释放
        mData.reset(static_cast< uint8_t* >(virt), [](uint8_t* p) {});
        mSize = size;
        return mData.get();
    }
}