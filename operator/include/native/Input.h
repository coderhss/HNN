//
// Created by bryab on 23-6-19.
//

#ifndef HNN_INPUT_H
#define HNN_INPUT_H
#include "Layer.h"
namespace HNN {
    class Input : public Layer {

        ErrorCode loadParam() override;
    };
}
#endif //HNN_INPUT_H
