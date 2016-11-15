
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -Wno-write-strings")

file (GLOB SRCS *.cpp *.h parser/*.cpp parser/*.h parser/*.c)

add_executable (server ${SRCS})

target_link_libraries(server common)
