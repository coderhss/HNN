//
// Created by bryab on 23-6-13.
//
#include "DataReader.h"
namespace HNN {
    DataReaderFromStdio::DataReaderFromStdio(FilePtr file) : filePtr(file) {}

    ErrorCode DataReaderFromStdio::scan(const std::string &format, void *data) const {
        int ret = fscanf(filePtr.get(), format.c_str(), data);
        if (ret <= 0) {
            LOG_W("read data {} num is: {}",format, ret);
            return ErrorCode::NN_FAILED;
        }
        return ErrorCode::NN_OK;
    }

    ErrorCode DataReaderFromStdio::read(void *buffer, uint32_t size) const {
        uint32_t read_size = fread(buffer, 1, size, filePtr.get());
        if (read_size != size) {
            LOG_E("read model bin size is wrong. expect: {}, read: {}", size, read_size);
            return ErrorCode::NN_FAILED;
        }
        return ErrorCode::NN_OK;
    }

    ErrorCode DataReaderFromStdio::reference(uint32_t size, const void **buffer) const {
        return ErrorCode::NN_OK;
    }
}