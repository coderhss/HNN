#include <iostream>
#include "TensorBase.h"
#include "log.h"
#include "spdlog/spdlog.h"
#include "DataManagerBase.h"
#include "DataManagerCommon.h"
#include "Allocator.h"
#include "gtest/gtest.h"
#include "Net.h"
#include "register.h"
#include "common.hpp"
#include "Tensor.h"
#include <omp.h>
#include "opencv2/opencv.hpp"
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

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest();
    RUN_ALL_TESTS();
//    HNN::DataManagerBasePtr a;
    HNN::DataManagerCommon dataMgr;
    dataMgr.malloc(100 * sizeof (int));
    HNN::Net net;
    std::string path = "";
    std::string model_path = "";
    std::string test_pic = "";
    if (argc > 1) {
        path = argv[1];
        model_path = argv[2];
        test_pic = argv[3];
    }
    net.loadParam(path);
    net.loadModel(model_path);

    cv::Mat mat = cv::imread(test_pic, cv::IMREAD_COLOR);
    cv::Mat resizeImage;
    cv::resize(mat, resizeImage, cv::Size(227, 227), 0, 0);
    uint32_t height = resizeImage.rows;
    uint32_t weith = resizeImage.cols;
    uint32_t channel = resizeImage.channels();
    

    std::vector<float> dst_data;
    std::vector<cv::Mat> bgrChannels(3);
    cv::split(resizeImage, bgrChannels);
    for (auto i = 0; i < bgrChannels.size(); i++)
    {
        std::vector<float> data = std::vector<float>(bgrChannels[i].reshape(1, 1));
        dst_data.insert(dst_data.end(), data.begin(), data.end());
    }

    LOG_I("height: {}, weith: {}, c: {}", height, weith, channel);
    HNN::ShapeVector shape{1, channel, height, weith};
    HNN::TensorPtr input = std::make_shared< HNN::Tensor >(shape);
    float* data = input->getData<float>();
    const float mean_vals[3] = {104.f, 117.f, 123.f};
    for (uint32_t i = 0; i < input->getNumber(); ++i) {
        // LOG_E("ind: {} {}", i, i / 51529);
        *(data + i) = (dst_data[i] - mean_vals[(i / 51529)]);
    }
    auto executer = net.getExecuter();
    // for (uint32_t i = 0; i < 20; ++i) {
    //     LOG_E("ini: {}", *(input->getData< float >() + i));
    // }
    executer->input("data", input);
    HNN::TensorPtr tensor = std::make_shared< HNN::Tensor >();
    HNN::Config config;
    #include <chrono>   
using namespace std;
using namespace chrono;

auto start = system_clock::now();
// do something...
    executer->getBlob("prob", tensor, config);
auto end   = system_clock::now();
auto duration = duration_cast<microseconds>(end - start);
cout <<  "花费了" 
     << double(duration.count()) * microseconds::period::num / microseconds::period::den 
     << "秒" << endl;

    std::string savePath = "./";
    // executer->dumpAllTensor(savePath);
    // for (uint32_t i = 0; i < 50; ++i) {
    //     LOG_E("result: {}", *(tensor->getData<float>() + i));
    // }


    LOG_I("TEst {}", 1);
    LOG_E("error {}", 3.1);
    LOG_W("warn {}", 99);
    LOG_T("trace {}", 100);
    LOG_D("debug {}", 110);
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
    // #pragma omp parallel for
    // for (int i = 0; i < 1000; ++i) {
    //     std::cout << omp_get_thread_num() << " ";
    // }
    return 0;
}
