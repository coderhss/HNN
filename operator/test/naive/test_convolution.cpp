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
private:
    LayerPtr layer;
};


TEST_F(TestConvolution, run) {

}