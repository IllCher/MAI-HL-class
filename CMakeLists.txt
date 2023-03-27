cmake_minimum_required(VERSION 3.16)
project(my_http_server)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)
find_package(Poco REQUIRED COMPONENTS Foundation Util Net Data MySQL)

add_executable(my_http_server
        main.cpp
        MyRequestHandler.cpp
        MyRequestHandlerFactory.cpp
        MyAPI.cpp)

target_include_directories(my_http_server PRIVATE ${POCO_INCLUDE_DIRS})
target_link_libraries(my_http_server PRIVATE ${POCO_LIBRARIES} Threads::Threads)

configure_file(config.json config.json COPYONLY)




