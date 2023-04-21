//
// Created by bryab on 23-4-14.
//

#ifndef HNN_TENSORBASE_H
#define HNN_TENSORBASE_H

#include <vector>
#include <string>
#include "DataManagerBase.h"
namespace HNN {
    using ShapeVector = std::vector< uint32_t >;

    class TensorBase {
    public:
        TensorBase();
//
        virtual ~TensorBase(){};
//
        TensorBase(const ShapeVector &shape, DataManagerBasePtr dataManagerBasePtr);

        template< typename T > inline T* getData(const uint32_t size = 0) const {
            if (mShape.empty() || mDataManagerPtr == nullptr) {
                     //DataManagerBasePtr
                return nullptr;
            }


        }

    private:
        std::string mName;
        ShapeVector mShape;
        DataManagerBasePtr mDataManagerPtr;

    };
}
#endif //HNN_TENSORBASE_H
