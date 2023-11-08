//
// Created by bryab on 23-6-13.
//
#include "ModelBin.h"
#include <iostream>
namespace HNN {
#define FLOAT16 0x01306B47
#define UINT8 0x000D4B38
#define FLOAT32 0x0002C056

    TensorBasePtr ModelBinFromDataReader::load(uint32_t width, int type) const {
        ShapeVector shape{1, 1, 1, width};
        TensorPtr tensor;
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
                        tensor = std::make_shared<Tensor>(shape, MemFormat::NCHW, MemoryType::MEM_ON_CPU, DataType::HNN_FLOAT32);
                        void *root = tensor->getData<void>();
                        dataReaderPtr->read(root, width * sizeof(float));
                    }
                } else {
                    tensor = std::make_shared<Tensor>(shape, MemFormat::NCHW, MemoryType::MEM_ON_CPU, DataType::HNN_FLOAT32);
                    void *root = tensor->getData<void>();
                    dataReaderPtr->read(root, width * sizeof(float));
                }
                break;
            }
            case 1: {
                tensor = std::make_shared< Tensor >(shape, MemFormat::NCHW, MemoryType::MEM_ON_CPU, DataType::HNN_FLOAT32);
                void *buffer = tensor->getData< void >();
                dataReaderPtr->read(buffer, width * sizeof(float));
                break;
            }
            case 2:
                break;
            default: ;

        }
        return tensor;
    }

    TensorBasePtr ModelBinFromDataReader::load(uint32_t n, uint32_t c, uint32_t h, uint32_t w, int type) const {
        uint32_t number = n * c * h * w;
        auto tensor = load(number, type);
        ShapeVector shape{n, c, h, w};
//        tensor->reshape(shape);
        return tensor;
    }

}