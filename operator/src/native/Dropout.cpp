//
// Created by bryab on 23-7-8.
//
#include "Dropout.h"
namespace HNN {
    ErrorCode Dropout::loadParam(const ParamDict &paramDict) {
        return Layer::loadParam(paramDict);
    }

    ErrorCode Dropout::loadModel(HNN::ModelBinPtr modelBin) {
        return Layer::loadModel(modelBin);
    }
}
