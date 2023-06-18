set(targetName operator)

add_library(${targetName} STATIC src/native/Convolution.cpp include/register.h include/native/NativeRegistor.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common/thirdparty/spdlog/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common/thirdparty/googletest/googletest/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common/thirdparty/googletest/googlemock/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common/include/tensor)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common/include/data_manager)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common/include/log)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common/include/allocator)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/native)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../engine/include)