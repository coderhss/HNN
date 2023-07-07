//
// Created by bryab on 23-7-8.
//
#include "Softmax.h"
namespace HNN {
    ErrorCode Softmax::loadParam(const ParamDict &paramDict) {
        return Layer::loadParam(paramDict);
    }

    ErrorCode Softmax::loadModel(HNN::ModelBinPtr modelBin) {
        return Layer::loadModel(modelBin);
    }
}
