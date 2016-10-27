find_package (PkgConfig REQUIRED)

pkg_check_modules (GTK2 REQUIRED gtk+-2.0)

include_directories (${GTK2_INCLUDE_DIRS})
link_directories (${GTK2_LIBRARY_DIRS})
add_definitions (${GTK2_CFLAGS_OTHER})

add_definitions("-g -o0 -Wall -Werror -pedantic -pedantic-errors -std=c++11 -pthread `pkg-config gtkmm-3.0 --cflags --libs --libs goocanvasmm-2.0`")

file (GLOB SRCS  *.cpp *.h)

add_executable (client ${SRCS})

target_link_libraries(client common)
target_link_libraries (client ${GTK2_LIBRARIES})