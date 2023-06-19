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
        if (magic != 1314) {
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
        uint32_t currentBlobIndex = 0;
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
            layer->tops.resize(topNumber);

            for (uint32_t j = 0; j < bottomNumber; ++j) {
                char bottomName[256];
                SCAN_VALUE("%255s", bottomName);
                std::string bottomNameString = std::string(bottomName);

                auto bottomBlobIndex = getIndexFromBlobName(bottomNameString);

                if (bottomBlobIndex == -1) {
                    BlobPtr& blob = this->blobs[currentBlobIndex];
                    blob.reset(new Blob());
                    blob->name = bottomNameString;
                    blobName2Index[bottomNameString] = currentBlobIndex;
                    bottomBlobIndex = static_cast< int >(currentBlobIndex);
                    currentBlobIndex ++;
                }

                this->blobs[bottomBlobIndex]->consumer = i;
                layer->bottoms[j] = bottomBlobIndex;
            }

            for (uint32_t j = 0; j < topNumber; ++j) {
                char topName[256];
                SCAN_VALUE("%255s", topName);

                auto& blob = this->blobs[currentBlobIndex];

                blob->name = std::string(topName);
                blob->producer = i;
                layer->tops[j] = currentBlobIndex;
                currentBlobIndex ++;
            }


        }

        return ErrorCode::NN_OK;
    }

    int Net::getIndexFromBlobName(const std::string &name) {
        if (this->blobName2Index.find(name) == this->blobName2Index.end()) {
            LOG_D("cannot find blob by name {}.", name);
            return -1;
        }
        return this->blobName2Index.at(name);
    }

    BlobPtr Net::getBlobFromName(const std::string &name) {
        auto index = getIndexFromBlobName(name);
        if (index == -1 || index >= this->blobs.size()) {
            LOG_D("index is invalid, index: {}, blob size: {}", index, blobs.size());
            return nullptr;
        }
        return blobs.at(index);
    }

}