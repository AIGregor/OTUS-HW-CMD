cmake_minimum_required(VERSION 3.2)

project(bulk_test)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(GTEST_LIBRARY C:/GTest/googletest-master/googletest/msvc/2010/gtest-md/Win32-Debug/gtestd.lib) 
	set(GTEST_MAIN_LIBRARY C:/GTest/googletest-master/googletest/msvc/2010/gtest-md/Win32-Debug/gtest_maind.lib)
	set(GTEST_ROOT C:/GTest/googletest-master/googletest)
endif()

find_package(GTest REQUIRED)

add_executable(bulk_test_cli testBulk.cpp ${HEADER_FILES})

set_target_properties(bulk_test_cli PROPERTIES
INCLUDE_DIRECTORIES "${GTEST_INCLUDE_DIRS};${INCLUDE_DIR}"
)

target_link_libraries(bulk_test_cli ${GTEST_LIBRARIES} )

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_link_libraries(bulk_test_cli pthread)
endif()

add_test(CheckSize 			bulk_test_cli)
add_test(CheckAddValue		bulk_test_cli)
add_test(CheckRemoveValue 	bulk_test_cli)
add_test(CheckFullCells 	bulk_test_cli)