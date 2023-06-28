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
        return Layer::loadModel(modelBin);
    }
}