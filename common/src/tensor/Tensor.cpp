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
}
