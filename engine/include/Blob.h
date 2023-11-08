//
// Created by bryab on 23-6-12.
//

#ifndef HNN_BLOB_H
#define HNN_BLOB_H
#include <string>
#include "common.hpp"
#include "DataReader.h"
namespace HNN {
    class Blob {
    public:
        Blob();
        std::string name;
        int producer;
        int consumer;

    };
    using BlobPtr = std::shared_ptr< Blob >;
}
#endif //HNN_BLOB_H
