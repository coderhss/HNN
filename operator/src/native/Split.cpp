//
// Created by bryab on 23-7-8.
//
#include "Split.h"
namespace HNN {
    ErrorCode Split::loadParam(const ParamDict &paramDict) {
        return ErrorCode::NN_OK;
    }

    ErrorCode Split::loadModel(ModelBinPtr modelBin) {
        return ErrorCode::NN_OK;
    }

    ErrorCode Split::inference(TensorPtr input, TensorPtr& output) {
        return Layer::inference(input, output);
    }
}