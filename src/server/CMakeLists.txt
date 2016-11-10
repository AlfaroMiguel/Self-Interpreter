
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

file (GLOB SRCS *.cpp *.h)

add_executable (server ${SRCS} controlador_eventos.cpp controlador_eventos.h)

target_link_libraries(server common)
