//
// Created by bryab on 23-6-12.
//

#ifndef HNN_BLOB_H
#define HNN_BLOB_H
#include <string>
#include "common.h"
#include "DataReader.h"
namespace HNN {
    class Blob {
    public:
        Blob();
        std::string name;
        int producer;
        int consumer;

    };
}
#endif //HNN_BLOB_H
