#include <iostream>
#include "TensorBase.h"
#include "log.h"
#include "spdlog/spdlog.h"
#include "DataManagerBase.h"
#include "DataManagerCommon.h"
#include "Allocator.h"
#include "gtest/gtest.h"

class Test : public testing::TestWithParam<int> {

};

TEST_P(Test, test) {
    int n = GetParam();
    EXPECT_EQ(n, 1);
}

TEST(test, test) {
    EXPECT_EQ(1, 1);
}

std::vector<int> a{0, 1, 2};
INSTANTIATE_TEST_CASE_P(TestSuitName, Test, testing::ValuesIn(a));

int main() {
    ::testing::InitGoogleTest();
    RUN_ALL_TESTS();
//    HNN::DataManagerBasePtr a;
    HNN::DataManagerCommon dataMgr;
    dataMgr.malloc(100 * sizeof (int));


    LOG_I("TEst {}", 1);
    LOG_E("error {}", 3.1);
    LOG_W("warn {}", 99);
    LOG_T("trace {}", 100);
//    auto* all = new HNN::Allocator();
//    int * ab = (int *)all->fastMalloc(100 * sizeof(int));
//
//    for (int i = 0; i < 100; ++i) {
//        ab[i] = i;
//    }
//    for (int i = 0; i < 100; ++i) {
////        LOG_I("i = {}", ab[i]);
//    }
//    all->fastFree(ab);
//
//    std::cout << "Hello, World!" << std::endl;
    return 0;
}
