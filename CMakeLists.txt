# header
cmake_minimum_required	(VERSION 2.6)
project			(COG_object_exporter)

set		(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -ggdb -g3 -pipe")
set			(CMAKE_CXX_COMPILER "clang")

# local libraries
add_library		(mesh Mesh.cpp)

# main executable
add_executable		(main main.cpp)
target_link_libraries	(main mesh stdc++)
