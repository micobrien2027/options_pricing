cmake_minimum_required(VERSION 3.10)
project(OptionsPricing)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(OptionsPricing
    src/main.cpp
    src/BlackScholes.cpp
)
