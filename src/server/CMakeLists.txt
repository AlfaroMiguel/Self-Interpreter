add_definitions("-g -o0 -Wall -pedantic")

file (GLOB SRCS *.cpp *.h)
file (GLOB COMMON ../common/*.cpp ../common/*.h)

add_executable (server ${COMMON} ${SRCS})