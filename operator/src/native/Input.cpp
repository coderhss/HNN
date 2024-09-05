//
// Created by bryab on 23-6-19.
//
#include "Input.h"

namespace HNN {
    ErrorCode Input::loadParam(const ParamDict& paramDict) {
        width = paramDict.get(0, 0);
        LOG_D("Input width: {}", width);
        height = paramDict.get(1, 0);
        depth = paramDict.get(11, 0);
        channel = paramDict.get(2, 0);
        return ErrorCode::NN_OK;
    }

    ErrorCode Input::loadModel(ModelBinPtr modelBin) {
        return ErrorCode::NN_OK;
    }

    ErrorCode Input::inference(std::vector<TensorPtr>& input, std::vector<TensorPtr>& output, const Config& config) {
        uint32_t inNum = input.size();
        uint32_t outNum = output.size();
        if (inNum != outNum) {
            LOG_E("input num: {} != output num: {}", inNum, outNum);
            return ErrorCode::NN_FAILED;
        }

        for (uint32_t i = 0; i < inNum; ++i) {
            output[i] = input[i];
        }

        return ErrorCode::NN_OK;
    }
}