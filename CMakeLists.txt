cmake_minimum_required(VERSION 3.16)

project(breakout VERSION 0.1.0 LANGUAGES C)

# raylib
add_subdirectory(external/raylib)

set_property(GLOBAL PROPERTY C_STANDARD 11)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -fsanitize=address -fsanitize=undefined")

add_executable(${PROJECT_NAME} 
    src/main.c
    src/game.c
)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -fexceptions)
target_link_libraries(${PROJECT_NAME} raylib)
target_include_directories(${PROJECT_NAME}
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)
