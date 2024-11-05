cmake_minimum_required(VERSION 3.10)
project(snake_game)

set(CMAKE_CXX_STANDARD 17)

include_directories("/Users/victorialoziak/Downloads/SFML-2.6.1-macOS-clang-arm64/include")

link_directories("/Users/victorialoziak/Downloads/SFML-2.6.1-macOS-clang-arm64/lib")

set(FREETYPE_ROOT "/Users/victorialoziak/Downloads/SFML-2.6.1-macOS-clang-arm64/extlibs/freetype.framework")
set(FREETYPE_INCLUDE_DIRS "${FREETYPE_ROOT}/Headers")
set(FREETYPE_LIBRARIES "${FREETYPE_ROOT}/Versions/A/freetype")

include_directories(${FREETYPE_INCLUDE_DIRS})

add_executable(snake_game main.cpp GameEngine.cpp Snake.cpp Fruit.cpp Bomb.cpp RenderingEngine.cpp )

target_link_libraries(snake_game sfml-graphics sfml-window sfml-system)
