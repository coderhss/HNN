//
// Created by bryab on 23-7-8.
//
#include "Dropout.h"
namespace HNN {
    ErrorCode Dropout::loadParam(const ParamDict &paramDict) {

        scale = paramDict.get(0, 1.0f);

        return ErrorCode::NN_OK;
    }

    ErrorCode Dropout::loadModel(ModelBinPtr modelBin) {
        return ErrorCode::NN_OK;
    }

    ErrorCode Dropout::inference(std::vector<TensorPtr>& input, std::vector<TensorPtr>& output, const Config& config) {
        if (scale == 1.0f) {
            output[0] = input[0];
        }
        return ErrorCode::NN_OK;
    }
}
