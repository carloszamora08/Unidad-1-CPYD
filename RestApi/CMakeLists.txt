cmake_minimum_required(VERSION 3.16.1)
project(RestApi)

set(CMAKE_CXX_STANDARD 23)
find_package(Crow CONFIG REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Crow::Crow asio::asio)