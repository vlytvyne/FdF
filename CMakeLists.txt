cmake_minimum_required(VERSION 3.12)
project(fdf)

include_directories(includes)
set(SRC main.c libft.a)

add_executable(fdf ${SRC})

target_link_libraries(fdf libmlx.a /Users/vlytvyne/Desktop/fdf/libft.a "-framework OpenGL" "-framework AppKit")