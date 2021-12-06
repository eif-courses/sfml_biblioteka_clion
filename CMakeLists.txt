cmake_minimum_required(VERSION 3.20)
project(sfml_biblioteka_clion)

set(CMAKE_CXX_STANDARD 14)

# Windows Operacinei sistemai
# Užkomentuoti jeigu ne Windows OS kitaip konfigūruojame
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)
#----------------------------------------

set(SFML_INCLUDE_DIR "C:/Users/Marius/Desktop/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "C:/Users/Marius/Desktop/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/include/lib")
set(SFML_DIR "C:/Users/Marius/Desktop/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries (${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
