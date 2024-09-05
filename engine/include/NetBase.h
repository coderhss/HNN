//
// Created by bryab on 23-6-13.
//

#ifndef HNN_NETBASE_H
#define HNN_NETBASE_H
#include "Layer.h"
#include "ParamDict.h"
namespace HNN {

    class NetBase {
    public:
        NetBase() = default;

        virtual ~NetBase() = default;

        ErrorCode loadParam(FilePtr file);

        ErrorCode loadParam(const std::string& filePath);

        ErrorCode loadParam(DataReaderPtr dataReader);

        ErrorCode loadModel(FilePtr file);

        ErrorCode loadModel(const std::string& filePath);

        ErrorCode loadModel(DataReaderPtr dataReader);

        inline int getIndexFromBlobName(const std::string& name);

        BlobPtr getBlobFromName(const std::string& name);

        BlobPtr getBlobFromIndex(uint32_t index);

        LayerPtr getLayerFromIndex(uint32_t layerIndex);

        std::vector< BlobPtr > blobs;
        std::unordered_map< std::string, uint32_t > blobName2Index;
        std::vector< LayerPtr > layers;
    };

}
#endif //HNN_NET_H
