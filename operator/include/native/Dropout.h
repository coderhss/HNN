//
// Created by bryab on 23-7-8.
//

#ifndef HNN_DROPOUT_H
#define HNN_DROPOUT_H
#include "Layer.h"

namespace HNN {
    class Dropout : public Layer {
    public:
        ErrorCode loadParam(const ParamDict& paramDict) override;

        ErrorCode loadModel(ModelBinPtr modelBin) override;

        ErrorCode inference(std::vector<TensorPtr>& input, std::vector<TensorPtr>& output, const Config& config) override;

        float scale{0.0};
    };
}

#endif //HNN_DROPOUT_H
