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

    ErrorCode Split::inference(std::vector<TensorPtr>& input, std::vector<TensorPtr>& output, const Config& config) {
        for (uint32_t i = 0; i < output.size(); ++i) {
            output[i] = input[0];
        }
        return ErrorCode::NN_OK;
    }
}