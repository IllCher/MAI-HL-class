cmake_minimum_required(VERSION 3.10)

project(my_http_server)

# POCO dependencies
find_package(POCO REQUIRED Foundation Net JSON Util)

# Set compiler options
set(CMAKE_CXX_STANDARD 17)

# Add executable and sources
add_executable(my_http_server main.cpp MyRequestHandlerFactory.cpp MyRequestHandler.cpp)

# Link against POCO libraries
target_link_libraries(my_http_server ${POCO_LIBRARIES})

# Include POCO headers
target_include_directories(my_http_server PRIVATE ${POCO_INCLUDE_DIRS})



