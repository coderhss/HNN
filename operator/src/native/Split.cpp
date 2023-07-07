//
// Created by bryab on 23-7-8.
//
#include "Split.h"
namespace HNN {
    ErrorCode Split::loadParam(const ParamDict &paramDict) {
        return Layer::loadParam(paramDict);
    }

    ErrorCode Split::loadModel(HNN::ModelBinPtr modelBin) {
        return Layer::loadModel(modelBin);
    }
}