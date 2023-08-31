//
// Created by bryab on 23-7-17.
//
#include "expr/Expr.hpp"
#include "expr/NeuralNetWorkOp.hpp"
#include "../test_op.h"
using namespace MNN::Express;
class TestConvolution : public testing::Test {
public:
    TestConvolution() {}

protected:
    void SetUp() override {
        layer = CommonFactory< HNN::Layer >::getInstance().Create("Convolution");
    }

    HNN::ErrorCode testConvolution(uint32_t width, uint32_t height, uint32_t outNum) {
        cv::Mat kernel(3, 3, CV_32FC3);
        cv::Mat image(320, 320, CV_32FC3);
        cv::Mat out;
        auto input = _Input({1, 2, 2, 1});
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < 10; ++k) {
                }
                std::cout << std::endl;
            }
        }

        cv::RNG rng;
        rng.fill(kernel, cv::RNG::UNIFORM, 1, 5);
        rng.fill(image, cv::RNG::UNIFORM, 1, 5);
        cv::filter2D(image, out, -1, kernel);
        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 20; ++j) {
                std::cout << out.at<float>(i, j) << std::endl;
            }
        }
        std::cout << *(float*)kernel.data << std::endl;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                std::cout << kernel.at<float>(i, j) << std::endl;
            }
        }


        return HNN::ErrorCode::NN_FAILED;
    }

private:
    HNN::LayerPtr layer;
};


TEST_F(TestConvolution, run) {
    ASSERT_EQ(testConvolution(0, 0, 0), HNN::ErrorCode::NN_OK);
}