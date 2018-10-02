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

configure_file(in_test1.txt in_test1.txt COPYONLY)
configure_file(in_test2.txt in_test2.txt COPYONLY)
configure_file(in_test3.txt in_test3.txt COPYONLY)
configure_file(in_test4.txt in_test4.txt COPYONLY)
configure_file(in_test5.txt in_test5.txt COPYONLY)
configure_file(in_test6.txt in_test6.txt COPYONLY)
configure_file(out_test1.txt out_test1.txt COPYONLY)
configure_file(out_test2.txt out_test2.txt COPYONLY)
configure_file(out_test3.txt out_test3.txt COPYONLY)
configure_file(out_test4.txt out_test4.txt COPYONLY)
configure_file(out_test5.txt out_test5.txt COPYONLY)
configure_file(out_test6.txt out_test6.txt COPYONLY)

add_executable(bulk_test_cli testBulk.cpp ${HEADER_FILES} ${SRC_FILES})

set_target_properties(bulk_test_cli PROPERTIES
INCLUDE_DIRECTORIES "${GTEST_INCLUDE_DIRS};${INCLUDE_DIR}"
)

target_link_libraries(bulk_test_cli ${GTEST_LIBRARIES} )

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_link_libraries(bulk_test_cli pthread)
endif()

add_test(BulkTest1	bulk_test_cli)
add_test(BulkTest2	bulk_test_cli)
add_test(BulkTest3	bulk_test_cli)
add_test(BulkTest4	bulk_test_cli)
add_test(BulkTest5	bulk_test_cli)
add_test(BulkTest6	bulk_test_cli)