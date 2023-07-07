//
// Created by bryab on 23-7-8.
//
#include "ReLU.h"

namespace HNN {

    ErrorCode ReLU::loadParam(const ParamDict &paramDict) {
        return Layer::loadParam(paramDict);
    }

    ErrorCode ReLU::loadModel(HNN::ModelBinPtr modelBin) {
        return Layer::loadModel(modelBin);
    }

}

