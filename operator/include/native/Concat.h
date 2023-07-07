//
// Created by bryab on 23-7-8.
//

#ifndef HNN_CONCAT_H
#define HNN_CONCAT_H
#include "Layer.h"
namespace HNN {
    class Concat : public Layer {
    public:
        ErrorCode loadParam(const ParamDict& paramDict) override;

        ErrorCode loadModel(ModelBinPtr modelBin) override;
    };
}
#endif //HNN_CONCAT_H
