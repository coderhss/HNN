set(target_name common)

add_library(${target_name} STATIC src/data_manager/DataManagerBase.cpp src/tensor/Tensor.cpp src/tensor/TensorBase.cpp include/log/log.h)

file(GLOB_RECURSE sub_files ${CMAKE_CURRENT_SOURCE_DIR}/include)
message(${target_name})
target_include_directories(${target_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${target_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/tensor)
target_include_directories(${target_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/data_manager)
include_directories(common/thirdparty/spdlog/include)
add_subdirectory(thirdparty)