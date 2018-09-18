cmake_minimum_required(VERSION 3.2)

project(hw-cmd VERSION 0.0.1)

add_executable(hw-cmd_cli main.cpp log_observer.cpp cmd.cpp 
									log_observer.h cmd.h)

install(TARGETS hw-cmd_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT real.garik@gmail.com)

include (CPack)