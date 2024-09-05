#include "Padding.h"

namespace HNN {

    ErrorCode Padding::loadParam(const ParamDict& paramDict) {
        paddingParam->top = paramDict.get(0, 0);
        paddingParam->bottom = paramDict.get(1, 0);
        paddingParam->left = paramDict.get(2, 0);
        paddingParam->right = paramDict.get(3, 0);
        paddingParam->type = paramDict.get(4, 0);
        paddingParam->value = paramDict.get(5, 0.f);
        paddingParam->perChannelPadDataSize = paramDict.get(6, 0);
        paddingParam->front = paramDict.get(7, 0);
        paddingParam->behind = paramDict.get(8, 0);
        return ErrorCode::NN_OK;
    }

    ErrorCode Padding::loadModel(ModelBinPtr modelBin) {
        if (paddingParam->perChannelPadDataSize) {
            paddingParam->perChannelPadData = modelBin->load(paddingParam->perChannelPadDataSize, 1);
        }
        return ErrorCode::NN_OK;
    }

    ErrorCode Padding::inference(std::vector<TensorPtr>& input, std::vector<TensorPtr>& output, const Config& config) {

        


        return ErrorCode::NN_OK;
    }
    
} // namespace HNN