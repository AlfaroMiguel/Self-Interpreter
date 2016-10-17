add_definitions("-g -o0 -Wall -pedantic")

file (GLOB COMMON ../common/*.cpp ../common/*.h)
file (GLOB SRCS  *.cpp *.h)

add_executable (client ${SRCS} ${COMMON})