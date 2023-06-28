//
// Created by bryab on 23-6-13.
//

#ifndef HNN_MODELBIN_H
#define HNN_MODELBIN_H
#include "DataReader.h"
#include "Tensor.h"
namespace HNN {
    class ModelBin {
    public:
        ModelBin() = default;

        virtual ~ModelBin() = default;
        virtual TensorPtr load(uint32_t width, int type) const = 0;

    };

    using ModelBinPtr = std::shared_ptr< ModelBin >;

    class ModelBinFromDataReader : public ModelBin {
    public:
        explicit ModelBinFromDataReader(DataReaderPtr dataReader)
            : ModelBin(), dataReaderPtr(dataReader){};

        TensorPtr load(uint32_t width, int type) const override;

        DataReaderPtr dataReaderPtr;
    };

}
#endif //HNN_MODELBIN_H