cmake_minimum_required(VERSION 3.7)

project(Arkanoid LANGUAGES C)

# Trouver SDL2
find_package(SDL2 CONFIG REQUIRED)

# Utiliser pkg-config pour SDL2_ttf
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

# Ajouter les répertoires d'en-tête
include_directories(${PROJECT_SOURCE_DIR}/include ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

# Ajouter les fichiers source
file(GLOB SOURCES "src/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})

# Lier les bibliothèques SDL2 et SDL2_ttf
if (TARGET SDL2::SDL2)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main ${SDL2_TTF_LIBRARIES})
else()
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2 SDL2main ${SDL2_TTF_LIBRARIES} m)
endif()

# Copier les fichiers nécessaires
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sprites.bmp
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

