//
// Created by bryab on 23-4-14.
//

#ifndef HNN_TENSORBASE_H
#define HNN_TENSORBASE_H

#include <vector>
#include <string>
#include "DataManagerBase.h"
#include "core/DataType.h"
namespace HNN {
    using ShapeVector = std::vector< uint32_t >;

    class TensorBase {
    public:
        TensorBase() = default;
//
        virtual ~TensorBase(){};
//
        TensorBase(const ShapeVector &shape, DataManagerBasePtr dataManagerBasePtr);

        TensorBase(const ShapeVector& shape){};

        TensorBase(const ShapeVector &shape,
                   const MemoryType &memType = MemoryType::MEM_ON_CPU,
                   const DataType &dataType = DataType::HNN_FLOAT32);

        TensorBase(const void* virt_ptr,
                   const void* phy_ptr,
                   const ShapeVector &shape,
                   const MemoryType &memType = MemoryType::MEM_ON_CPU,
                   const DataType &dataType = DataType::HNN_FLOAT32);

        ErrorCode reshape(const ShapeVector& shape);

        inline const ShapeVector& getShape() { return mShape; }

        inline const DataType& getDataType() { return dataType; }

        inline const uint32_t getTypeSize() { return GetTypeSize(dataType); }

        virtual void setProperty(ShapeVector& shape, uint32_t& stride, uint32_t& nscalar, uint32_t& size) = 0;

        inline void setInited(const bool inited) { tensorInited = inited; };

        inline uint32_t getNumber() const { return number; }

        template< typename T > inline T* getData(const uint32_t size = 0) const {
            if (mShape.empty() || mDataManagerPtr == nullptr) {
                return nullptr;
            }
            uint8_t* data = static_cast< uint8_t* >(mDataManagerPtr->getData());
            return (T*)data;
        }

        template< typename T > inline T* getDataOfChannel(const uint32_t c) const {
            if (c >= mShape[1] || mDataManagerPtr == nullptr) {
                LOG_E("input channel error {} vs {}", c, mShape[1]);
                return nullptr;
            }
            T* data = static_cast< T* >(mDataManagerPtr->getData());
            return &data[c * mShape[2] * mShape[3]];
        }
        std::string mName = "";

    protected:
        ErrorCode init();
        ErrorCode CreateDataManager();
        ErrorCode calculateNumber();

        MemoryType mMemoryType = MemoryType ::MEM_ON_CPU;
    private:
        ShapeVector mShape;
        uint32_t number{0};
        uint32_t mSize{0};
        bool tensorInited = false;
        DataType dataType = DataType::HNN_FLOAT32;
        DataManagerBasePtr mDataManagerPtr;
        std::vector< const void* > mPtrVec;

    };
    using TensorBasePtr = std::shared_ptr< TensorBase >;
}
#endif //HNN_TENSORBASE_H
