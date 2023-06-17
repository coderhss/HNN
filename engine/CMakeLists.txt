set(target_name engine)

add_library(${target_name} STATIC src/Blob.cpp include/Layer.h src/Layer.cpp include/Net.h src/Net.cpp include/DataReader.h src/DataReader.cpp include/ModelBin.h src/ModelBin.cpp include/ParamDict.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common/thirdparty/spdlog/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common/thirdparty/googletest/googletest/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common/thirdparty/googletest/googlemock/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common/include/tensor)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common/include/data_manager)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common/include/log)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common/include/allocator)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common/include)
