//
// Created by bryab on 23-6-18.
//

#ifndef HNN_CONVOLUTION_H
#define HNN_CONVOLUTION_H
#include "Layer.h"


namespace HNN {
    class Convolution : public Layer {
    public:
        ErrorCode loadParam(ParamDict& paramDict) override;

        uint32_t kernelWidth{0};
        uint32_t kernelHeight{0};
        uint32_t padLeft{0};
        uint32_t padRight{0};
        uint32_t padTop{0};
        uint32_t padBottom{0};
        std::unique_ptr< Tensor > kernel;
    };
}

#endif //HNN_CONVOLUTION_H
