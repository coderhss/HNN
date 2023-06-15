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

        ErrorCode loadParam(DataReaderPtr dataReader);

        std::vector< Blob > blobs;
        std::vector< Layer > layers;
    };

}
#endif //HNN_NET_H
