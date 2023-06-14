//
// Created by bryab on 23-6-13.
//
#include "Net.h"
namespace HNN {
    ErrorCode Net::loadParam(FilePtr file) {
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
            }
        }
        return ErrorCode::NN_OK;
    }

}