//
// Created by bryab on 23-5-11.
//

#ifndef HNN_DATATYPE_H
#define HNN_DATATYPE_H
#include <stdint.h>
#include <cstddef>

namespace HNN {
    enum class DataType : uint32_t{
        HNN_NONE        = 0,
        HNN_BYTE        = 1,
        HNN_BOOL        = 2,

        HNN_INT8,
        HNN_INT16,
        HNN_INT32,

        HNN_UINT8,
        HNN_UINT16,
        HNN_UINT32,

        HNN_FLOAT16,
        HNN_FLOAT32,
    };

    inline size_t GetTypeSize(DataType& dataType) {
        switch (dataType) {

            case DataType::HNN_BYTE:
                return 1;
            case DataType::HNN_BOOL:
                return 1;
            case DataType::HNN_INT8:
                return 1;
            case DataType::HNN_INT16:
                return 2;
            case DataType::HNN_INT32:
                return 4;
            case DataType::HNN_UINT8:
                return 1;
            case DataType::HNN_UINT16:
                return 2;
            case DataType::HNN_UINT32:
                return 4;
            case DataType::HNN_FLOAT16:
                return 2;
            case DataType::HNN_FLOAT32:
                return 4;
            default:
                return 0;
        }
    }
}
#endif //HNN_DATATYPE_H
