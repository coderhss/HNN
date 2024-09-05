//
// Created by bryab on 23-6-12.
//
#include "Layer.h"

namespace HNN {
    ErrorCode Layer::loadParam(const ParamDict& paramDict) {
        return ErrorCode::NN_OK;
    }

    ErrorCode Layer::loadModel(ModelBinPtr modelBin) {
        return ErrorCode::NN_FAILED;
    }

    ErrorCode Layer::inference(std::vector<TensorPtr>& input, std::vector<TensorPtr>& output, const Config& config) {
        return ErrorCode::NN_FAILED;
    }
}