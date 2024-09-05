#ifndef HNN_EXECUTER_H
#define HNN_EXECUTER_H
#include "common.hpp"
#include "Tensor.h"
#include "NetBase.h"


namespace HNN {

    class Executer {
    public:

        Executer(NetBase* net) : net(net) {
            featureMaps.resize(net->blobs.size());
        };

        ErrorCode input(std::string name, TensorPtr& tensor);

        ErrorCode forward();

        ErrorCode getBlob(std::string blobName, TensorPtr& tensor, Config& config);

        ErrorCode dfsForword(uint32_t blobIndex, Config& config);

        ErrorCode dumpAllTensor(std::string& path);

        std::vector< TensorPtr > featureMaps;

    private:
        NetBase* net{nullptr};
    };
    
} // namespace HNN

#endif