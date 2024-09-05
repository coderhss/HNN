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
        if (layer != nullptr) {
            std::cout << "no null" << std::endl;
        }
        pool_layer = CommonFactory< HNN::Layer >::getInstance().Create("Pooling");
        
    }

    HNN::ErrorCode testConvolution(uint32_t width, uint32_t height, uint32_t outNum) {

    const std::vector<float> inputData = {// channel = 0
                                  // depth = 0
                                  0.5488, 0.7152, 0.6028, 0.5449, 0.4237, 0.6459, 0.4376, 0.8918, 0.9637,
                                  0.3834, 0.7917, 0.5289, 0.568, 0.9256, 0.071, 0.0871,
                                  // depth = 1
                                  0.0202, 0.8326, 0.7782, 0.87, 0.9786, 0.7992, 0.4615, 0.7805, 0.1183,
                                  0.6399, 0.1434, 0.9447, 0.5218, 0.4147, 0.2646, 0.7742,
                                  // depth = 2
                                  0.4562, 0.5684, 0.0188, 0.6176, 0.6121, 0.6169, 0.9437, 0.6818, 0.3595,
                                  0.437, 0.6976, 0.0602, 0.6668, 0.6706, 0.2104, 0.1289,
                                  // channel = 1
                                  // depth = 0
                                  0.5488, 0.7152, 0.6028, 0.5449, 0.4237, 0.6459, 0.4376, 0.8918, 0.9637,
                                  0.3834, 0.7917, 0.5289, 0.568, 0.9256, 0.071, 0.0871
                                 };

        auto input = _Input({1, 1, 8, 8}, Dimensionformat::NCHW, halide_type_of<float>());
        // for (int i = 0; i < 10; ++i) {
        //     for (int j = 0; j < 3; ++j) {
        //         for (int k = 0; k < 10; ++k) {
        //         }
        //         std::cout << std::endl;
        //     }
        // }
        ::memcpy(input->writeMap<float>(), inputData.data(), inputData.size() * sizeof(float));
        auto in_ptr = input->readMap< float >();
        // for (uint32_t i = 0; i < 8; ++ i) {
        //     for (uint32_t j = 0; j < 8; ++ j) {
        //         std::cout << *(in_ptr + i * 8 + j) << ", ";
        //     }
        //     std::cout << std::endl;
        // }
        std::vector< int > k = {2, 2};
        auto res = _MaxPool(input, k, {2, 2});
        auto ptr = res->readMap<float>();
        std::cout << "print result." << std::endl;
        for (uint32_t i = 0; i < 4; ++i) {
            for (uint32_t j = 0; j < 4 ; ++j) {
                std::cout << *(ptr + i * 4 + j) << ", ";
            }
            std::cout << std::endl;
        }
        std::vector< uint32_t > shape{1, 1, 8, 8};
        auto tensor = std::make_shared< HNN::Tensor >(inputData.data(), inputData.data(), shape);
        HNN::ParamDict pd;
        pd.set(0, 0);
        pd.set(1, 2);
        pd.set(2, 2);
        pd.set(8, 4);
        pd.set(18, 4);
        
        std::vector<HNN::TensorPtr> out_tensor(1);
        std::vector<HNN::TensorPtr> in_tensor{tensor};
        HNN::Config config;
        pool_layer->loadParam(pd);
        pool_layer->inference(in_tensor, out_tensor, config);

        float* data = out_tensor[0]->getData< float >();

        for (uint32_t i = 0; i < 16; ++i) {
            std::cout << data[i] << " " << std::endl;
        }

        return HNN::ErrorCode::NN_OK;
    }

private:
    HNN::LayerPtr layer;
    HNN::LayerPtr pool_layer;
};


TEST_F(TestConvolution, run) {
    ASSERT_EQ(testConvolution(0, 0, 0), HNN::ErrorCode::NN_OK);
}