//
// Created by bryab on 23-6-17.
//

#ifndef HNN_PARAMDICT_H
#define HNN_PARAMDICT_H
#include "common.h"
#include "DataReader.h"
#define HNN_MAX_PARAM_COUNT 32
namespace HNN {
    typedef struct {
        uint32_t type;
        union {
            int intValue;
            float floatValue;
        };

    } Param;
    using ParamPtr = std::shared_ptr< Param >;
    using ParamVec = std::vector< ParamPtr >;

    class ParamDict {
        ParamDict();

        virtual ~ParamDict() {};

        uint32_t getType(int id) const;

        int get(int id, int defaultValue) const;

        float get(int id, float defaultValue) const;

        void set(int id, int value);

        void set(int id, float value);

        ErrorCode loadParam(DataReaderPtr dataReader);

        ErrorCode loadParamBin(DataReaderPtr dataReader);

    private:
        ParamVec params;
    };
}
#endif //HNN_PARAMDICT_H
