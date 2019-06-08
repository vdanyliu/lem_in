cmake_minimum_required(VERSION 3.12.1)
project(lem_in_vis C)

set(CMAKE_C_STANDARD 99)

file(GLOB SOURCES
#        libft/*.h
#        libft/*.c
        *.h
        *.c)

aux_source_directory(libft/src LBFT_SRC)
add_library(ft STATIC ${LBFT_SRC})


add_executable(lem_in_vis
        ${SOURCES})

target_link_libraries(lem_in_vis ft)
#set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror -fsanitize=address -g -fno-omit-frame-pointer")
#set(GCC_COVERAGE_COMPILE_FLAGS "-fsanitize=address -g -fno-omit-frame-pointer")
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror")
#set(GCC_COVERAGE_COMPILE_FLAGS "-march=native -Ofast")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
target_link_libraries(lem_in_vis -lmlx "-framework OpenGL" "-framework AppKit -Wall -Wextra -Werror")

