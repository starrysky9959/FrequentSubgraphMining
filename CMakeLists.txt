cmake_minimum_required(VERSION 3.0.0)
project(FSM VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O3  -Wall")

include(CTest)
enable_testing()

add_executable(
    ${PROJECT_NAME} 
    src/main.cpp
)
target_include_directories(
    ${PROJECT_NAME} PUBLIC
    src/
)
target_compile_features(
    ${PROJECT_NAME} PRIVATE 
    cxx_std_17
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
