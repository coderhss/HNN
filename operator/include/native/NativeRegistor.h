//
// Created by bryab on 23-6-19.
//

#ifndef HNN_NATIVEREGISTOR_H
#define HNN_NATIVEREGISTOR_H
#include "common.h"
#include "Convolution.h"
#include "Input.h"
#include "Layer.h"
#include "Pooling.h"
#include "ReLU.h"
#include "Softmax.h"
#include "Split.h"
#include "Concat.h"
#include "Dropout.h"

REGISTER_COMMON_ENGINE(HNN, Input, Layer, Input);
REGISTER_COMMON_ENGINE(HNN, Convolution, Layer, Convolution);
REGISTER_COMMON_ENGINE(HNN, Pooling, Layer, Pooling);
REGISTER_COMMON_ENGINE(HNN, ReLU, Layer, ReLU);
REGISTER_COMMON_ENGINE(HNN, Softmax, Layer, Softmax);
REGISTER_COMMON_ENGINE(HNN, Split, Layer, Split);
REGISTER_COMMON_ENGINE(HNN, Dropout, Layer, Dropout);
REGISTER_COMMON_ENGINE(HNN, Concat, Layer, Concat);

#endif //HNN_NATIVEREGISTOR_H
