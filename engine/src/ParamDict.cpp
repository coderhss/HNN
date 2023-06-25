//
// Created by bryab on 23-6-18.
//
#include "ParamDict.h"
namespace HNN {

    static bool isStringFloat(const char valueString[16]) {
        for (int i = 0; i < 16; ++i) {
            if (valueString[i] == '\0') {
                return false;
            }

            if (valueString[i] == '.' || tolower(valueString[i]) == 'e') {
                return true;
            }
        }
        return true;
    }

    static float string2float(const char valueString[16]) {
        double value = 0.0;

        const char* ptr = valueString;

        bool sign = *ptr != '-';
        if (*ptr == '+' || *ptr == '-') {
            ptr ++;
        }

        int32_t valueBefore = 0;
        while (std::isdigit(*ptr)) {
            valueBefore = valueBefore * 10 + (*ptr - '0');
            ptr ++;
        }

        value = (double)valueBefore;

        if (*ptr == '.') {
            ptr++;
            uint32_t pow10 = 1;
            uint32_t valueAfter = 0;

            while (std::isdigit(*ptr)) {
                valueAfter = valueAfter * 10 + (*ptr - '0');
                pow10 *= 10;
                ptr++;
            }
            value += valueAfter / (double )pow10;
        }

        if (*ptr == 'e' || *ptr == 'E') {
            ptr++;

            bool fact = *ptr != '-';
            if (*ptr == '+' || *ptr == '-') {
                ptr ++;
            }
            uint32_t expon = 0;
            while(std::isdigit(*ptr)) {
                expon = expon * 10 + (*ptr - '0');
                ptr ++;
            }

            double scale = 1.0;
            while (expon >= 8) {
                scale *= 1e8;
                expon -= 8;
            }
            while (expon > 0) {
                scale *= 10.0;
                expon -= 1;
            }

            value = fact ? value * scale : value / scale;
        }

        return sign ? (float)value : (float)-value;
    }

    uint32_t ParamDict::getType(int id) const {
        return 0;
    }

    int ParamDict::get(int id, int defaultValue) const {
        if (params[id] == nullptr) {
            return defaultValue;
        }
        return params[id]->type ? params[id]->intValue : defaultValue;
    }

    float ParamDict::get(int id, float defaultValue) const {
        if (params[id] == nullptr) {
            return defaultValue;
        }
        return params[id]->type ? params[id]->floatValue : defaultValue;
    }

    void ParamDict::set(int id, int value) {

    }

    void ParamDict::set(int id, float value) {

    }

    ErrorCode ParamDict::loadParam(DataReaderPtr dataReader) {
        int id;
        while (dataReader->scan("%d=", &id) == ErrorCode::NN_OK) {
            bool isArray = id <= -23300;
            if (isArray) {
                id = -id - 23300;
            }

            if (id >= HNN_MAX_PARAM_COUNT) {
                LOG_E("id: {} over max: {}", id, HNN_MAX_PARAM_COUNT);
                return ErrorCode::NN_FAILED;
            }

            if (isArray) {

            } else {
                char valueStr[16];
                auto ret = dataReader->scan("%15s", valueStr);
                if (ret == ErrorCode::NN_FAILED) {
                    LOG_E("param dict read filed.");
                    return ErrorCode::NN_FAILED;
                }

                bool isFloat = isStringFloat(valueStr);

                if (params[id] == nullptr) {
                    params[id].reset(new Param());
                }
                if (isFloat) {
                    params[id]->floatValue = string2float(valueStr);
                } else {
                    auto ret = sscanf(valueStr, "%d", &params[id]->intValue);
                    if (ret != 1) {
                        LOG_E("dict param error.");
                        return ErrorCode::NN_FAILED;
                    }
                }
                params[id]->type = isFloat ? 3 : 2;
            }
        }
        return ErrorCode::NN_OK;
    }

    ErrorCode ParamDict::loadParamBin(DataReaderPtr dataReader) {
        return ErrorCode::NN_FAILED;
    }

}