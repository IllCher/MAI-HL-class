cmake_minimum_required(VERSION 3.2)

project(hl_server C CXX)

SET (service "service")
SET (writer "writer")
set (STD_CXX "c++17")
set (REDISCPP_FLAGS "-DREDISCPP_HEADER_ONLY=ON")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -std=${STD_CXX} ${REDISCPP_FLAGS}")
set (CMAKE_CXX_FLAGS_RELEASE "-O3 -g0 -std=${STD_CXX} -Wall -DNDEBUG ${REDISCPP_FLAGS}")


find_package(OpenSSL)
find_package(Threads)
find_package(ZLIB)
find_package(Poco REQUIRED COMPONENTS Foundation Util Net XML JSON Crypto NetSSL Data)
find_package(CppKafka REQUIRED)


if(NOT ${Poco_FOUND})
    message(FATAL_ERROR "Poco C++ Libraries not found.")
endif()

include_directories(${Poco_INCLUDE_DIRS})
include_directories("/usr/include/mysql")
include_directories("/usr/local/include/mysql")
link_directories("/usr/local/lib")

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${service} main.cpp
        config/config.cpp
        database/database.cpp
        database/cache.cpp
        database/user.cpp
        database/wall.cpp
        database/chat.cpp)

add_executable(load_data load_data.cpp)

add_executable(${writer} writer_main.cpp
        config/config.cpp
        database/database.cpp
        database/cache.cpp
        database/user.cpp
        database/wall.cpp
        database/chat.cpp)

target_include_directories(${service} PRIVATE "${CMAKE_BINARY_DIR}")
target_compile_options(${service} PRIVATE -Wall -Wextra -pedantic -Werror )
set_target_properties(${service} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${service} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_link_libraries(${service} PRIVATE
        ${CMAKE_THREAD_LIBS_INIT}
        ${Poco_LIBRARIES}
        "PocoData"
        "PocoDataMySQL"
        "mysqlclient"
        ZLIB::ZLIB
        "rdkafka++"
        CppKafka::cppkafka)

target_include_directories(load_data PRIVATE "${CMAKE_BINARY_DIR}")
target_compile_options(load_data PRIVATE -Wall -Wextra -pedantic -Werror )
set_target_properties(load_data PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(load_data PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_link_libraries(load_data PRIVATE
        ${CMAKE_THREAD_LIBS_INIT}
        ${Poco_LIBRARIES}
        "PocoData"
        "PocoDataMySQL"
        "mysqlclient"
        ZLIB::ZLIB
        )



target_include_directories(${writer} PRIVATE "${CMAKE_BINARY_DIR}")
target_compile_options(${writer} PRIVATE -Wall -Wextra -pedantic -Werror )
set_target_properties(${writer} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${writer} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_link_libraries(${writer} PRIVATE
        ${CMAKE_THREAD_LIBS_INIT}
        ${Poco_LIBRARIES}
        "PocoData"
        "PocoDataMySQL"
        "mysqlclient"
        ZLIB::ZLIB
        "rdkafka++"
        CppKafka::cppkafka)








