//
// Created by bryab on 23-6-13.
//
#include "DataReader.h"
namespace HNN {
    DataReaderFromStdio::DataReaderFromStdio(FilePtr file) : filePtr(file) {}

    ErrorCode DataReaderFromStdio::scan(const std::string &format, void *data) const {
        int ret = fscanf(filePtr.get(), format.c_str(), data);
        LOG_D("read data num is: {}", ret);
        if (ret <= 0) {
            LOG_W("read data {} num is: {}",format, ret);
            return ErrorCode::NN_FAILED;
        }
        return ErrorCode::NN_OK;
    }
}