#多多IM编译配置

cmake_minimum_required(VERSION 2.6)

project(duoduo C CXX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug")
endif()

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

if(APPLE)
elseif(LINUX)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lpthread -lrt -ldl -lstdc++")
endif()

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -w -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -w -std=c++11 -pthread")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_FWRITE_UNLOCK_")

#add_subdirectory(boot)
add_subdirectory(core)
#add_subdirectory(biz)
#add_subdirectory(test)

