cmake_minimum_required(VERSION 3.16)
project(gbemulator C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.16
)
FetchContent_MakeAvailable(SDL3)

add_executable(gbemulator src/main.c
    src/cart.c)
target_include_directories(gbemulator PRIVATE include)
target_link_libraries(gbemulator PRIVATE SDL3::SDL3)