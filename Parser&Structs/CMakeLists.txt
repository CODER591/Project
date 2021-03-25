

find_package(Qt5 COMPONENTS Core Network REQUIRED)

add_library(parser_and_structs_stat STATIC
    request_types.h
    parser.h
    parser.cpp
)

target_link_libraries(parser_and_structs_stat Qt5::Core Qt5::Network)