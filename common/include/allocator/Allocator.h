//
// Created by bryab on 23-4-16.
//

#ifndef HNN_ALLOCATOR_H
#define HNN_ALLOCATOR_H

#include <cstdlib>
#include <mutex>

namespace HNN {
    class Allocator {
    public:
        Allocator() = default;
        virtual ~Allocator(){};
        virtual void* fastMalloc(int size);
        virtual void fastFree(void *pointer);

    private:
        std::mutex mtx;
    };
}

#endif //HNN_ALLOCATOR_H