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

    TensorBase::TensorBase(const std::vector<uint32_t> &shape, const MemoryType &memType, const DataType &dataType) {

    }
}