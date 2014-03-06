cmake_minimum_required(VERSION 2.8)

project(libbfileparser C CXX)

set (DATADIR "${CMAKE_INSTALL_PREFIX}/share")
set (PKGDATADIR "${DATADIR}/libbfileparser")

add_subdirectory(src)
add_subdirectory(defs)
add_subdirectory(test)

add_test(NAME test WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/test COMMAND test_bfileparser)
enable_testing()
