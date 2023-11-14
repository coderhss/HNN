//
// Created by bryab on 23-7-8.
//
#include "ReLU.h"

namespace HNN {

    ErrorCode ReLU::loadParam(const ParamDict &paramDict) {

        slope = paramDict.get(0, 0.0f);

        return ErrorCode::NN_OK;
    }

    ErrorCode ReLU::loadModel(ModelBinPtr modelBin) {
        return ErrorCode::NN_OK;
    }

    ErrorCode ReLU::inference(TensorPtr input, TensorPtr& output) {
        return Layer::inference(input, output);
    }

}

