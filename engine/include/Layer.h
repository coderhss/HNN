//
// Created by bryab on 23-6-12.
//

#ifndef HNN_LAYER_H
#define HNN_LAYER_H
#include "Blob.h"
#include "ParamDict.h"
#include "ModelBin.h"

namespace HNN {
    class Layer {
    public:

        struct OpParam {};

        Layer() = default;

        virtual ~Layer(){};

        virtual ErrorCode loadParam(const ParamDict& paramDict);

        virtual ErrorCode loadModel(ModelBinPtr modelBin);

        virtual ErrorCode inference(TensorPtr input, TensorPtr& output);

        virtual ErrorCode runImpl(TensorPtr input, TensorPtr& output, std::shared_ptr< OpParam > param) { return ErrorCode::NN_OK; };

        std::string type;

        std::string name;

        std::vector< uint32_t > bottoms;

        std::vector< uint32_t > tops;
    };
    using LayerPtr = std::shared_ptr< Layer >;
}
#endif //HNN_LAYER_H
