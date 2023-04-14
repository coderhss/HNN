//
// Created by bryab on 23-4-14.
//

#ifndef HNN_TENSORBASE_H
#define HNN_TENSORBASE_H

#include <vector>
#include <string>

namespace HNN {
    using ShapeVector = std::vector<uint32_t>;

    class TensorBase {
    public:
//        TensorBase();
//
//        virtual ~TensorBase();
//
//        TensorBase(const ShapeVector &shape);

    private:
        std::string mName;
        ShapeVector mShape;

    };
}
#endif //HNN_TENSORBASE_H
