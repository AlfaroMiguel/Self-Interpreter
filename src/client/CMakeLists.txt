find_package (PkgConfig REQUIRED)

pkg_check_modules (GTKMM REQUIRED gtkmm-3.0)
pkg_check_modules (GOOCANVASMM REQUIRED goocanvasmm-2.0)

include_directories(${GTKMM_INCLUDE_DIRS} ${GSTMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS} ${GSTMM_LIBRARY_DIRS})

include_directories(${GOOCANVASMM_INCLUDE_DIRS} ${GOOCANVASMM_INCLUDE_DIRS})
link_directories(${GOOCANVASMM_LIBRARY_DIRS} ${GOOCANVASMM_LIBRARY_DIRS})

add_definitions("-g -o0 -Wall -Werror -pedantic -pedantic-errors -std=c++11 -pthread `pkg-config gtkmm-3.0 --cflags --libs --libs goocanvasmm-2.0`")

file (GLOB SRCS  *.cpp *.h)

add_executable (client ${SRCS})

target_link_libraries(client common)
target_link_libraries(client ${GTKMM_LIBRARIES} ${GSTMM_LIBRARIES})
target_link_libraries(client ${GOOCANVASMM_LIBRARIES} ${GOOCANVASMM_LIBRARIES})
