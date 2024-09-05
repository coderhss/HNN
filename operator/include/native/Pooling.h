//
// Created by bryab on 23-7-8.
//

#ifndef HNN_POOLING_H
#define HNN_POOLING_H
#include "Layer.h"

namespace HNN {
    class Pooling : public Layer {
    public:
        ErrorCode loadParam(const ParamDict& paramDict) override;

        ErrorCode loadModel(ModelBinPtr modelBin) override;

        ErrorCode inference(std::vector<TensorPtr>& input, std::vector<TensorPtr>& output, const Config& config) override;

        ErrorCode runImpl(std::vector<TensorPtr>& input, std::vector<TensorPtr>& output, const Config& config);

        ErrorCode makePadding(TensorPtr& input, TensorPtr& output, const Config& config);

        struct PoolParam : public OpParam {
            int pooling_type{0};    // 0
            int kernel_w{0};    //1    
            int stride_w{1};    //2
            int pad_left{0};    //3
            int global_pooling{0};  //4
            int pad_mode{0};    //5
            int avgpool_count_include_pad{0};   //6
            int adaptive_pooling{0};    //7
            int out_w{0};   //8
            int kernel_h{kernel_w}; //11
            int stride_h{stride_w}; //12
            int pad_top{pad_left};  //13
            int pad_right{pad_left};  //14          
            int pad_bottom{pad_top};  //15
            int out_h{out_w};         //18

        };
        std::shared_ptr< PoolParam > pool_param = std::make_shared< PoolParam >();
    };
}

#endif //HNN_POOLING_H
