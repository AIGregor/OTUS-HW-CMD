cmake_minimum_required(VERSION 3.2)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
   project(bulk VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
   project(bulk VERSION 0.0.1)
endif()

add_executable(bulk_cli main.cpp log_observer.cpp cmd.cpp 
									log_observer.h cmd.h)

set_target_properties(bulk_cli PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON  
)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set_target_properties(bulk_cli PROPERTIES COMPILE_OPTIONS -W3)
else()
	set_target_properties(bulk_cli PROPERTIES COMPILE_OPTIONS -Wpedantic -Wall -Wextra)
endif()
									
install(TARGETS bulk_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT real.garik@gmail.com)

include (CPack)