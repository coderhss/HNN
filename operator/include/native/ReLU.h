//
// Created by bryab on 23-7-8.
//

#ifndef HNN_RELU_H
#define HNN_RELU_H
#include "Layer.h"

namespace HNN {
    class ReLU : public Layer {
    public:
        ErrorCode loadParam(const ParamDict& paramDict) override;

        ErrorCode loadModel(ModelBinPtr modelBin) override;

        ErrorCode inference(TensorPtr input, TensorPtr& output) override;

        float slope{0.0};

    };
}
#endif //HNN_RELU_H
