cmake_minimum_required(VERSION 3.13)
project(xsd-cxx-fusion CXX)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TARGET_PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)

include(build/conanbuildinfo.cmake)
conan_basic_setup()

if(CONAN_CATCH2_ROOT_DEBUG)
  include(${CONAN_CATCH2_ROOT_DEBUG}/lib/cmake/Catch2/Catch.cmake)
else()
  include(${CONAN_CATCH2_ROOT}/lib/cmake/Catch2/Catch.cmake)
endif()

set(COMPILATION_COMMANDS -Wunused -Wall -Wextra -Wfloat-conversion -Wpedantic -march=native -fconcepts -Wno-ignored-qualifiers)


add_custom_command( OUTPUT ${CMAKE_SOURCE_DIR}/xsd/shiporder.h ${CMAKE_SOURCE_DIR}/xsd/shiporder.cpp
  COMMAND xsdcxx cxx-tree --generate-serialization --generate-from-base-ctor --hxx-suffix .h --cxx-suffix .cpp --std c++11 --output-dir ${CMAKE_SOURCE_DIR}/xsd ${CMAKE_SOURCE_DIR}/shiporder.xsd
  MAIN_DEPENDENCY ${CMAKE_SOURCE_DIR}/shiporder.xsd
  COMMENT "Generating source code from XSD" )

add_custom_target(generate-xsd DEPENDS ${CMAKE_SOURCE_DIR}/xsd/shiporder.h ${CMAKE_SOURCE_DIR}/xsd/shiporder.cpp
  COMMENT "Checking if re-generation is required" )

add_library(xsd-lib ${CMAKE_SOURCE_DIR}/xsd/shiporder.cpp)
target_include_directories(xsd-lib PRIVATE xsd)
target_compile_options(xsd-lib PRIVATE ${COMPILATION_COMMANDS})
set_target_properties(xsd-lib PROPERTIES ${TARGET_PROPERTIES})
target_link_libraries(xsd-lib ${CONAN_LIBS})
add_dependencies(xsd-lib generate-xsd)

add_executable(xsd-cxx-fusion tests/test_main.cpp tests/test_shiporder.cpp)
target_include_directories(xsd-cxx-fusion PRIVATE include xsd)
target_compile_options(xsd-cxx-fusion PRIVATE ${COMPILATION_COMMANDS})
set_target_properties(xsd-cxx-fusion PROPERTIES ${TARGET_PROPERTIES})
target_link_libraries(xsd-cxx-fusion ${CONAN_LIBS} xsd-lib)

enable_testing()

catch_discover_tests(xsd-cxx-fusion TEST_PREFIX "constexpr." EXTRA_ARGS -s --reporter=xml --out=constexpr.xml)
