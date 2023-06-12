//
// Created by bryab on 23-6-12.
//

#ifndef HNN_LAYER_H
#define HNN_LAYER_H
#include "Blob.h"
namespace HNN {
    class Layer {
    public:
        Layer();

        virtual ~Layer(){};

        virtual ErrorCode load_param() = 0;


    };
}
#endif //HNN_LAYER_H
