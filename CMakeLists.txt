cmake_minimum_required(VERSION 3.17)
project(FCG_T1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})


add_executable(FCG_T1
        ExibePoligonosCSG.cpp
        Poligono.cpp
        Poligono.h
        Ponto.cpp
        Ponto.h
        Temporizador.cpp
        Temporizador.h)
target_link_libraries(FCG_T1 -lglut -lGLU -lGL)