//
// Created by bryab on 23-4-15.
//
#include "TensorBase.h"

namespace HNN {
    TensorBase::TensorBase(const ShapeVector &shape, DataManagerBasePtr dataManagerBasePtr)  :
            mShape(shape), mDataManagerPtr(dataManagerBasePtr) {}

    TensorBase::TensorBase(const ShapeVector &shape, const MemoryType &memType, const DataType &dataType) :
            mShape(shape), mMemoryType(memType), dataType(dataType) {
    }

    TensorBase::TensorBase(const void* virt_ptr,
               const void* phy_ptr,
               const ShapeVector &shape,
               const MemoryType &memType,
               const DataType &dataType) : 
               mShape(shape), mMemoryType(memType), dataType(dataType), mPtrVec({virt_ptr, phy_ptr}) {};

    ErrorCode TensorBase::init() {
        auto memoryAllocated = !(mDataManagerPtr == nullptr);
        auto ret = ErrorCode::NN_OK;
        if ((ret = CreateDataManager()) != ErrorCode::NN_OK) {
            LOG_E("create data manager error.");
            return ret;
        }
        setInited(true);
        calculateNumber();
        mSize = number * GetTypeSize(dataType);
        if (memoryAllocated) {
            return ErrorCode::NN_OK;
        }
        if (mPtrVec.size() == 2) {
            mDataManagerPtr->setPtr(
                const_cast< void* >(mPtrVec[0]), const_cast< void* >(mPtrVec[1]), mSize
            );
        } else {
            mDataManagerPtr->malloc(mSize);
        }
        return ErrorCode::NN_OK;
    }

    ErrorCode TensorBase::CreateDataManager() {
        if (mDataManagerPtr == nullptr) {
            auto memoryTypeStr = DataManagerType2Name.at(mMemoryType);
            mDataManagerPtr = CommonFactory< DataManagerBase >::getInstance().Create(memoryTypeStr);
            if (mDataManagerPtr == nullptr) {
                LOG_E("data manager of {} create failed!", memoryTypeStr);
                return ErrorCode::NN_FAILED;
            }
        }
        return ErrorCode::NN_OK;
    }

    ErrorCode TensorBase::reshape(const ShapeVector &shape) {
        if (shape.empty()) {
            LOG_W("reshape size is empty.");
            return ErrorCode::NN_FAILED;
        }
        uint32_t size = shape[0];
        for (uint32_t i = 1; i < shape.size(); ++i) {
            size *= shape[i];
        }
        if (size != this->number) {
            LOG_E("reshape number {} is unequal to old number {}", size, this->number);
            return ErrorCode::NN_FAILED;
        }
        this->mShape = shape;
        return ErrorCode::NN_OK;
    }

    ErrorCode TensorBase::calculateNumber() {
        if (tensorInited) {
            if (mShape.empty()) {
                number = 0;
            } else {
                number = mShape[0];
                for (uint32_t i = 0; i < mShape.size(); ++i) {
                    number *= mShape[i];
                }
            }
        }
        return ErrorCode::NN_OK;
    }
}