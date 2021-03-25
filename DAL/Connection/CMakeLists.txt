

add_library(dal_connect_static_lib STATIC
    connect.cpp
    connect.h
)

target_link_libraries(dal_connect_static_lib Qt5::Core Qt5::Sql)