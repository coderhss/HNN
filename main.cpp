#include <iostream>
#include "TensorBase.h"
#include "log.h"
#include "spdlog/spdlog.h"
int main() {
    spdlog::debug("test log{}", 1);
    LOG_I("TEst {}", 1);
    LOG_E("error {}", 3.1);
    LOG_W("warn {}", 99);
    LOG_T("trace {}", 100);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
