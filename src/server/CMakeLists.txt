
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -Wno-write-strings")

file (GLOB SRCS *.cpp *.h parser/*.cpp parser/*.h)

add_executable (server ${SRCS} virtualmachine.cpp virtualmachine.h lobby.cpp lobby.h client.cpp client.h morph.cpp morph.h server_handler.cpp server_handler.h event_handler.cpp event_handler.h event_handler_selector.cpp event_handler_selector.h connect_client_handler.cpp connect_client_handler.h initialize_client_handler.cpp initialize_client_handler.h choose_lobby_client_handler.cpp choose_lobby_client_handler.h move_morph_client_handler.cpp move_morph_client_handler.h get_client_handler.cpp get_client_handler.h do_client_handler.cpp do_client_handler.h)

target_link_libraries(server common)
