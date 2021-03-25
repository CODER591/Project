cmake_minimum_required(VERSION 3.10)

if(0)
find_package(Qt5 COMPONENTS Core Network Gui Widgets Qml Concurrent Sql REQUIRED)


add_library(gui_peer_lib STATIC
     friendmodel.h
     friendmodel.cpp
     friendrequestitem.h
     friendrequestitem.cpp
     frienditem.h
     frienditem.cpp
     friendrequestmodel.h
     friendrequestmodel.cpp
     messageitem.h
     messageitem.cpp
     messagemodel.h
     messagemodel.cpp
     guimanager.h
     guimanager.cpp
     rolesenum.h

)


target_link_libraries(gui_peer_lib Qt5::Core Qt5::Network Qt5::Gui Qt5::Widgets Qt5::Qml Qt5::Concurrent Qt5::Sql)

endif()