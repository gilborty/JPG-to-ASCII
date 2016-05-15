cmake_minimum_required (VERSION 2.6)
project(JPG-to-ASCII)

SET(CMAKE_CXX_FLAGS -std=c++11)

find_package( OpenCV REQUIRED )

SET( SRCS src/main.cpp
          src/Converter.cpp)

SET( ARTWORK_DIR ${CMAKE_BINARY_DIR}/artwork )      
add_executable(JPG-to-ASCII ${SRCS})

target_link_libraries( JPG-to-ASCII ${OpenCV_LIBS} )

file(MAKE_DIRECTORY ${ARTWORK_DIR} )
