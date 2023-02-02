cmake_minimum_required (VERSION 3.8)

project ("e-board")

set (OpenCV_DIR C:/opencv/build )
find_package (OpenCV REQUIRED)
include_directories (${OpenCV_INCLUDE_DIRS})

add_executable (e-board "e-board.cpp" "e-board.hpp" "main.cpp")
target_link_libraries (e-board ${OpenCV_LIBS})

set_property (TARGET e-board PROPERTY CXX_STANDARD 20)

