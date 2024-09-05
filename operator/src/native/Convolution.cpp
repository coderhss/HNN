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
        param->dilationWidth = paramDict.get(2, 1);
        param->dilationHeight = paramDict.get(12, (int)param->dilationWidth);
        param->padLeft = paramDict.get(4, 0);
        param->padRight = paramDict.get(15, (int32_t)param->padLeft);
        param->padTop = paramDict.get(14, (int32_t)param->padLeft);
        param->padBottom = paramDict.get(16, (int32_t)param->padTop);
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

    ErrorCode Convolution::inference(std::vector<TensorPtr>& input, std::vector<TensorPtr>& output, const Config& config) {

        return runImpl(input, output, config);
    }

    ErrorCode Convolution::runImpl(std::vector<TensorPtr>& input, std::vector<TensorPtr>& output, const Config& config) {
        TensorPtr tensorBoarded;
        makePadding(input[0], tensorBoarded, config);
        ShapeVector boardShape = tensorBoarded->getShape();
        uint32_t N = boardShape[0], C = boardShape[1], inH = boardShape[2], inW = boardShape[3]; 
        uint32_t outW = (inW - param->kernelWidth) / param->widthStride + 1;
        uint32_t outH = (inH - param->kernelHeight) / param->heightStride + 1;
        uint32_t outC = param->outputNum;
        ShapeVector outShape = {N, outC, outH, outW};
        output[0] = std::make_shared< Tensor >(outShape);

        float* weight = param->kernel->getData< float >();
        float* inputTensor = tensorBoarded->getData< float>();
        float* outputTensor = output[0]->getData< float >();
        uint32_t maxk = param->kernelHeight * param->kernelWidth;
        std::vector<int> spaceOffset(maxk);
        {
            int p1 = 0;
            int p2 = 0;
            int gap = inW - param->kernelWidth;
            for (int i = 0; i < param->kernelHeight; i++) {
                for (int j = 0; j < param->kernelWidth; j++) {
                    spaceOffset[p1] = p2;
                    p1++;
                    p2++;
                }
                p2 += gap;
            }
        }
        float* bias = param->bias->getData<float>();
        for (uint32_t n = 0; n < N; ++n) {
            float* perTensor = inputTensor + n * C * inH * inW;
            float* perOutTensor = outputTensor + n * outC * outH * outW;
            #pragma omp parallel for num_threads(4)
            for (uint32_t c = 0; c < outC; ++c) {
                float* outPerChanelTensor = perOutTensor + c * outH * outW;
                for (uint32_t h = 0; h < outH; ++h) {
                    for (uint32_t w = 0; w < outW; ++w) {
                        float sum = 0.0f;
                        if (param->biasTerm) {
                            sum = bias[c];
                        }
                        float* kernel = weight + c * maxk * param->inputNum;
                        for (uint32_t inc = 0; inc < param->inputNum; ++inc) {
                            float* perChannelTensor = perTensor + inc * inH * inW;
                            float* perPatchTensor = perChannelTensor + h * param->heightStride * inW + w * param->widthStride;
                            for (uint32_t k = 0; k < maxk; ++k) {
                                sum += kernel[k] * perPatchTensor[spaceOffset[k]];
                            }
                            kernel += maxk;
                        }
                        outPerChanelTensor[w] = sum;
                    }
                    outPerChanelTensor += outW;
                }
            }
        }
        
        return ErrorCode::NN_OK;
    }

    ErrorCode Convolution::makePadding(TensorPtr& input, TensorPtr& output, const Config& config) {
        auto shape = input->getShape();
        uint32_t N = shape[0];
        uint32_t C = shape[1];
        uint32_t H = shape[2];
        uint32_t W = shape[3];

        if (param->padLeft > 0 || param->padRight || param->padBottom || param->padTop) {
            uint32_t newW = W + param->padLeft + param->padRight;
            uint32_t newH = H + param->padTop + param->padBottom;
            ShapeVector shape = {N, C, newH, newW};
            uint32_t head = newW * param->padTop;
            uint32_t tail = newW * param->padBottom;
            TensorPtr tensor = std::make_shared< Tensor >(shape);
            float* src = input->getData< float >();

            float* dst = tensor->getData< float >();
            for (uint32_t n = 0; n < N; ++n) {
                // dst += n * C * newH * newW;
                // src += n * C * H * W;
                uint32_t dst_o = 0;
                uint32_t src_o = 0;
                for (uint32_t c = 0; c < C; ++c) {
                    dst_o = c * newH * newW;
                    src_o = c * H * W;
                    for (uint32_t i = 0; i < H; ++i) {
                        memcpy(dst + dst_o + head + newW * i + param->padLeft, src + src_o + W * i, W * 4);
                    }
                }
            }
            output = tensor;
        } else {
            output = input;
        }

        return ErrorCode::NN_OK;
    }

}