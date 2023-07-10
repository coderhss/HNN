//
// Created by bryab on 23-4-15.
//
#include "TensorBase.h"

namespace HNN {
    TensorBase::TensorBase(const ShapeVector &shape, DataManagerBasePtr dataManagerBasePtr)  :
            mShape(shape), mDataManagerPtr(dataManagerBasePtr) {}

    ErrorCode TensorBase::init() {
        auto memoryAllocated = !(mDataManagerPtr == nullptr);
        auto ret = ErrorCode::NN_OK;
        if ((ret = CreateDataManager()) != ErrorCode::NN_OK) {
            LOG_E("create data manager error.");
            return ret;
        }
        setInited(true);
        mDataManagerPtr->malloc(mSize);
        return ErrorCode::NN_OK;
    }

    ErrorCode TensorBase::CreateDataManager() {
        if (mDataManagerPtr == nullptr) {
            mDataManagerPtr = CommonFactory< DataManagerBase >::getInstance().Create(mMemoryType);
            if (mDataManagerPtr == nullptr) {
                LOG_E("data manager of {} create failed!", mMemoryType);
                return ErrorCode::NN_FAILED;
            }
        }
        return ErrorCode::NN_OK;
    }

    TensorBase::TensorBase(const std::vector<uint32_t> &shape, const MemoryType &memType, const DataType &dataType) : mShape(shape) {

    }

    ErrorCode TensorBase::reshape(const ShapeVector &shape) {
        if (shape.empty()) {
            LOG_W("reshape size is empty.");
            return ErrorCode::NN_FAILED;
        }
        uint32_t size = shape[0];
        for (uint32_t i = 1; shape.size(); ++i) {
            size *= shape[i];
        }
        if (size != this->number) {
            LOG_E("reshape number {} is unequal to old number {}", size, this->number);
            return ErrorCode::NN_FAILED;
        }
        this->mShape = shape;
        return ErrorCode::NN_OK;
    }
}