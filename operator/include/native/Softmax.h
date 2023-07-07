//
// Created by bryab on 23-7-8.
//

#ifndef HNN_SOFTMAX_H
#define HNN_SOFTMAX_H
#include "Layer.h"
namespace HNN {
    class Softmax : public Layer {
    public:
        ErrorCode loadParam(const ParamDict& paramDict) override;

        ErrorCode loadModel(ModelBinPtr modelBin) override;
    };
}

#endif //HNN_SOFTMAX_H
