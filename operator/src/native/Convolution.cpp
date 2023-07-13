//
// Created by bryab on 23-6-18.
//

#include "Layer.h"
#include "Convolution.h"

namespace HNN {

    ErrorCode Convolution::loadParam(const ParamDict& paramDict) {
        kernelDataSize = paramDict.get(6, 0);
        biasTerm = paramDict.get(5, 0);
        outputNum = paramDict.get(0, 1);
        kernelWidth = paramDict.get(1, 1);
        kernelHeight = paramDict.get(12, (int)kernelWidth);
        widthStride = paramDict.get(3, 1);
        heightStride = paramDict.get(13, (int)(widthStride));
        inputNum = kernelDataSize / kernelHeight / kernelWidth / outputNum;
        return ErrorCode::NN_OK;
    }

    ErrorCode Convolution::loadModel(ModelBinPtr modelBin) {
        kernel = modelBin->load(inputNum, outputNum, kernelHeight, kernelWidth, 0);
        if (biasTerm) {
            bias = modelBin->load(outputNum, 1);
        }
        return ErrorCode::NN_OK;
    }

    ErrorCode Convolution::inference(TensorPtr input, TensorPtr output) {
        return Layer::inference(input, output);
    }

}