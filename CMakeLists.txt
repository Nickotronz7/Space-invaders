cmake_minimum_required(VERSION 3.10)
project(Tarea_3 C)

set(CMAKE_C_STANDARD 99)

add_executable(Tarea_3 "Source Files/main.c" "Source Files/cJSON.c" Headers/cJSON.h "Source Files/cJSON_Utils.c"
        Headers/cJSON_Utils.h "Source Files/client.c" "Source Files/server.c" Headers/server.h Headers/client.h
        "Source Files/json_builder.c" Headers/json_builder.h "Source Files/game.c" "Headers/game.h")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})
target_link_libraries(Tarea_3 Threads::Threads)
target_link_libraries(Tarea_3 ${CURSES_LIBRARIES})