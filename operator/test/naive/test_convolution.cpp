//
// Created by bryab on 23-7-17.
//
#include "../test_op.h"
using namespace HNN;
class TestConvolution : public testing::Test {
public:
    TestConvolution() {}

protected:
    void SetUp() override {
        layer = CommonFactory< Layer >::getInstance().Create("Convolution");
    }

    ErrorCode testConvolution(uint32_t width, uint32_t height, uint32_t outNum) {
        return ErrorCode::NN_FAILED;
    }

private:
    LayerPtr layer;
};


TEST_F(TestConvolution, run) {
    ASSERT_EQ(testConvolution(0, 0, 0), ErrorCode::NN_OK);
}