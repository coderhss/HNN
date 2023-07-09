//
// Created by bryab on 23-7-8.
//
#include "Concat.h"
namespace HNN {
    ErrorCode Concat::loadParam(const ParamDict &paramDict) {
        return Layer::loadParam(paramDict);
    }

    ErrorCode Concat::loadModel(ModelBinPtr modelBin) {
        return Layer::loadModel(modelBin);
    }
}
