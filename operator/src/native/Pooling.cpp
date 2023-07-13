//
// Created by bryab on 23-7-8.
//
#include "Pooling.h"
namespace HNN {
    ErrorCode Pooling::loadParam(const ParamDict &paramDict) {
        return ErrorCode::NN_OK;
    }

    ErrorCode Pooling::loadModel(ModelBinPtr modelBin) {
        return ErrorCode::NN_OK;
    }

    ErrorCode Pooling::inference(TensorPtr input, TensorPtr output) {
        return Layer::inference(input, output);
    }
}
