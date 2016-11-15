
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -Wno-write-strings")

file (GLOB SRCS *.cpp *.h parser/*.cpp parser/*.h)

add_executable (server ${SRCS} virtualmachine.cpp virtualmachine.h lobby.cpp lobby.h client.cpp client.h)

target_link_libraries(server common)
