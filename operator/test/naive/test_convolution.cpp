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
        cv::Mat kernel(3, 3, CV_32F);
        cv::RNG rng;
        rng.fill(kernel, cv::RNG::UNIFORM, 1, 5);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                std::cout << kernel.at<float>(i, j) << std::endl;
            }
        }
        return ErrorCode::NN_FAILED;
    }

private:
    LayerPtr layer;
};


TEST_F(TestConvolution, run) {
    ASSERT_EQ(testConvolution(0, 0, 0), ErrorCode::NN_OK);
}