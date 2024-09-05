//
// Created by bryab on 23-7-8.
//
#include "Softmax.h"
#include "common.hpp"
namespace HNN {
    ErrorCode Softmax::loadParam(const ParamDict &paramDict) {

        axis = paramDict.get(0, 0);

        return ErrorCode::NN_OK;
    }

    ErrorCode Softmax::loadModel(ModelBinPtr modelBin) {
        return ErrorCode::NN_OK;
    }

    ErrorCode Softmax::inference(std::vector<TensorPtr>& input, std::vector<TensorPtr>& output, const Config& config) {
        ShapeVector inShape = input[0]->getShape();
        output[0] = std::make_shared< Tensor >(inShape);
        uint32_t N = inShape[0], C = inShape[1], H = inShape[2], W = inShape[3];
        float* in = input[0]->getData<float>();
        float* out = output[0]->getData<float>();
        for (uint32_t n = 0; n < N; ++n) {
            float* inBatchPtr = in + n * C * H * W;
            float* outBatchPtr = out + n * C * H * W;
            float max = -FLT_MAX;
            float sum = 0;
            for (uint32_t c = 0; c < C; ++c) {
                max = std::max(max, *(inBatchPtr + c));
            }

            for (uint32_t c = 0; c < C; ++c) {
                outBatchPtr[c] = expf(*(inBatchPtr + c) - max);
                sum += outBatchPtr[c];
            }

            for (uint32_t c = 0; c < C; ++c) {
                outBatchPtr[c] /= sum;
            }
        }
        return ErrorCode::NN_OK;
    }
}
