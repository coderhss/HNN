//
// Created by bryab on 23-6-13.
//
#include "Net.h"
namespace HNN {
    ErrorCode Net::loadParam(FilePtr file) {
        DataReaderPtr dataReader = std::shared_ptr< DataReader >(new DataReaderFromStdio(file));
        auto ret = loadParam(dataReader);
        if (ret != ErrorCode::NN_OK) {
            LOG_E("load data from stdio failed.");
            return ErrorCode::NN_FAILED;
        }
        return ErrorCode::NN_OK;
    }

    ErrorCode Net::loadParam(const std::string &filePath) {
        FILE* filePointer = fopen(filePath.c_str(), "rb");
        if (filePointer == nullptr) {
            LOG_E("open file {} filed.", filePath);
            return ErrorCode::NN_FAILED;
        }

        {
            FilePtr file(filePointer, [&](FILE *p) {
                fclose(p);
                filePointer = nullptr;
            });
            auto ret = loadParam(file);
            if (ret != ErrorCode::NN_OK) {
                LOG_E("load param is filed.");
                return ErrorCode::NN_FAILED;
            }
        }
        return ErrorCode::NN_OK;
    }

    ErrorCode Net::loadParam(DataReaderPtr dataReader) {
#define SCAN_VALUE(fmt, data)                                       \
        do {                                                        \
            if (dataReader->scan(fmt, &data) != ErrorCode::NN_OK) { \
                LOG_E("parse" #data "filed.");                      \
                return ErrorCode::NN_FAILED;                        \
            }                                                       \
        } while(0)

        // parse header
        int magic = 0;
        SCAN_VALUE("%d", magic);
        if (magic != 7767517) {
            LOG_E("param is too old");
            return ErrorCode::NN_FAILED;
        }

        int layoutNumber = 0;
        int blobNumber = 0;
        SCAN_VALUE("%d", layoutNumber);
        SCAN_VALUE("%d", blobNumber);

        if (layoutNumber <= 0 || blobNumber <= 0) {
            LOG_E("layout or blob number invalid, layout: {}, blob: {}", layoutNumber, blobNumber);
            return ErrorCode::NN_FAILED;
        }

        this->blobs.resize(blobNumber);
        this->layers.resize(layoutNumber);

        for (uint32_t i = 0; i < layoutNumber; ++i) {
            char layerType[256], layerName[256];
            uint32_t bottomNumber = 0, topNumber = 0;

            SCAN_VALUE("%255s", layerType);
            SCAN_VALUE("%255s", layerName);
            SCAN_VALUE("%d", bottomNumber);
            SCAN_VALUE("%d", topNumber);
            std::string type = std::string(layerType);
            auto layer = CommonFactory< Layer >::getInstance().Create(type);

            if (layer == nullptr) {
                LOG_E("layer create failed.", type);
                return ErrorCode::NN_FAILED;
            }

            layer->type = type;
            layer->name = std::string(layerName);

            layer->bottoms.resize(bottomNumber);

            for (uint32_t j = 0; j < bottomNumber; ++j) {
                char bottomName[256];
                SCAN_VALUE("%255s", bottomName);




            }

        }

        return ErrorCode::NN_OK;
    }

}