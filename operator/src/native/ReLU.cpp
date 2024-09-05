//
// Created by bryab on 23-7-8.
//
#include "ReLU.h"

namespace HNN {

    ErrorCode ReLU::loadParam(const ParamDict &paramDict) {

        slope = paramDict.get(0, 0.0f);

        return ErrorCode::NN_OK;
    }

    ErrorCode ReLU::loadModel(ModelBinPtr modelBin) {
        return ErrorCode::NN_OK;
    }

    ErrorCode ReLU::inference(std::vector<TensorPtr>& input, std::vector<TensorPtr>& output, const Config& config) {
        TensorPtr inputTensor = input[0];
        uint32_t num = inputTensor->getNumber();
        ShapeVector shape = inputTensor->getShape();
        float* data = inputTensor->getData< float >();
        for (uint32_t i = 0; i < num; ++i) {
            if (data[i] < 0) {
                data[i] = 0;
            }
        }
        output[0] = std::make_shared< Tensor >(data, data, shape);

        return ErrorCode::NN_OK;
    }

}

