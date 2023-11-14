//
// Created by bryab on 23-4-15.
//

#ifndef HNN_TENSOR_H
#define HNN_TENSOR_H
#include "TensorBase.h"
#include "core/DataType.h"
namespace HNN {
    enum class MemFormat {
        NCHW,
        NHWC
    };
    class Tensor : public TensorBase {
    public:
        Tensor() = default;

        virtual ~Tensor(){};

        Tensor(const ShapeVector &shape, DataManagerBasePtr dataManagerBasePtr);

        Tensor(const ShapeVector &shape,
               const MemFormat &shapeMode = MemFormat::NCHW,
               const MemoryType &memType = MemoryType::MEM_ON_CPU,
               const DataType &dataType = DataType::HNN_FLOAT32)
               : TensorBase(shape, memType, dataType) {
            this->setInited(init() == ErrorCode::NN_OK);
        }

        Tensor(const void* virt_ptr,
           const void* phy_ptr,
           const ShapeVector &shape,
           const MemoryType &memType = MemoryType::MEM_ON_CPU,
           const DataType &dataType = DataType::HNN_FLOAT32): TensorBase(virt_ptr, phy_ptr, shape, memType, dataType) {
            this->setInited(init() == ErrorCode::NN_OK);
           };

        void setProperty(ShapeVector& shape, uint32_t& stride, uint32_t& nscalar, uint32_t& size) override;

        inline const MemFormat getMemoryFormat() const {
            return mMemoryFormat;
        }
    private:
        MemFormat mMemoryFormat = MemFormat::NCHW;
    };
    using TensorPtr = std::shared_ptr< Tensor >;
}

#endif //HNN_TENSOR_H
