//
// Created by bryab on 23-6-18.
//

#ifndef HNN_CONVOLUTION_H
#define HNN_CONVOLUTION_H
#include "Layer.h"


namespace HNN {
    class Convolution : public Layer {
        ErrorCode loadParam(ParamDict& paramDict) override;
    };
}

#endif //HNN_CONVOLUTION_H
