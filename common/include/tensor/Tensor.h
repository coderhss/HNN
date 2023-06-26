//
// Created by bryab on 23-4-15.
//

#ifndef HNN_TENSOR_H
#define HNN_TENSOR_H
#include "TensorBase.h"
namespace HNN {
    #define NCHW ("NCHW")
    #define NHWC ("NHWC")
    class Tensor : public TensorBase {
    public:
        Tensor() = default;

        virtual ~Tensor(){};

        Tensor(const ShapeVector &shape, DataManagerBasePtr dataManagerBasePtr);

        inline std::string getMemoryFormat() const {
            return mMemoryFormat;
        }
    private:
        std::string mMemoryFormat = NCHW;
    };
    using TensorPtr = std::shared_ptr< Tensor >;
}

#endif //HNN_TENSOR_H
