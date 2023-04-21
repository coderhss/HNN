//
// Created by bryab on 23-4-15.
//

#ifndef HNN_LOG_H
#define HNN_LOG_H

#include "spdlog/spdlog.h"

#define _LOG_D(msg, ...)                                            \
    do {                                                            \
        std::string tag = "[" + std::string(__FILE__) + "] "        \
                            + std::string(msg);                     \
        spdlog::debug(tag, ##__VA_ARGS__);                          \
    } while(0)

#define _LOG_I(msg, ...)                                            \
    do {                                                            \
        std::string tag = "[" + std::string(__FILE__) + "] "        \
                            + std::string(msg);                     \
        spdlog::info(tag, ##__VA_ARGS__);                           \
    } while(0)

#define _LOG_W(msg, ...)                                            \
    do {                                                            \
        std::string tag = "[" + std::string(__FILE__) + "] "        \
                            + std::string(msg);                     \
        spdlog::warn(tag, ##__VA_ARGS__);                           \
    } while(0)

#define _LOG_E(msg, ...)                                            \
    do {                                                            \
        std::string tag = "[" + std::string(__FILE__) + "] "        \
                            + std::string(msg);                     \
        spdlog::error(tag, ##__VA_ARGS__);                          \
    } while(0)

#define _LOG_T(msg, ...)                                            \
    do {                                                            \
        std::string tag = "[" + std::string(__FILE__) + "] "        \
                            + std::string(msg);                     \
        spdlog::trace(tag, ##__VA_ARGS__);                          \
    } while(0)

#define LOG_D(...) _LOG_D(__VA_ARGS__, "")

#define LOG_I(...) _LOG_I(__VA_ARGS__, "")

#define LOG_W(...) _LOG_W(__VA_ARGS__, "")

#define LOG_E(...) _LOG_E(__VA_ARGS__, "")

#define LOG_T(...) _LOG_T(__VA_ARGS__, "")

#endif //HNN_LOG_H
