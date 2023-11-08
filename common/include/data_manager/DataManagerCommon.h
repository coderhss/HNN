//
// Created by bryab on 23-4-15.
//

#ifndef HNN_DATAMANAGERCOMMON_H
#define HNN_DATAMANAGERCOMMON_H

#include <mutex>
#include "DataManagerBase.h"
namespace HNN {
    class DataManagerCommon : public DataManagerBase {
    public:
        void *malloc(const uint32_t size) override;
        void free(void* p) override;
        void* setPtr(void* virt, void* phy, uint32_t size) override;
    private:
        std::mutex mtx;
    };
}
#endif //HNN_DATAMANAGERCOMMON_H
