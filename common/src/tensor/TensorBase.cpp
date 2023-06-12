//
// Created by bryab on 23-4-15.
//
#include "TensorBase.h"

namespace HNN {
    TensorBase::TensorBase(const ShapeVector &shape, DataManagerBasePtr dataManagerBasePtr)  :
            mShape(shape), mDataManagerPtr(dataManagerBasePtr) {}

    ErrorCode TensorBase::init() {

//        if ()
        return ErrorCode::NN_FAILED;
    }
}