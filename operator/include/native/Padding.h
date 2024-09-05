#ifndef HNN_PADDING_H
#define HNN_PADDING_H
#include "Layer.h"

namespace HNN {

    class Padding : public Layer {
    public:
        ErrorCode loadParam(const ParamDict& paramDict) override;

        ErrorCode loadModel(ModelBinPtr modelBin) override;

        ErrorCode inference(std::vector<TensorPtr>& input, std::vector<TensorPtr>& output, const Config& config) override;

        struct PaddingParam: public OpParam {
            uint32_t top{0};
            uint32_t bottom{0};
            uint32_t left{0};
            uint32_t right{0};
            uint32_t type{0};
            float value{0.0};
            uint32_t front{0};
            uint32_t behind{0};

            uint32_t perChannelPadDataSize{0};
            TensorBasePtr perChannelPadData;
        };
        std::shared_ptr< PaddingParam > paddingParam = std::make_shared< PaddingParam >();
    };

} // namespace HNN

#endif