add_library(bfileparser SHARED BFileParser.cc BFileItem.cc)
install(TARGETS bfileparser LIBRARY DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
        DESTINATION include/libbfileparser
        FILES_MATCHING PATTERN "*.hh")
