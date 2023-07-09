//
// Created by bryab on 23-7-10.
//

#ifndef HNN_DATAMANAGERREGISTER_H
#define HNN_DATAMANAGERREGISTER_H
#include "core/CommonFactory.h"
#include "common.h"
#include "DataManagerBase.h"
#include "DataManagerCommon.h"

REGISTER_COMMON_ENGINE(HNN, DataManagerCommon, DataManagerBase, DataManagerCommon);
#endif //HNN_DATAMANAGERREGISTER_H
