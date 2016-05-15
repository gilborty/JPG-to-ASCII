cmake_minimum_required (VERSION 2.6)
project(JPG-to-ASCII)

SET(CMAKE_CXX_FLAGS -std=c++11)

find_package( OpenCV REQUIRED )

SET( SRCS src/main.cpp
          src/Converter.cpp)
      
add_executable(JPG-to-ASCII ${SRCS})

target_link_libraries( JPG-to-ASCII ${OpenCV_LIBS} )
