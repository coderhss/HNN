//
// Created by bryab on 23-7-17.
//
#include <iostream>
#include "gtest/gtest.h"
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    auto ret = RUN_ALL_TESTS();
    std::cout << "hello world" << std::endl;
    return 0;
}