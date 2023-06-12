//
// Created by bryab on 23-5-9.
//

#ifndef HNN_ERRORCODE_H
#define HNN_ERRORCODE_H
#include <stdint.h>
namespace HNN {
    enum class ErrorCode : uint32_t {
        NN_OK,
        NN_FAILED
    };
}

#endif //HNN_ERRORCODE_H
