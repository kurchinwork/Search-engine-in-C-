cmake_minimum_required(VERSION 3.20)
project(SearchEngine)

set(CMAKE_CXX_STANDARD 20)

include (FetchContent)

#Подключение библиотеки Nlohmann
FetchContent_Declare(
        json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

add_executable(SearchEngine main.cpp
        ConverterJSON.cpp
        ConverterJSON.h)

target_link_libraries(SearchEngine PRIVATE nlohmann_json::nlohmann_json)