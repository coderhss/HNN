set(target_name common)

add_library(${target_name} STATIC src/data_manager/DataManagerBase.cpp src/tensor/Tensor.cpp src/tensor/TensorBase.cpp src/allocator/Allocator.cpp src/common.cpp src/data_manager/DataManagerCommon.cpp)

file(GLOB_RECURSE sub_files ${CMAKE_CURRENT_SOURCE_DIR}/include)
message(${target_name})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/spdlog/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/googletest/googletest/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/data_manager)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/tensor)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/log)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/allocator)
#target_include_directories(${target_name} PUBLI${CMAKE_CURRENT_SOURCE_DIR}/include/tensorC ${CMAKE_CURRENT_SOURCE_DIR}/include)
#target_include_directories(${target_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/data_manager)
#target_include_directories(${target_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/tensor)

add_subdirectory(thirdparty)
target_link_libraries(${target_name} PUBLIC spdlog gtest)