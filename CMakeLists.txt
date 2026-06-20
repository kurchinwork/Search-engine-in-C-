cmake_minimum_required(VERSION 3.20)
project(SearchEngine)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_TLS_VERIFY OFF)

include (FetchContent)

#Подключение библиотеки Nlohmann
FetchContent_Declare(
        json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)

#Подключение библиотеки Google Test
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# Для того чтобы устранить ошибку компиляции:
# can't link... Standard Library mismatch..
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(json googletest)

enable_testing()

include_directories(include)

add_executable(SearchEngine
        src/main.cpp
        src/ConverterJSON.cpp
        src/InvertedIndex.cpp
        include/InvertedIndex.h
)
target_link_libraries(SearchEngine PRIVATE nlohmann_json::nlohmann_json)

add_executable(run_tests
        src/tests.cpp
        src/ConverterJSON.cpp
        src/InvertedIndex.cpp
        include/InvertedIndex.h
)

target_link_libraries(run_tests PRIVATE gtest_main nlohmann_json::nlohmann_json)



