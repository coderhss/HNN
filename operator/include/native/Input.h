//
// Created by bryab on 23-6-19.
//

#ifndef HNN_INPUT_H
#define HNN_INPUT_H
#include "Layer.h"
namespace HNN {
    class Input : public Layer {
    public:
        ErrorCode loadParam(const ParamDict& paramDict) override;

        ErrorCode loadModel(ModelBinPtr modelBin) override;

        uint32_t width{0};
        uint32_t height{0};
        uint32_t depth{0};
        uint32_t channel{0};
    };
}
#endif //HNN_INPUT_H
