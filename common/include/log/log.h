//
// Created by bryab on 23-4-15.
//

#ifndef HNN_LOG_H
#define HNN_LOG_H

#include "spdlog/spdlog.h"

#define _LOG_D(msg, ...)                                            \
    do {                                                            \
        spdlog::debug(msg, ##__VA_ARGS__);                          \
    } while(0)

#define _LOG_I(msg, ...)                                            \
    do {                                                            \
        spdlog::info(msg, ##__VA_ARGS__);                           \
    } while(0)

#define _LOG_W(msg, ...)                                            \
    do {                                                            \
        spdlog::warn(msg, ##__VA_ARGS__);                           \
    } while(0)

#define _LOG_E(msg, ...)                                            \
    do {                                                            \
        spdlog::error(msg, ##__VA_ARGS__);                          \
    } while(0)

#define _LOG_T(msg, ...)                                            \
    do {                                                            \
        spdlog::trace(msg, ##__VA_ARGS__);                          \
    } while(0)

#define LOG_D(...) _LOG_D(__VA_ARGS__, "")

#define LOG_I(...) _LOG_I(__VA_ARGS__, "")

#define LOG_W(...) _LOG_W(__VA_ARGS__, "")

#define LOG_E(...) _LOG_E(__VA_ARGS__, "")

#define LOG_T(...) _LOG_T(__VA_ARGS__, "")

#endif //HNN_LOG_H
