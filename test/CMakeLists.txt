# automatically enable catch2 to generate ctest targets
if(CONAN_CATCH2_ROOT_DEBUG)
  include(${CONAN_CATCH2_ROOT_DEBUG}/lib/cmake/Catch2/Catch.cmake)
else()
  include(${CONAN_CATCH2_ROOT}/lib/cmake/Catch2/Catch.cmake)
endif()

set (CMAKE_CXX_STANDARD 17)

add_library(catch_main STATIC catch_main.cpp)

target_link_libraries(catch_main PUBLIC CONAN_PKG::catch2)
target_link_libraries(catch_main PUBLIC CONAN_PKG::rapidcheck)
target_link_libraries(catch_main PRIVATE project_options)

# set(CMAKE_CXX_FLAGS -fprofile-instr-generate -fcoverage-mapping)
add_executable(tests tests_vector.cpp tests_matrix.cpp test_line.cpp)
target_link_libraries(tests
                      PRIVATE project_warnings
                              project_options
                              catch_main
                              gem
                              --coverage)

# automatically discover tests that are defined in catch based test files you can modify the unittests. TEST_PREFIX to
# whatever you want, or use different for different binaries
catch_discover_tests(
  tests
  TEST_PREFIX
  "unittests."
  EXTRA_ARGS
  -s
  --reporter=xml
  --out=tests.xml)