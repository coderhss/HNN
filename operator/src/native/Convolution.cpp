//
// Created by bryab on 23-6-18.
//

#include "Layer.h"
#include "Convolution.h"

namespace HNN {

    ErrorCode Convolution::loadParam(const ParamDict& paramDict) {
        kernelDataSize = paramDict.get(6, 0);
        biasTerm = paramDict.get(5, 0);
        outputNum = paramDict.get(0, 0);
        return ErrorCode::NN_OK;
    }

    ErrorCode Convolution::loadModel(ModelBinPtr modelBin) {
        auto tensor = modelBin->load(kernelDataSize, 0);
        if (biasTerm) {
            modelBin->load(outputNum, 1);
        }
        return ErrorCode::NN_OK;
    }

}