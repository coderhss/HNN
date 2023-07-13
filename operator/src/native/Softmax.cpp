//
// Created by bryab on 23-7-8.
//
#include "Softmax.h"
namespace HNN {
    ErrorCode Softmax::loadParam(const ParamDict &paramDict) {

        axis = paramDict.get(0, 0);

        return ErrorCode::NN_OK;
    }

    ErrorCode Softmax::loadModel(ModelBinPtr modelBin) {
        return ErrorCode::NN_OK;
    }

    ErrorCode Softmax::inference(TensorPtr input, TensorPtr output) {
        return Layer::inference(input, output);
    }
}
