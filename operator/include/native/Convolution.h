//
// Created by bryab on 23-6-18.
//

#ifndef HNN_CONVOLUTION_H
#define HNN_CONVOLUTION_H
#include "Layer.h"
#include "Tensor.h"


namespace HNN {
    class Convolution : public Layer {
    public:
        ErrorCode loadParam(const ParamDict& paramDict) override;

        ErrorCode loadModel(ModelBinPtr modelBin) override;

        ErrorCode inference(TensorPtr input, TensorPtr output) override;

        uint32_t kernelWidth{0};
        uint32_t kernelHeight{0};
        uint32_t outputNum{0};
        uint32_t inputNum{0};
        uint32_t padLeft{0};
        uint32_t padRight{0};
        uint32_t padTop{0};
        uint32_t padBottom{0};
        uint32_t kernelDataSize{0};
        uint32_t biasTerm{0};
        uint32_t widthStride{0};
        uint32_t heightStride{0};
        TensorBasePtr kernel;
        TensorBasePtr bias;
    };
}

#endif //HNN_CONVOLUTION_H
