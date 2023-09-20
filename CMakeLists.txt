cmake_minimum_required(VERSION 3.12)

project(zte-panel)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include
    vendor/HTTPRequest/include
)

add_subdirectory(src)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
