cmake_minimum_required(VERSION 3.14)
project(Laboratorio_8)

# 🔧 Usa runtime dinámico (MultiThreadedDebugDLL) para todo el proyecto
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")

# 🛠️ Forzar GoogleTest a usar el mismo runtime que el proyecto
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Crea una biblioteca con calculator.cpp
add_library(calculator STATIC calculator.cpp)

# Asegúrate de que los headers estén disponibles para otras partes del proyecto
target_include_directories(calculator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Agrega el subdirectorio tests
add_subdirectory(tests)
