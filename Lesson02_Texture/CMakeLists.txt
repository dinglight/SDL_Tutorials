cmake_minimum_required(VERSION 3.5)

# set the project name
project(hello_sdl2)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(PkgConfig)
pkg_check_modules(SDL2 REQUIRED
    sdl2
    SDL2_image
    )


# set src files
set(SRCS
    src/Game.cpp
    src/main.cpp
    )

# add the executable
add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
    ${SDL2_INCLUDE_DIRS})


file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
