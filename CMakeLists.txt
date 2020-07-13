cmake_minimum_required(VERSION 3.16)

project(breakout VERSION 1.0.0 LANGUAGES C)

# raylib
add_subdirectory(external/raylib)

set_property(GLOBAL PROPERTY C_STANDARD 11)
set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")
set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -fsanitize=address -fsanitize=undefined")

add_executable(${PROJECT_NAME} 
    src/main.c
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} raylib)