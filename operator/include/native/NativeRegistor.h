//
// Created by bryab on 23-6-19.
//

#ifndef HNN_NATIVEREGISTOR_H
#define HNN_NATIVEREGISTOR_H
#include "common.h"
#include "Convolution.h"
#include "Input.h"
#include "Layer.h"

REGISTER_COMMON_ENGINE(HNN, Input, Layer, Input);
REGISTER_COMMON_ENGINE(HNN, Convolution, Layer, Convolution);
#endif //HNN_NATIVEREGISTOR_H
