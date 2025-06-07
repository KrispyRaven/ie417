# tests/CMakeLists.txt

# 🔽 Archivos de test
set(TEST_SOURCES
    test_authentication.cpp
)

add_executable(test_auth ${TEST_SOURCES})

# Incluir directorios base
target_include_directories(test_auth PRIVATE ${CMAKE_SOURCE_DIR})

# Vincular con GoogleTest
target_link_libraries(test_auth
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main
)

# Registrar los tests
include(GoogleTest)
gtest_discover_tests(test_auth)
