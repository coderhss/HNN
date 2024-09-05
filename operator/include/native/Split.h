//
// Created by bryab on 23-7-8.
//

#ifndef HNN_SPLIT_H
#define HNN_SPLIT_H
#include "Layer.h"
namespace HNN {
    class Split : public Layer {
    public:
        ErrorCode loadParam(const ParamDict& paramDict) override;

        ErrorCode loadModel(ModelBinPtr modelBin) override;

        ErrorCode inference(std::vector<TensorPtr>& input, std::vector<TensorPtr>& output, const Config& config) override;
    };
}

#endif //HNN_SPLIT_H
