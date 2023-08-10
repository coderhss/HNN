//
// Created by bryab on 23-6-18.
//

#include "Layer.h"
#include "Convolution.h"

namespace HNN {

    ErrorCode Convolution::loadParam(const ParamDict& paramDict) {

        param->kernelDataSize = paramDict.get(6, 0);
        param->biasTerm = paramDict.get(5, 0);
        param->outputNum = paramDict.get(0, 1);
        param->kernelWidth = paramDict.get(1, 1);
        param->kernelHeight = paramDict.get(12, (int)param->kernelWidth);
        param->widthStride = paramDict.get(3, 1);
        param->heightStride = paramDict.get(13, (int)(param->widthStride));
        param->inputNum = param->kernelDataSize / param->kernelHeight / param->kernelWidth / param->outputNum;
        return ErrorCode::NN_OK;
    }

    ErrorCode Convolution::loadModel(ModelBinPtr modelBin) {
        param->kernel = modelBin->load(param->inputNum, param->outputNum, param->kernelHeight, param->kernelWidth, 0);
        if (param->biasTerm) {
            param->bias = modelBin->load(param->outputNum, 1);
        }
        return ErrorCode::NN_OK;
    }

    ErrorCode Convolution::inference(TensorPtr input, TensorPtr output) {
        runImpl(input, output, param);
        return Layer::inference(input, output);
    }

    ErrorCode Convolution::runImpl(HNN::TensorPtr input, HNN::TensorPtr output, std::shared_ptr<OpParam> param) {
        return ErrorCode::NN_OK;
    }

}