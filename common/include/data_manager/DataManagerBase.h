//
// Created by bryab on 23-4-14.
//

#ifndef HNN_DATAMANAGERBASE_H
#define HNN_DATAMANAGERBASE_H
#include "common.h"

namespace HNN {

    class DataManagerBase {
    public:
        virtual ~DataManagerBase(){}
        virtual void* malloc(const uint32_t size) = 0;
        virtual void free(void* p) = 0;
    };
    using DataManagerBasePtr = std::shared_ptr< DataManagerBase >;
}

#endif //HNN_DATAMANAGERBASE_H
