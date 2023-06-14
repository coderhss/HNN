//
// Created by bryab on 23-6-13.
//

#ifndef HNN_NET_H
#define HNN_NET_H
#include "Layer.h"
namespace HNN {

    class Net {
    public:
        Net() = default;

        virtual ~Net() = default;

        ErrorCode loadParam(FilePtr file);

        ErrorCode loadParam(const std::string& filePath);

    };

}
#endif //HNN_NET_H
