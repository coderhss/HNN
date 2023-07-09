//
// Created by bryab on 23-7-8.
//
#include "Pooling.h"
namespace HNN {
    ErrorCode Pooling::loadParam(const ParamDict &paramDict) {
        return Layer::loadParam(paramDict);
    }

    ErrorCode Pooling::loadModel(ModelBinPtr modelBin) {
        return Layer::loadModel(modelBin);
    }
}
