# tests/CMakeLists.txt
add_executable(test_calculator test_calculator.cpp)

# Asegúrate de incluir headers si fuese necesario (por ejemplo si calculator.h está un nivel arriba)
target_include_directories(test_calculator PRIVATE ${CMAKE_SOURCE_DIR})

# Enlazar con la biblioteca calculator y GoogleTest
target_link_libraries(test_calculator
    calculator
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_calculator)
