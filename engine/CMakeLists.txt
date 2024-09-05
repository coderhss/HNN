set(target_name engine)

add_library(${target_name} STATIC src/Blob.cpp include/Layer.h src/Layer.cpp include/NetBase.h include/Net.h src/Net.cpp include/DataReader.h src/DataReader.cpp include/ModelBin.h src/ModelBin.cpp include/ParamDict.h src/ParamDict.cpp include/Config.h src/Config.cpp include/Executer.h src/Executer.cpp)

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
