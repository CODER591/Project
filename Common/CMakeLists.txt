
find_package(Qt5 COMPONENTS Core Network Gui Widgets Qml Concurrent Sql REQUIRED)

add_library(common_lib STATIC
    client_data_types.h
    hashhelper.cpp 
    hashhelper.h
)


target_link_libraries(common_lib Qt5::Core Qt5::Network Qt5::Gui Qt5::Widgets Qt5::Qml Qt5::Concurrent Qt5::Sql)