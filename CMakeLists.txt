cmake_minimum_required(VERSION 3.26)

set(PROJECT_NAME school2024_test_task7)
project(${PROJECT_NAME})

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

set(CMAKE_CXX_STANDARD 20)

set(${PROJECT_NAME}_HEADERS
        src/ConfigHandler.hpp
)

set(${PROJECT_NAME}_SOURCES
        src/ConfigHandler.cpp
        src/main.cpp
)

set(${PROJECT_NAME}_SOURCE_LIST
        ${${PROJECT_NAME}_SOURCES}
        ${${PROJECT_NAME}_HEADERS}
)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCE_LIST})

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
