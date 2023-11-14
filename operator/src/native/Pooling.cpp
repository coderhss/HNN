//
// Created by bryab on 23-7-8.
//
#include "Pooling.h"
#include <iostream>
namespace HNN {
    ErrorCode Pooling::loadParam(const ParamDict &paramDict) {
        pool_param->pooling_type = paramDict.get(0, 0);

        pool_param->kernel_w = paramDict.get(1, 2);
        pool_param->kernel_h = paramDict.get(11, pool_param->kernel_w);

        pool_param->stride_w = paramDict.get(2, 2);
        pool_param->stride_h = paramDict.get(pool_param->stride_w, 2);

        pool_param->pad_left = paramDict.get(3, 0);
        pool_param->pad_right = paramDict.get(pool_param->pad_left, 0);

        pool_param->pad_top = paramDict.get(13, 0);
        pool_param->pad_bottom = paramDict.get(15, pool_param->pad_top);

        pool_param->pad_bottom = paramDict.get(4, 0);

        pool_param->avgpool_count_include_pad = paramDict.get(6, 0);

        pool_param->global_pooling = paramDict.get(4, 0);

        pool_param->out_w = paramDict.get(8, 0);
        pool_param->out_h = paramDict.get(18, pool_param->out_w);

        pool_param->adaptive_pooling = paramDict.get(4, 0);

        pool_param->pad_mode = paramDict.get(5, 0);

        return ErrorCode::NN_OK;
    }

    ErrorCode Pooling::loadModel(ModelBinPtr modelBin) {
        return ErrorCode::NN_OK;
    }

    ErrorCode Pooling::inference(TensorPtr input, TensorPtr& output) {

        return runImpl(input, output, nullptr);
    }

    ErrorCode Pooling::runImpl(TensorPtr input, TensorPtr& output, ParamPtr param) {
        auto& in_shape = input->getShape();
        auto& dataType = input->getDataType();

        int32_t out_h = pool_param->out_h;
        int32_t out_w = pool_param->out_w;
        int32_t out_c = in_shape[1];
        int32_t out_n = in_shape[0];
        ShapeVector out_shape{out_n, out_c, out_h, out_w};
        output = std::make_shared< Tensor >(out_shape);

        auto* out_ptr = output->getData< float >();

        if (pool_param->pooling_type == 0) {
            const uint32_t kernel_size = pool_param->kernel_h * pool_param->kernel_w;
            std::vector< int32_t > space_ind(kernel_size);
            uint32_t p1 = 0, p2 = 0;
            uint32_t gap = in_shape[3] - pool_param->kernel_w;
            for (uint32_t i = 0; i < pool_param->kernel_h; ++i) {
                for (uint32_t j = 0; j < pool_param->kernel_w; ++j) {
                    space_ind[p1] = p2;
                    p1++;
                    p2++;
                }
                p2 += gap;
            }

            for (uint32_t c = 0; c < out_c; ++c) {
                auto* per_channel_ptr = input->getDataOfChannel< float >(c);
                for (uint32_t h = 0; h < out_h; ++h) {
                    for (uint32_t w = 0; w < out_w; ++w) {
                        auto* sptr = per_channel_ptr + h * in_shape[3] * pool_param->stride_h + w * pool_param->stride_w;
                        float max_v = sptr[0];
                        for (uint32_t k = 1; k < kernel_size; ++k) {
                            max_v = std::max(max_v, sptr[space_ind[k]]);
                        }
                        out_ptr[w] = max_v;
                    }
                    out_ptr += out_w;
                }
            }
        }


        return ErrorCode::NN_OK;
    }
}
