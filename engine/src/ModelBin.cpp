//
// Created by bryab on 23-6-13.
//
#include "ModelBin.h"
namespace HNN {
#define FLOAT16 0x01306B47
#define UINT8 0x000D4B38
#define FLOAT32 0x0002C056

    TensorPtr ModelBinFromDataReader::load(uint32_t width, int type) const {
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

                if (flagStruct.tag == FLOAT16) {

                } else if (flagStruct.tag == UINT8) {

                } else if (flagStruct.tag == FLOAT32) {

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