//
// Created by bryab on 23-4-15.
//
#include "Tensor.h"
#include "TensorBase.h"

namespace HNN {
    Tensor::Tensor(const ShapeVector& shape, DataManagerBasePtr dataManagerBasePtr) : TensorBase(shape, dataManagerBasePtr) {
        if (shape.size() < 4) {
            LOG_E("shape vector is not 4.");
            return;
        }
    }

    void Tensor::setProperty(ShapeVector &shape, uint32_t &stride, uint32_t &nscalar, uint32_t &size) {

    }


}
