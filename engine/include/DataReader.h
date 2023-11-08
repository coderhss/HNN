//
// Created by bryab on 23-6-13.
//

#ifndef HNN_DATAREADER_H
#define HNN_DATAREADER_H
#include "common.hpp"
namespace HNN {
    using FilePtr = std::shared_ptr< FILE >;
    class DataReader {
    public:
        DataReader() = default;

        virtual ~DataReader() = default;

        virtual ErrorCode scan(const std::string& format, void* data) const = 0;

        virtual ErrorCode read(void* buffer, uint32_t size) const = 0;

        virtual ErrorCode reference(uint32_t size, const void** buffer) const = 0;

    };

    class DataReaderFromStdio : public DataReader {
    public:
        explicit DataReaderFromStdio(FilePtr file);
        virtual ~DataReaderFromStdio() = default;

        ErrorCode scan(const std::string& format, void* data) const override;

        ErrorCode read(void* buffer, uint32_t size) const override;

        ErrorCode reference(uint32_t size, const void** buffer) const override;

    private:
        FilePtr filePtr;
    };
    using DataReaderPtr = std::shared_ptr< DataReader >;
}
#endif //HNN_DATAREADER_H
