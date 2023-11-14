//
// Created by bryab on 23-7-8.
//
#include "Concat.h"
namespace HNN {
    ErrorCode Concat::loadParam(const ParamDict &paramDict) {

        axis = paramDict.get(0, 0);

        return ErrorCode::NN_OK;
    }

    ErrorCode Concat::loadModel(ModelBinPtr modelBin) {
        return ErrorCode::NN_OK;
    }

    ErrorCode Concat::inference(TensorPtr input, TensorPtr& output) {
        return Layer::inference(input, output);
    }
}
