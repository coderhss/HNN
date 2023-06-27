//
// Created by bryab on 23-6-13.
//

#ifndef HNN_NET_H
#define HNN_NET_H
#include "Layer.h"
#include "ParamDict.h"
namespace HNN {

    class Net {
    public:
        Net() = default;

        virtual ~Net() = default;

        ErrorCode loadParam(FilePtr file);

        ErrorCode loadParam(const std::string& filePath);

        ErrorCode loadParam(DataReaderPtr dataReader);

        ErrorCode loadModel(FilePtr file);

        ErrorCode loadModel(const std::string& filePath);

        ErrorCode loadModel(DataReaderPtr dataReader);

        inline int getIndexFromBlobName(const std::string& name);

        inline BlobPtr getBlobFromName(const std::string& name);

        std::vector< BlobPtr > blobs;
        std::unordered_map< std::string, uint32_t > blobName2Index;
        std::vector< LayerPtr > layers;
    };

}
#endif //HNN_NET_H
