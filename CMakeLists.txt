cmake_minimum_required(VERSION 3.7)

project(Arkanoid LANGUAGES C)

# Find SDL2
find_package(SDL2 REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

# Add include directories
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include)

# Add source files
file(GLOB SOURCES "src/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})

# Link SDL2 and SDL2_ttf libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})

# Copy necessary files
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sprites.bmp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
