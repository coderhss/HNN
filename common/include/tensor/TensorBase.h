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

        virtual void setProperty(ShapeVector& shape, uint32_t& stride, uint32_t& nscalar, uint32_t& size) = 0;

        inline void setInited(const bool inited) { tensorInited = inited; };

        template< typename T > inline T* getData(const uint32_t size = 0) const {
            if (mShape.empty() || mDataManagerPtr == nullptr) {
                return nullptr;
            }
            uint8_t* data = static_cast< uint8_t* >(mDataManagerPtr->getData());
            return static_cast< T* >(data);
        }

    protected:
        ErrorCode init();
        ErrorCode CreateDataManager();

        std::string mMemoryType = "DataManagerCommon";
    private:
        std::string mName;
        ShapeVector mShape;
        uint32_t mSize;
        bool tensorInited = false;

        DataManagerBasePtr mDataManagerPtr;

    };
}
#endif //HNN_TENSORBASE_H
