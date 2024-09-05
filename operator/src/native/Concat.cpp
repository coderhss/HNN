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

    ErrorCode Concat::inference(std::vector<TensorPtr>& input, std::vector<TensorPtr>& output, const Config& config) {
        auto type = input[0]->getMemoryFormat();
        auto shape = input[0]->getShape();

        if (type == MemFormat::NCHW) {
            uint32_t batchSize = shape[0];
            uint32_t newChannel = shape[1];
            uint32_t newHeight = shape[2];
            uint32_t newWidth = shape[3];
            std::vector<uint32_t> strides(input.size());
            strides[0] = newChannel * newHeight * newWidth;
            for (uint32_t i = 1; i < input.size(); ++i) {
                auto tmpShape = input[i]->getShape();
                if (newHeight != tmpShape[2] || newWidth != tmpShape[3]) {
                    LOG_E("shape is not compat H: {} W: {}, H: {} W: {}", newHeight, newWidth, tmpShape[2], tmpShape[3]);
                    return ErrorCode::NN_FAILED;
                }
                newChannel += tmpShape[1];
                strides[i] = tmpShape[1] * tmpShape[2] * tmpShape[3];
            }
            ShapeVector newShape{batchSize, newChannel, newHeight, newWidth};
            output[0] = std::make_shared< Tensor >(newShape);
            float* data = output[0]->getData< float >();
            uint32_t typeSize = input[0]->getTypeSize();
            for (uint32_t n = 0; n < batchSize; ++n) {
                for (uint32_t i = 0; i < input.size(); ++i) {
                    uint32_t copySize = strides[i] * typeSize;
                    memcpy(data, input[i]->getData<float>(), copySize);
                    data += strides[i];
                }
            }
        }
        return ErrorCode::NN_OK;
    }
}
