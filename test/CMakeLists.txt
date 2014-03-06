include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/../src)

add_executable( test_bfileparser test_bfileparser.cc)
target_link_libraries( test_bfileparser bfileparser crypto)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../defs/ES7v1.10.def
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY OneReg-000.KM6 DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
