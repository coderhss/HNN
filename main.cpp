#include <iostream>
#include "TensorBase.h"
#include "log.h"
#include "spdlog/spdlog.h"
#include "DataManagerBase.h"
#include "DataManagerCommon.h"
#include "Allocator.h"
#include "gtest/gtest.h"

TEST(test, test) {
    EXPECT_EQ(1, 1);
}

int main() {
    ::testing::InitGoogleTest();
    RUN_ALL_TESTS();
    spdlog::debug("test log{}", 1);
    HNN::DataManagerBasePtr a;
    HNN::DataManagerCommon dataMgr;
    dataMgr.malloc(100 * sizeof (int));


    LOG_I("TEst {}", 1);
    LOG_E("error {}", 3.1);
    LOG_W("warn {}", 99);
    LOG_T("trace {}", 100);
    auto* all = new HNN::Allocator();
    int * ab = (int *)all->fastMalloc(100 * sizeof(int));

    for (int i = 0; i < 100; ++i) {
        ab[i] = i;
    }
    for (int i = 0; i < 100; ++i) {
        LOG_I("i = {}", ab[i]);
    }
    all->fastFree(ab);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
