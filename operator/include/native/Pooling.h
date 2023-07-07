//
// Created by bryab on 23-7-8.
//

#ifndef HNN_POOLING_H
#define HNN_POOLING_H
#include "Layer.h"

namespace HNN {
    class Pooling : public Layer {
    public:
        ErrorCode loadParam(const ParamDict& paramDict) override;

        ErrorCode loadModel(ModelBinPtr modelBin) override;
    };
}

#endif //HNN_POOLING_H
