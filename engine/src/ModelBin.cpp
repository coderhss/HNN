//
// Created by bryab on 23-6-13.
//
#include "ModelBin.h"
namespace HNN {
#define FLOAT16 0x01306B47
#define UINT8 0x000D4B38
#define FLOAT32 0x0002C056

    TensorPtr ModelBinFromDataReader::load(uint32_t width, int type) const {
        ShapeVector shape{1, 1, 1, width};
        TensorPtr tensor = std::make_shared< Tensor >(shape);
        switch (type) {
            case 0:
            {
                FlagStruct flagStruct;
                auto ret = dataReaderPtr->read(&flagStruct, sizeof(flagStruct));
                if (ret != ErrorCode::NN_OK) {
                    LOG_E("load bin failed.");
                    return nullptr;
                }
                uint32_t flag = flagStruct.f0 + flagStruct.f1 + flagStruct.f2 + flagStruct.f3;
                ErrorCode readStatus = ErrorCode::NN_OK;
                if (flagStruct.tag == FLOAT16) {

                } else if (flagStruct.tag == UINT8) {

                } else if (flagStruct.tag == FLOAT32) {
                    const void* referenceBuffer = 0;
                    readStatus = dataReaderPtr->reference(width * sizeof(float), &referenceBuffer);
                    if (readStatus != ErrorCode::NN_OK) {
                        LOG_E("read model bin failed.");

                    } else {
                        void* root = tensor->getData< void >();
                        dataReaderPtr->read(root, width * sizeof(float));

                    }
                }

                break;
            }
            case 1:
                break;
            case 2:
                break;
            default: ;

        }
        return nullptr;
    }

}