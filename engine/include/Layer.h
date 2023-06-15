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

        virtual ErrorCode load_param();

        std::string type;

        std::string name;

        std::vector< uint32_t > bottoms;

        std::vector< uint32_t > tops;
    };
}
#endif //HNN_LAYER_H
