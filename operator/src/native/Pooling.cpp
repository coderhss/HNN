//
// Created by bryab on 23-7-8.
//
#include "Pooling.h"
#include <iostream>
#include "common.hpp"
#include <omp.h>
namespace HNN {
    ErrorCode Pooling::loadParam(const ParamDict &paramDict) {
        pool_param->pooling_type = paramDict.get(0, 0);

        pool_param->kernel_w = paramDict.get(1, 0);
        pool_param->kernel_h = paramDict.get(11, pool_param->kernel_w);

        pool_param->stride_w = paramDict.get(2, 1);
        pool_param->stride_h = paramDict.get(12, pool_param->stride_w);

        pool_param->pad_left = paramDict.get(3, 0);
        pool_param->pad_right = paramDict.get(14, pool_param->pad_left);

        pool_param->pad_top = paramDict.get(13, pool_param->pad_left);
        pool_param->pad_bottom = paramDict.get(15, pool_param->pad_top);

        pool_param->avgpool_count_include_pad = paramDict.get(6, 0);

        pool_param->global_pooling = paramDict.get(4, 0);

        pool_param->out_w = paramDict.get(8, 0);
        pool_param->out_h = paramDict.get(18, pool_param->out_w);

        pool_param->adaptive_pooling = paramDict.get(7, 0);

        pool_param->pad_mode = paramDict.get(5, 0);

        return ErrorCode::NN_OK;
    }

    ErrorCode Pooling::loadModel(ModelBinPtr modelBin) {
        return ErrorCode::NN_OK;
    }

    ErrorCode Pooling::inference(std::vector<TensorPtr>& input, std::vector<TensorPtr>& output, const Config& config) {

        return runImpl(input, output, config);
    }

    ErrorCode Pooling::runImpl(std::vector<TensorPtr>& input, std::vector<TensorPtr>& output, const Config& config) {

        if (pool_param->global_pooling) {
            ShapeVector in_shape = input[0]->getShape();
            ShapeVector outShape = {in_shape[0], in_shape[1], 1, 1};
            uint32_t size = in_shape[2] * in_shape[3];
            output[0] = std::make_shared< Tensor >(outShape);
            if (pool_param->pooling_type == 1) {
                float* in = input[0]->getData<float>();
                float* out = output[0]->getData<float>();
                for (uint32_t n = 0; n < in_shape[0]; ++n) {
                    float* batchPtr = in + n * in_shape[1] * size;
                    float* outBatchPtr = out + n * in_shape[1];
                    for (uint32_t c = 0; c < in_shape[1]; ++c) {
                        float sum = 0;
                        float* channelPtr = batchPtr + c * size;
                        for (uint32_t i = 0; i < size; ++i) {
                            sum += channelPtr[i];
                            // std::cout << channelPtr[i] << " ";
                        }
                        outBatchPtr[c] = sum / size;
                    }
                }
                return ErrorCode::NN_OK;
            } else if (pool_param->pooling_type == 0) {
                float max = 0;
                float* in = input[0]->getData<float>();
                float* out = output[0]->getData<float>();
                for (uint32_t n = 0; n < in_shape[0]; ++n) {
                    float* batchPtr = in + n * in_shape[1] * size;
                    float* outBatchPtr = out + n * in_shape[1];
                    for (uint32_t c = 0; c < in_shape[1]; ++c) {
                        float* channelPtr = batchPtr + c * size;
                        for (uint32_t i = 0; i < size; ++i) {
                            max = std::max(*(channelPtr + i), max);
                        }
                        *outBatchPtr = max;
                    }
                }
                return ErrorCode::NN_OK;
            }
        }


        TensorPtr tensorBoard;
        makePadding(input[0], tensorBoard, config);
        ShapeVector in_shape = tensorBoard->getShape();
        auto& dataType = tensorBoard->getDataType();

        uint32_t out_h = (in_shape[2] - pool_param->kernel_h) / pool_param->stride_h + 1;
        uint32_t out_w = (in_shape[3] - pool_param->kernel_w) / pool_param->stride_w + 1;
        uint32_t out_c = in_shape[1];
        uint32_t out_n = in_shape[0];
        ShapeVector out_shape{out_n, out_c, out_h, out_w};
        output[0] = std::make_shared< Tensor >(out_shape);

        auto* out_ptr = output[0]->getData< float >();

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


            #pragma omp parallel for num_threads(4)
            for (uint32_t c = 0; c < out_c; ++c) {
                auto* per_channel_ptr = tensorBoard->getDataOfChannel< float >(c);
                #pragma omp parallel for num_threads(4)
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

    ErrorCode Pooling::makePadding(TensorPtr& input, TensorPtr& output, const Config& config) {
        auto shape = input->getShape();
        uint32_t N = shape[0];
        uint32_t C = shape[1];
        uint32_t H = shape[2];
        uint32_t W = shape[3];
        uint32_t wtailpad = 0;
        uint32_t htailpad = 0;
        if (pool_param->pad_mode == 0) {

            uint32_t wtail = (W + pool_param->pad_left + pool_param->pad_right - pool_param->kernel_w) % pool_param->stride_w;
            uint32_t htail = (W + pool_param->pad_top + pool_param->pad_bottom - pool_param->kernel_h) % pool_param->stride_h;
            if (wtail != 0)
                wtailpad = pool_param->stride_w - wtail;
            if (htail != 0)
                htailpad = pool_param->stride_h - htail;

            if (pool_param->pad_left > 0 || (pool_param->pad_right + wtailpad) > 0 || pool_param->pad_top || (pool_param->pad_bottom + htailpad) > 0) {
                uint32_t newW = W + pool_param->pad_left + pool_param->pad_right + wtailpad;
                uint32_t newH = H + pool_param->pad_top + pool_param->pad_bottom + htailpad;
                ShapeVector shape = {N, C, newH, newW};
                uint32_t head = newW * pool_param->pad_top;
                uint32_t tail = newH * pool_param->pad_bottom;
                TensorPtr tensor = std::make_shared< Tensor >(shape);
                float* src = input->getData< float >();
                float* dst = tensor->getData< float >();
                for (uint32_t n = 0; n < N; ++n) {
                    // dst += n * C * newH * newW;
                    // src += n * C * H * W;
                    uint32_t dst_o = 0;
                    uint32_t src_o = 0;
                    for (uint32_t c = 0; c < C; ++c) {
                        dst_o = c * newH * newW;
                        src_o = c * H * W;
                        for (uint32_t i = 0; i < H; ++i) {
                            memcpy(dst + dst_o + head + newW * i + pool_param->pad_left, src + src_o + W * i, W * 4);
                            // for (uint32_t j = 0; j < W; ++j) {
                            //     std::cout << *(src + src_o + W * i + j) << " ";
                            // }
                            // std::cout << std::endl;
                        }
                        // std::cout << std::endl;
                        // while(true);
                    }
                }
                output = tensor;
            } else {
                output = input;
            }
        }

        return ErrorCode::NN_OK;
    }
}
