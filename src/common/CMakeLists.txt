add_definitions("-g -o0 -Wall -Werror -pedantic -pedantic-errors -std=c++11 -pthread")

file (GLOB SRCS  *.cpp *.h *.hpp)

add_library(common ${SRCS})


